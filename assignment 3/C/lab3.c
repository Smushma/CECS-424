#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Person {
	char* name;
	int age;

} Person;

/**
 * Prints out elements for float arrays
 * (But can be made for std data types e.g. int, floar, char, etc.)
 */
void printArr(void* arr, int size) {
	for (int i = 0; i < size; i++)
		printf("%.2f \n", *((float*)arr + i));	
}

/**
 * Prints out elements for Person typedef struct arrays
 */
void printPersonArr(void* arr, int size) {
	Person* temp = (Person*) arr;

	for (int i = 0; i < size; i++)
	{
		printf("%s:%d\n", temp->name, temp->age);
		temp = ((Person*) temp + 1);
	}
}

/**
 * Compares two objects; passed as argument for std lib "qsort" function
 */
int cmpFloat (const void* a, const void* b) {
	return ((*(float*)a) - (*(float*)b));
}

/**
 * Compares Person structs for sorting by name
 * If the names are the same, order by ascending age
 */
int cmpPersonByName(const void* a, const void* b) {
	Person* temp_a = (Person*) a;
	Person* temp_b = (Person*) b;

	if(strcmp(temp_a->name, temp_b->name) == 0) // If the names are the same
		return (temp_a->age - temp_b->age); // return the name by descending age

	return strcmp(temp_a->name, temp_b->name);  // return name by alphabetical order
}

/**
 * Compares Person structs for sorting by age
 * If the ages are the same, order by name alphabetically
 */
int cmpPersonByAge(const void* a, const void* b) {
	Person* temp_a = (Person*)a;
	Person* temp_b = (Person*)b;

	if(temp_a->age == temp_b->age) // If the age are the same
		return strcmp(temp_a->name, temp_b->name); // return name by alphabetical order

	return (temp_b->age - temp_a->age); // return the name by descending age
}

int main() {
	int arrSize;

	printf("-----FLOAT SORTING-----\n");
	float arrFloat[] = { 645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26 };
	arrSize = sizeof(arrFloat) / sizeof(arrFloat[0]);
	qsort(arrFloat, arrSize, sizeof(float), cmpFloat); // Std lib sort
	printArr(arrFloat, arrSize);

	printf("\n-----PERSON STRUCT SORTING-----\n");
	printf("-----BY NAME-----\n");
	Person arrPerson[] = {[0].name = "Hal", [0].age = 20,
							[1].name = "Susann", [1].age = 31,
							[2].name = "Dwight", [2].age = 19,
							[3].name = "Kassandra", [3].age = 21,
							[4].name = "Lawrence", [4].age = 25,
							[5].name = "Cindy", [5].age = 22,
							[6].name = "Cory", [6].age = 27,
							[7].name = "Mac", [7].age = 19,
							[8].name = "Romana", [8].age = 27,
							[9].name = "Doretha", [9].age = 32,
							[10].name = "Danna", [10].age = 20,
							[11].name = "Zara", [11].age = 23,
							[12].name = "Rosalyn", [12].age = 26,
							[13].name = "Risa",[13].age = 24,
							[14].name = "Benny",[14].age = 28,
							[15].name = "Juan", [15].age = 33,
							[16].name = "Natalie", [16].age = 25};

	arrSize = sizeof(arrPerson) / sizeof(arrPerson[0]);

	// Sort by name
	qsort(arrPerson, arrSize, sizeof(Person), cmpPersonByName); // Std lib sort
	printPersonArr(arrPerson, arrSize);

	// Sort by age
	printf("\n\n-----BY AGE-----\n");
	qsort(arrPerson, arrSize, sizeof(Person), cmpPersonByAge); // Std lib sort
	printPersonArr(arrPerson, arrSize);

	return 0;
}