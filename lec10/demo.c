# include <stdio.h>
# include <string.h>
 

 struct person_t{
 	char fname[256];
 	char lname[256];
 	unsigned int age;
 };

 int main(){
 	struct person_t somePerson;

 	strcpy(somePerson.fname, "Sanchit");
 	strcpy(somePerson.lname, "Chawla");
 	somePerson.age = 12; // its primitive so you can just set it
 	//somePerson.fname = "Sunsern";

 	printf("Firstname: %s\n", somePerson.fname);
 	printf("Lastname: %s\n", somePerson.lname);
 	printf("Age: %d\n", somePerson.age);
 }