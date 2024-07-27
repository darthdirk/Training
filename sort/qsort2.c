#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 50

// Person struct to rec info about a person
typedef struct person {
    char name[NAME_LENGTH];
    int age;
    int height;
} Person;


// compares the address of the pointer but in this case its the pointer to a pointer
int compare_people(const void *pa, const void *pb) {
    // Cast to a pointer to a pointer
    const Person *A = *(const Person **)pa;
    const Person *B = *(const Person **)pb;

    // Sort by height
    return A->height - B->height;
}

// Allocate mem for a new person struct fill with the ness info
// then return the pointer that we just allocated i.e. newperson
Person *make_person(char *name, int age, int ht) {
    Person *newperson = malloc(sizeof(Person));
    memset(newperson->name, 0, NAME_LENGTH);
    strncpy(newperson->name, name, NAME_LENGTH - 1);
    newperson->age = age;
    newperson->height= ht;
    return newperson;
}

int main(int argc, const char **argv) {
    const int NUMPEOPLE = 5;

    // arr of pointers to people 
    Person **people = calloc(NUMPEOPLE, sizeof(Person *));

    people[0] = make_person("Leia", 25, 42);
    people[1] = make_person("Luke", 25, 55);
    people[2] = make_person("Yoda", 900, 25);
    people[3] = make_person("Obiwan", 45, 52);
    people[4] = make_person("Padme", 43, 48);

    qsort(people, NUMPEOPLE, sizeof(Person *), compare_people);

    printf("Index\tName\tAge\tHeight (inches)\n");

    for(int i = 0; i < NUMPEOPLE; i++) {
        Person *person = people[i];
        printf("%d\t%s\t%d\t%d\n", i, people[i]->name, people
        [i]->age, people[i]->height);

        // free the person
        free(person);
    }
    // free the entire arr
    free(people);

    return 0;
}
