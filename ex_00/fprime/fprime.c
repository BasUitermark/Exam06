#include <stdio.h>

void    fprime(int n)
{
    if (n == 1)
        printf("1");
    else
	{
        int i = 2;
        while (i <= n)
		{
            if (n % i == 0)
			{
                printf("%d", i);
                n /= i;
                if (n > 1)
                    printf("*");
            }
			else
                i++;
        }
    }
    printf("\n");
}