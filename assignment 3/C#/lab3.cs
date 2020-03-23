using System;
using System.Text;
using System.Linq;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace Lab3 {
    class Program {
        struct Person {
            public string name;
            public int age;
        }

        /**
            Prints out elements for std data types arrays
            (e.g. int, floar, char, etc.)
        */
        static void printArr<T>(IList<T> arr) {
            foreach (T element in arr)
                Console.WriteLine(element);
        }

        /**
            Prints out elements for Person struct array
        */
        static void printPersonArr(Person[]arr) {
            foreach (Person item in arr)
                Console.WriteLine(item.name + ":" + item.age);
        }

        /**
            Compares Person structs for sorting by name
            If the names are the same, order by ascending age
        */
        static int cmpPersonByName(Person a, Person b) {
            // Sort by name first then age
            if (a.name.CompareTo(b.name) == 0)
                return a.age.CompareTo(b.age);

            return a.name.CompareTo(b.name);
        }

        /**
            Compares Person structs for sorting by age
            If the ages are the same, order by name alphabetically
        */
        static int cmpPersonByAge(Person a, Person b) {
            // Sort by name first then age
            if (a.age == b.age)
                return a.name.CompareTo(b.name);

            return b.age - a.age;
        }

        static void Main(string[] args) {
            Console.WriteLine("-----FLOAT SORTING-----");
            float[] arrFloat = { 645.32f, 37.40f, 76.30f, 5.40f, -34.23f, 1.11f, -34.94f, 23.37f, 635.46f, -876.22f, 467.73f, 62.26f };
            Array.Sort(arrFloat);
            printArr<float>(arrFloat);

            Console.WriteLine("\n-----PERSON STRUCT SORTING-----");
            Person[] personArr = { new Person() { name = "Hal", age = 20 },
                                    new Person() { name = "Susann", age = 31},
                                    new Person() { name = "Dwight", age = 19},
                                    new Person() { name = "Kassandra",age = 21},
                                    new Person() { name = "Lawrence", age = 25},
                                    new Person() { name = "Cindy", age = 22},
                                    new Person() { name = "Cory", age = 27},
                                    new Person() { name = "Mac", age = 19},
                                    new Person() { name = "Romana", age = 27},
                                    new Person() { name = "Doretha", age = 32},
                                    new Person() { name = "Danna", age = 20},
                                    new Person() { name = "Zara", age = 23},
                                    new Person() { name = "Rosalyn", age = 26},
                                    new Person() { name = "Risa", age = 24},
                                    new Person() { name = "Benny", age = 28},
                                    new Person() { name = "Juan", age = 33},
                                    new Person() { name = "Natalie", age = 25} };

            // Sort by name
            Console.WriteLine("-----BY NAME-----");
            Array.Sort<Person>(personArr, cmpPersonByName);
            printPersonArr(personArr);

            // Sort by age
            Console.WriteLine("\n-----BY AGE-----");
            Array.Sort<Person>(personArr, cmpPersonByAge);
            printPersonArr(personArr);
        }
    }
}