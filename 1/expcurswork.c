#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "AVLtree.h"

int main()
{
    FILE *file = fopen("Meow.txt", "r");
    char **values;
    values = malloc(8 * 50000);
    for (int i = 0; i < 50000; i++)
    {
        values[i] = malloc(20);
        fscanf(file, "%s", values[i]);
    }
    struct avltree *head = avltree_create(0, values[0]);
    for (int j = 0; j < 50000; j++)
    {
        head = avltree_add(head, j, values[j + 1]);
        if ((j + 1) % 2000 == 0)
        {
            clock_t begin, end;   
            double final= 0.0;
            struct avltree *tmp = head;
            for (int k = 0; k < 1000000; k++)
            {
                begin=clock();
	            tmp = avltree_add(tmp, j+1, "test");
	            end=clock();
	            final+=(double)(end-begin)/ CLOCKS_PER_SEC;
            }
	        printf("n = %d; time = %.6lf \n", j+1, final);

        }
    }
    avltree_free(head);
    for (int i = 0; i < 50000; i++)
        free(values[i]);
    free(values);
    return 0;
}