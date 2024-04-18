#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER 1000001

typedef struct
{
	int height;
	int width;
	bool isValid;
} mapInfo;

int	str_len(const char *str)
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

int read_file(char *filename, char *buffer)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error("Error opening file\n");
	
	int read_bytes = read(fd, buffer, BUFFER - 1);
	if (read_bytes == -1)
		handle_error("Error reading file\n");
	
	buffer[read_bytes] = '\0';
	close(fd);
	return(read_bytes);
}

mapInfo validate_map(const char *buffer)
{
	mapInfo info = {0, 0, true};
	int cur_width = 0;
	bool firstLine = true;

	for (int i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '\n')
		{
			if (firstLine)
			{
				firstLine = false;
				info.width = cur_width;
			}
			else if (cur_width != info.width)
			{
				info.isValid = false;
				break ;
			}
			cur_width = 0;
			info.height++;
		}
		else if (buffer[i] == 'X' || buffer[i] == '.')
			cur_width++;
		else
		{
			info.isValid = false;
			break ;
		}
	}

	if (cur_width > 0 && cur_width != info.width)
		info.isValid = false;
	// if (buffer[0] != '\0' && buffer[str_len(buffer) - 1] == '\n')
	// 	info.height--;

	return info;
}

void explore_block(const char *map, int width, int height, int x, int y, bool visited[BUFFER], int *current_size)
{
	if (x < 0 || x >= width || y < 0 || y >= height || map[y * (width + 1) + x] != 'X' || visited[y * width + x])
		return ;
	
	visited[y * width + x] = true;

	(*current_size)++;

	explore_block(map, width, height, x + 1, y, visited, current_size);
	explore_block(map, width, height, x - 1, y, visited, current_size);
	explore_block(map, width, height, x, y + 1, visited, current_size);
	explore_block(map, width, height, x, y - 1, visited, current_size);
}

int find_largest_block(const char *map, int height, int width)
{
	bool visited[BUFFER] = {false};
	int max_block = 0;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			if (map[y * (width + 1) + x] == 'X' && !visited[y * width + x])
			{
				int current_size = 0;
				explore_block(map, width, height, x, y, visited, &current_size);
				if (current_size > max_block)
					max_block = current_size;
			}

	return max_block;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		handle_error("Usage: program <filename>\n");
	
	char buffer[BUFFER];
	read_file(argv[1], buffer);

	mapInfo map_info = validate_map(buffer);
	if (!map_info.isValid)
		handle_error("Invalid Map\n");
	
	int largest_block = find_largest_block(buffer, map_info.height, map_info.width);

	printf("%d\n", largest_block);
	return EXIT_SUCCESS;
}