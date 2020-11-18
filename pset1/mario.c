#include <stdio.h>

int main(void)
{
    int height = 0;
    while (height < 1)
    {
    	printf("Height: ");
    	scanf("%d", &height);
    }
    int space = height - 1;
    int hash = 1;
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < space; a++)
        {
            printf(" ");
        }
        for (int b = 0; b < hash; b++)
        {
            printf("#");
        }
        printf(" ");
        for (int b = 0; b < hash; b++)
        {
            printf("#");
        }
        for (int a = 0; a < space; a++)
        {
            printf(" ");
        }
        space--;
        hash++;
        printf("\n");
    }
    
    return 0;
}