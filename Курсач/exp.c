#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "AA.h"

int main()
{
    struct node *head = new_node(0);
    for (int j = 0; j < 50000; j++)
    {
        head = insert(head, j);
        if ((j + 1) % 2000 == 0)
        {
            clock_t begin, end;   
            double final= 0.0;
            struct node *tmp;
            for (int k = 0; k < 1000000; k++)
            {
                begin=clock();
	            tmp = lookup(head, j); /*delete_node(head, j);*/
	            end=clock();
	            final+=(double)(end-begin)/ CLOCKS_PER_SEC;
            }
	        printf("n = %d; time = %.6lf \n", j+1, final);

        }
    }
    free_tree(head);
    return 0;
}