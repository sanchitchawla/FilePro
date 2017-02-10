#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct person_t
{
  char fname[256];
  char lname[256];
  unsigned int age;
};

typedef struct person_t Person;

void resetPerson(Person*);

int main(
{
  struct person_t somePerson;

  strcpy(somePerson.fname, "Peter");
  strcpy(somePerson.lname, "Struschka");
  somePerson.age = 19;

  printf("Firstname = %s\n", somePerson.fname);
  printf("Lastname = %s\n", somePerson.lname);
  printf("age = %u\n", somePerson.age);

  resetPerson(&somePerson);

  struct person_t* dynamicPerson;

  printf("Size = %lu\n", sizeof(struct person_t));
  dynamicPerson = (struct person_t*)malloc(sizeof(struct person_t));

  /* (*dynamicPerson).fname is the same as dynamicPerson->fname */
  strcpy(dynamicPerson->fname, "Peter");
  strcpy(dynamicPerson->lname, "Struschka");
  dynamicPerson->age = 20;

  printf("Firstname = %s\n", dynamicPerson->fname);
  printf("Lastname = %s\n", dynamicPerson->lname);
  printf("age = %u\n", dynamicPerson->age);

  resetPerson(dynamicPerson);

  free(dynamicPerson);
  dynamicPerson = NULL;

  return 0;
}

void resetPerson(struct person_t* person)
{
  strcpy(person->fname, "");
  strcpy(person->lname, "");
  person->age = 0;
}
