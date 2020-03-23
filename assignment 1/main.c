#include <stdio.h>
#include <stdlib.h>

/** 
  Function to print int array

  @param a[] the array to print
  @param len the length of the array
*/
void printArr(int a[], int len){
  for (int i = 0; i < len; i++) { //iterate through each element in array
    printf("%d ", a[i]); //print each element in array
  }
  printf("\n"); //print newline
}

/**
  Quicksort function for int array

  @param *a the pointer to the starting address of the array
  @param n the length of the array
*/
void qsort2(int *a, int n) {
  if (n < 2) return; //if only 1 element in list, return back to procedure

  int pivot = a[n / 2]; //set the pivot to the "middle" element of the array

  int i, j; //declare iterators to walk through the array
  for (i = 0, j = n - 1; ; i++, j--) { //work from each end, one end towards the other end
    while (a[i] < pivot) //make sure elements before the pivot are less than
      i++; //if current element is less than pivot, increment 'i' to check next element
    while (a[j] > pivot)  //make sure elements after the pivot are greater than
      j--; //if current element is greater than pivot, decrement 'j' to check next element

    if (i >= j) break; //if 'i' is greater or equal to j, stop looping thru the array. We must swap the pivot with a[j] as an element is "out of order"

    //swapping integer positions within array
    int temp = a[i]; //initialize temp variable to element at a[i]
    a[i] = a[j]; //set a[i] equal to a[j]
    a[j] = temp; //set a[j] equal to temp
  }
  
  qsort2(a, i); //recursive 'qsort2()' call for start of arr to 'i'th position for "first half" sorting
  qsort2(a + i, n - i); //recursive 'qsort2()' call for starting offset to 'n - i'th position for "second half" sorting
}

/**
  Helper function for mergesort, swaps elements based on conditions

  @param *a the pointer to the starting address of the array
  @param len the length of the array
  @param mid the "middle" element's position in the array
*/
void merge (int *a, int len, int mid) {
  int i, j, k; //declare iterators
  int *temp = malloc(len * sizeof(int)); //dynamically allocate a single large block of memory with the specified size

  for (i = 0, j = mid, k = 0; k < len; k++) { //walk thru both 'temp' and 'a' starting at the first element
    //let temp[k] equal to...
    if (j == len) temp[k] = a[i++]; //if 'j' is equal to 'len', then temp[k] == a[i++]
    else if (i == mid) temp[k] = a[j++]; //else if 'i' is equal to 'mid', then temp[k] = a[j++]
    else if (a[j] < a[i]) temp[k] = a[j++]; //else if 'a[j]' is less than 'a[i]', then temp[k] = a[j++]
    else temp[k] = a[i++]; //else temp[k] = a[i++]
  }

  for (i = 0; i < len; i++) { //loop through array 'temp'
    a[i] = temp[i]; //replace every element in 'a' with element in 'temp'
  }

  free(temp); //deallocates the memory previously allocated by malloc()
}

/**
  Mergesort function for int array

  @param *a the pointer to the starting address of the array
  @param n the length of the array
*/
void msort(int *a, int n) {
  if (n < 2) return; //if only 1 element in list, return back to procedure

  int mid = n / 2; //initialize 'mid' to the "middle" element's position in the array
  
  msort(a, mid); //recursive 'msort()' call for start of arr to 'mid' position for "first half" sorting
  msort(a + mid, n - mid); //recursive 'msort()' call for starting offset to 'n - mid' position for "second half" sorting
  merge(a, n, mid); //call 'merge()' to combine each half into a single array
}

/**
  Main function

  @param void
*/
int main(void) {
  int arr1[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1}; //initialize array 'arr1'
  size_t n1 = sizeof(arr1)/sizeof(arr1[0]); //calculate size of 'arr1'
  printf("Before quicksort:\n");
  printArr(arr1, n1); //call printArr() to print 'arr1' before quicksort
  qsort2(arr1, n1); //call qsort2() function to quicksort 'arr1'
  printf("After quicksort:\n");
  printArr(arr1, n1); //call printArr() to print 'arr1' after quicksort

  int arr2[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1}; //initialize array 'arr2'
  size_t n2 = sizeof(arr2)/sizeof(arr2[0]); //calculate size of 'arr2'
  printf("Before mergesort:\n");
  printArr(arr2, n2); //call printArr() to print 'arr2' before mergesort
  msort(arr2, n2); //call msort() function to mergesort 'arr2'
  printf("After mergesort:\n");
  printArr(arr2, n2); //call printArr() to print 'arr2' after mergesort

  return 0; //end main
}