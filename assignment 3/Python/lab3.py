class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def __repr__(self):
        return '{}:{}'.format(self.name, self.age)

if __name__ == '__main__':
    # Sort float list
    float_list = list_float = [645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26]
    float_list.sort()
    print(float_list)
    print()

    person_list = [Person("Hal", 20),
                   Person("Susann", 31),
                   Person("Dwight", 19),
                   Person("Kassandra", 21),
                   Person("Lawrence", 25),
                   Person("Cindy", 22), 
                   Person("Cory", 27), 
                   Person("Mac", 19),
                   Person("Romana", 27), 
                   Person("Doretha", 32),
                   Person("Danna", 20), 
                   Person("Zara", 23), 
                   Person("Rosalyn", 26), 
                   Person("Risa", 24), 
                   Person("Benny", 28),
                   Person("Juan", 33), 
                   Person("Natalie", 25)]

    # Sort Persons by name
    person_list.sort(key=lambda Person: Person.name) 
    print(person_list)
    print()

    # Sort Persons by age
    person_list.sort(key=lambda Person: Person.age, reverse=True)
    print(person_list)
