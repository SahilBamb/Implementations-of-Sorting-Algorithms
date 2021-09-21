/*
 *
 *  srtheap.c file
 *
 */

#include <stdbool.h>
#include <stddef.h>
#include "srt.h"
#include <stdio.h>
#include <limits.h>

//L(x) = 2x + 1
//R(x) = 2x + 2
//P(x) = (x-2)/2 <-Integer division 

void Heapify(void *base, size_t nelem, size_t size, int (*compar)(const void *, const void *), int rootIndex) {

    char *root = (char *)base + size * rootIndex;

    int tempIndex = rootIndex;
    char *tempPerm = (char *)base + size * rootIndex;

    int lChild = 2*(rootIndex+1)-1;
    char *leftChild = (char *)base + size * lChild;

    int rChild = 2*(rootIndex+1);
    char *rightChild = (char *)base + size * rChild;

    //If leftchild exists compare it to the root
    //If its greater than it, replace it within TempPerm and tempIndex
    if ((lChild<nelem) && (compar(leftChild,tempPerm)>0)) {
        tempIndex = lChild;
        tempPerm = (char *)base + size * lChild;

    }

    //If rightchild exists compare it to root or leftchild (tempPerm)
    //If its greater than it, replace it within TempPerm and tempIndex
    if ((rChild<nelem) && (compar(rightChild,tempPerm)>0)) {
        tempIndex = rChild;
        tempPerm = (char *)base + size * rChild;

    }

    //Note for later: this could potentially be replaced with only tempIndex and reusable child var

    if (rootIndex!=tempIndex) {
        swap(tempPerm,root,size);
        Heapify(base, nelem,size, compar, tempIndex);
    }

}


//Base address of array, nuimber of elements in that array, and size of each element in the array
void srtheap(void *base, size_t nelem, size_t size, int (*compar)(const void *, const void *)) {

    //Runs from first parent to 0, making sure that each node is a Heap
    //Starts at first parent because 'no child nodes' are automatically Heaps

    int rootIndex=(nelem/2)-1;
    while(rootIndex>-1){
        Heapify(base,nelem,size,compar,rootIndex);
        rootIndex--;
    }


    //Swaps first and last positions (max position at front of max heap)
    //Turns the entire list into a max heap starting at position 0 and going until end
    //arrSize constantly shrinks as last element is sorted and not part of heap anymore
    
    int arrSize=(nelem-1);
    while(arrSize>0){
        char *start = (char *)base;
        char *end = (char *)base + size * (arrSize);
        swap(start,end,size);
        Heapify(base,arrSize,size,compar,0);
        arrSize--;
    }


    return;

}



//In order to compile use
//gcc -std=c99 -DRAND -DPRINT -DTYPE=(float | double) -D(BUBB | HEAP | INSR | MERG) *.c

