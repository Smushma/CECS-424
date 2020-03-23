#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Define a struct to represent an allocation block
struct Block {
  int block_size; //# of bytes in the data section
  struct Block *next_block; //pointer to the next block
};

//Function prototypes
void my_initialize_heap(int size);
void* my_malloc(int size);
void my_free(void *data);
void test();
void formula();
void program();

//Global var. to determine the size of a block
const int OVERHEAD_SIZE = sizeof(struct Block); //16 bytes
//Global var. to determine the size of a void*
const int VOID_SIZE = sizeof(void*); //8 bytes
//Global pointer to the first free block in the free list
struct Block *free_head;

/**
 * Main block 
 */
int main(void) {
  test();
  program();

  return 0;
}

/**
 * Initialize heap 
 */
void my_initialize_heap(int size) {
  free_head = malloc(size); //allocate a block in memory of specified size
  free_head->block_size = size - OVERHEAD_SIZE; 
  free_head->next_block = NULL;
}

/**
 * Memory allocation
 */
void* my_malloc(int size) {
  //6(b)
  int multiple_of_void_ptr = size % VOID_SIZE; //4 bytes
  if (multiple_of_void_ptr) size += VOID_SIZE - multiple_of_void_ptr;

  struct Block *curr_block_ptr, 
    *prev_block_ptr = NULL, 
    *new_block_ptr;
	
  //Starting at the free_head, keep iterating thru the free list 
  //until we reach the end of it ("null" block)
  for (curr_block_ptr = free_head; curr_block_ptr; curr_block_ptr = curr_block_ptr->next_block) {
    if (curr_block_ptr->block_size >= size) { //The current block is big enough to fit the data
      //remaining space after data allocation
      int leftover_block_size = curr_block_ptr->block_size - size - OVERHEAD_SIZE; 
      
      //Decide whether or not we want to split the block
      if (leftover_block_size >= VOID_SIZE) { //Enough leftover space to create a new block
        //Initialize a new block at that location by assigning its block_size 
        new_block_ptr = (struct Block*) ((char*)(curr_block_ptr + 1) + leftover_block_size);
        new_block_ptr->block_size = size;
        //and setting its next_block pointer to null.
        new_block_ptr->next_block = NULL;

        //Reduce the size of the current block (our data can be put in)
        curr_block_ptr->block_size = leftover_block_size; 

        //New block pointing to the next data section
        return new_block_ptr + 1;
      }

      //Cannot split the block
      //redirect pointers to the block to point to the block that follows it
      if (prev_block_ptr) //If there was a prev block, set it to the next one
        prev_block_ptr->next_block = curr_block_ptr->next_block;
      else //the first node
        free_head = free_head->next_block;

      //Return a pointer to the data region of the block, 
      //which is “overhead size” bytes past the start of the block
      return curr_block_ptr + 1;
    }
    prev_block_ptr = curr_block_ptr; //Keep track of the previous node
  }
  return 0; //No free block found
}

/**
 * Free data block
 */
void my_free(void *data) {
  struct Block *free_block = (struct Block*) data - 1;
  free_block->next_block = free_head; //add block to the free list
  free_head = free_block;
}

/**
 * Testing the code
 */
void test() {
  printf("Sizes of data types:\n");
  printf("sizeof(char) = %zd\n", sizeof(char));
  printf("sizeof(int) = %zd\n", sizeof(int));
  printf("sizeof(double) = %zd\n", sizeof(double));
  printf("sizeof(void) = %zd\n", sizeof(void));
  printf("sizeof(void*) = %d\n", VOID_SIZE);
  printf("sizeof(struct Block) = %d\n", OVERHEAD_SIZE);

  int size = 1000;
  my_initialize_heap(size);

  //Test 1
  printf("\n-----Test 1-----\n");
  int* t1a = my_malloc(sizeof(int));
  printf("First my_malloc call: %p\n", t1a);
  my_free(t1a);
  printf("-> my_free() called\n");
  int* t1b = my_malloc(sizeof(int));
  printf("Second my_malloc call: %p\n", t1b);
  my_free(t1b);

  //Test 2
  printf("\n-----Test 2-----\n");
  int* t2a = my_malloc(sizeof(int));
  printf("First my_malloc call: %p\n", t2a);
  int* t2b = my_malloc(sizeof(int));
  printf("Second my_malloc call: %p\n", t2b);
  printf("The difference in address should be %d\n", (OVERHEAD_SIZE + VOID_SIZE));
  printf("Distance = %zd\n", (char*)t2a - (char*)t2b);
  my_free(t2a);
  my_free(t2b);

  //Test 3
  printf("\n-----Test 3-----\n");
  int* t3a = my_malloc(sizeof(int));
  printf("Address for the first integer is: %p\n", t3a);
  int* t3b = my_malloc(sizeof(int));
  printf("Address for the second integer is: %p\n", t3b);
  int* t3c = my_malloc(sizeof(int));
  printf("Address for the third integer is: %p\n", t3c);
  my_free(t3b);

  printf("-> Integer 2 freed\n");
  double* t3d = my_malloc(sizeof(double));
  printf("Address for the double is: %p\n", t3d);
  my_free(t3a);
  my_free(t3c);
  my_free(t3d);

  //Test 4
  printf("\n-----Test 4-----\n");
  char* t4a = my_malloc(sizeof(char));
  printf("Address for the character is: %p\n", t4a);
  int* t4b = my_malloc(sizeof(int));
  printf("Address for the integer is: %p\n", t4b);
  printf("The difference in address should be the same as in Test 2: %d\n", (OVERHEAD_SIZE + VOID_SIZE));
  printf("Distance = %ld\n", (char*)t4a - (char*)t4b);
  my_free(t4a);
  my_free(t4b);

  //Test 5
  printf("\n-----Test 5-----\n");
  int *t5a = my_malloc(100 * sizeof(int));
  int *t5b = my_malloc(sizeof(int));
  printf("Address for the array is: %p\n", t5a);
  printf("Address for the integer is: %p\n", t5b);
  printf("The difference between the addresses should be %ld\n", (100 * sizeof(int) + OVERHEAD_SIZE));

  my_free(t5a);
  printf("-> Array freed\n");
  printf("Address for the integer is: %p\n", t5b);
}

/**
 * Sigma formula
 */
void formula(int *arr, int size) {
    double sum_of_numbers = 0;
    for (int i = 0; i < size; i++) sum_of_numbers += arr[i];
 
    double mu = sum_of_numbers / size; //arithmetic mean of sum of numbers
    
    double summation = 0;
    for (int j = 0; j < size; j++) summation += pow(arr[j] - mu, 2);
    
    printf("\nSigma = %f\n\n", sqrt(summation/size));
}

/**
 * Test allocator to solve a classic problem requiring dynamic storage
 */
void program() {
  printf("\n-----Dynamic Storage Program-----\n");

  //User input 
  printf("Enter a positive int to initialize array: ");
  int size = 0;
  scanf("%d", &size);

  //Initialize array
  int *arr = my_malloc(size * sizeof(int));

  //Add values into array
  for (int i = 0; i < size; i++) {
    printf("\nPlease enter a positive integer(data): ");
    scanf("%d", &arr[i]);
  }

  //Call function to perform calculation
  formula(arr, size);
}