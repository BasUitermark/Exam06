#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#define MAX_BUFFER 1000001

int str_len(const char *str)
{
	int i = 0;
	while (str[i]) i++;
	return i;
}

void handle_error(const char *msg)
{
    write(STDERR_FILENO, msg, str_len(msg));
    exit(EXIT_FAILURE);
}

int read_file(const char *filename, char *buffer)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        handle_error("Error opening file\n");

    int read_bytes = read(fd, buffer, MAX_BUFFER - 1);
    if (read_bytes == -1)
	{
        close(fd);
        handle_error("Error reading file\n");
    }

    buffer[read_bytes] = '\0';
    close(fd);
    return read_bytes;
}

int map_height(const char *buffer)
{
    int height = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '\n')
            height++;
    return height;
}

int map_width(const char *buffer)
{
    int width = 0;
    while (buffer[width] != '\n' && buffer[width] != '\0')
        width++;
    return width;
}

bool validate_map(const char *buffer)
{
    int width = 0, height = 0;
    bool isFirstLine = true;
    int currentWidth = 0;

    for (int i = 0; buffer[i] != '\0'; i++) 
	{
        if (buffer[i] == '\n')
		{
            if (isFirstLine) 
			{
                isFirstLine = false;
                width = currentWidth;
            } 
			else if (currentWidth != width)
                return false;
            currentWidth = 0;
            height++;
        }
		else if (buffer[i] == 'X' || buffer[i] == '.')
            currentWidth++;
        else
            return false;
    }

    if (currentWidth > 0 && currentWidth != width)
        return false;

    if (buffer[0] != '\0' && buffer[str_len(buffer) - 1] == '\n')
        height--;

    return true;
}

void explore_block(const char *map, int width, int height, int x, int y, bool visited[MAX_BUFFER], int *current_size)
{
    if (x < 0 || x >= width || y < 0 || y >= height || map[y * (width + 1) + x] != 'X' || visited[y * width + x])
        return;

    visited[y * width + x] = true;

    (*current_size)++;

    explore_block(map, width, height, x + 1, y, visited, current_size); // Right
    explore_block(map, width, height, x - 1, y, visited, current_size); // Left
    explore_block(map, width, height, x, y + 1, visited, current_size); // Down
    explore_block(map, width, height, x, y - 1, visited, current_size); // Up
}

int find_largest_block(const char *map, int width, int height)
{
    bool visited[MAX_BUFFER] = {false};
    int max_block_size = 0;

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            if (map[y * (width + 1) + x] == 'X' && !visited[y * width + x])
			{
                int current_size = 0;
                explore_block(map, width, height, x, y, visited, &current_size);
                if (current_size > max_block_size)
                    max_block_size = current_size;
            }

    return max_block_size;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        handle_error("Usage: program <filename>\n");

    char buffer[MAX_BUFFER];
    read_file(argv[1], buffer);

    if (!validate_map(buffer))
        handle_error("Invalid Map\n");

    int largest_block_size = find_largest_block(buffer, map_width(buffer), map_height(buffer));

    printf("%d\n", largest_block_size);
    return EXIT_SUCCESS;
}
