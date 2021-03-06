#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// sorted 536870911 random elements in 368.177274 seconds

// sorted 1000000 random elements in .304547 seconds

// Memory efficient and quick sorting algorithm (O(nlogn))

/* HeapSort takes advantage of a Heap Data Structure */

/* Sifts an item down the heap if it is less than either of its children */
void sift_down(int **items, int numitems, int index)
{
    int elementToSift = (*items)[index];
    int leftchild = 2 * index + 1;
    int rightchild = 2 * index + 2;
    int child = leftchild;

    if(leftchild > numitems)
    {
        return;
    }

    if(rightchild < numitems && (*items)[rightchild] > (*items)[leftchild])
    {
        child = rightchild;
    }

    if((*items)[index] < (*items)[child])
    {
        (*items)[index] = (*items)[child];
        (*items)[child] = elementToSift;
        sift_down(items, numitems, child);
    }
    return;
}

/* Removes the top item of the heap */
int remove_max(int **items, int numitems)
{
    int element = (*items)[0];
    (*items)[0] = (*items)[numitems];
    sift_down(items,numitems,0);
    return element;
}

/* Builds the heap */
void build_heap(int **items, int numitems)
{
    int i;
    for(i = (numitems - 2)/2; i >= 0; i--)
        sift_down(items, numitems, i);
}

/* The actual sorting algorithm */
void *ascending_heap_sort(int **items, int numitems)
{
    build_heap(items, numitems);

    int sorted;
    for(sorted = numitems - 1; sorted > 0; sorted--)
    {
        //numitems--;
        int num = remove_max(items, sorted);
        (*items)[sorted] = num;
    }
}

/* -------------------------------------------------------- */
/* Main method strictly for testing */
#include <time.h>
int main(int argv, char* args[])
{
    int arg = atoi(args[1]);
    int *a = (int *)malloc(4*arg);

    int j;
    srand(time(NULL));
    for(j = 0; j < arg; j++)
    {
        a[j] = rand() % arg + 1;
    }
    
    for(j = 0; j < arg; j++)
        printf("%d\n",a[j]);
    printf("\n");
    
    clock_t begin, end;
    double time_spent;
    begin = clock();
    ascending_heap_sort(&a,arg);
    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    int i;
    for(i = 0; i < arg; i++)
    {
        printf("%d\n",a[i]);
    }
    
    printf("sorted %d elements in %f seconds\n", arg, time_spent);
    return 0;
}
