#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Person {
    string name;
    int age;
};

/**
 * Prints out elements for std data types arrays
 * (e.g. int, floar, char, etc.)
 */
template<class T>
void printArr(T arr[], int size) {
    for (size_t i = 0; i < size; i++)
        cout << arr[i] << endl;
}

/**
 * Prints out elements for Person struct array
 */
void printPersonArr(Person arr[], int size)
{
	for (int i = 0; i < size; i++)
        cout << arr[i].name << ":" << arr[i].age << endl; 
}

/**
 * Compares Person structs for sorting by name
 * If the names are the same, order by ascending age
 */
bool cmpPersonByName(Person a, Person b) {
    if (a.name == b.name) // If the names are the same
        return a.age < b.age; // return the one that has the younger age first

    return a.name < b.name; // return the name by alphabetical order
}

/**
 * Compares Person structs for sorting by age
 * If the ages are the same, order by name alphabetically
 */
bool cmpPersonByAge(Person a, Person b) {
    if (a.age == b.age) // If the age are the same
        return a.name < b.name; // return name by alphabetical order

    return a.age > b.age; // return the name by descending age
}

int main() {
    int arrSize; 

    cout << "-----FLOAT SORTING-----" << endl;
    float floatArr[] = { 645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26 };
    arrSize = sizeof(floatArr) / sizeof(floatArr[0]);
    sort(floatArr, floatArr + arrSize); // Std lib sort
    printArr(floatArr, arrSize);

    cout << "\n-----PERSON STRUCT SORTING-----" << endl;
    Person personArr[] = { {"Hal", 20},
                            {"Susann", 31},
							{"Dwight", 19}, 
							{"Kassandra",21},
							{"Lawrence", 25},
							{"Cindy", 22},
							{"Cory", 27},
							{"Mac", 19},
							{"Romana", 27},
							{"Doretha", 32},
							{"Danna", 20},
							{"Zara", 23},
							{"Rosalyn", 26},
							{"Risa", 24},
							{"Benny", 28},
							{"Juan", 33},
							{"Natalie", 25} };
                            
    arrSize = sizeof(personArr) / sizeof(personArr[0]);

    // Sort by name
    cout << "-----BY NAME-----" << endl;
    sort(personArr, personArr + arrSize, cmpPersonByName); // Std lib sort
    printPersonArr(personArr, arrSize);

    // Sort by age
    cout << "\n-----BY AGE-----" << endl;
    sort(personArr, personArr + arrSize, cmpPersonByAge); // Std lib sort
    printPersonArr(personArr, arrSize);

    return 0;
}