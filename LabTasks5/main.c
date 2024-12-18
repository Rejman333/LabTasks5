#include <stdio.h>
#include <stdlib.h>
#include <string.h> //For strcpy()
#include "my_header.h"

typedef struct {
	char name[128];
	char surname[128];
	int year;
	double score;
} Student;

void input_student_data(Student* p_student) {
	//Placeholders
	char name[128];
	char surname[128];
	int year;
	double score;

#ifdef SAFE_MODE
	printf("Name: \n");
	input_string_safely(name, (unsigned int)sizeof(name));
	stdin_clear();
	printf("Surname: \n");
	input_string_safely(surname, sizeof(surname));
	stdin_clear();
	printf("Year of birth: \n");
	input_int_safely(&year);
	stdin_clear();
	printf("Score: \n");
	input_double_safely(&score);
	stdin_clear();

	strcpy_s(p_student->name, sizeof(name), name);
	strcpy_s(p_student->surname, sizeof(surname), surname);
#else
	printf("Name: \n");
	input_string(name, (unsigned int)sizeof(name));
	stdin_clear();
	printf("Surname: \n");
	input_string(surname, (unsigned int)sizeof(surname));
	stdin_clear();
	printf("Year of birth: \n");
	input_int(&year);
	stdin_clear();
	printf("Score: \n");
	input_double(&score);
	stdin_clear();

	strcpy(p_student->name, name);
	strcpy(p_student->surname, surname);
#endif

	// strcpy(student.name, "Jan Kowalski"); We can use that to input string to a struct
	// snprintf or strncpy Would be safer!
	p_student->year = year;
	p_student->score = score;
}

void all_print(Student* students, int students_length) {
	for (int i = 0; i < students_length; i++) {
		printf("%d.\n\tName: %s\n\tSurname: %s\n\tYear: %d\n\tScore: %.2lf\n",
			i + 1, students[i].name, students[i].surname, students[i].year, students[i].score);
	}
}

void stdin_clear() {
	while (getchar() != '\n');
}

//Lots of explanation in here!
int input_string(char* str, unsigned int str_length) {
	char format[64];
	int result = 0;
	/*
	This creates a format string, but what is that?
	For example, if our str_length is 10,
	we would get a format string that looks like this:
		"%9s" — This tells the program to read a string that is at most
				9 characters long.

	When we use sprintf_s(), we don’t need to manually create this format string
	because sprintf_s() automatically ensures the length of the resulting string
	does not exceed the specified size.

	In this case, by using a custom format string, we make scanf() safer.
	To create the format string dynamically, we need to use triple % signs (%%%)
	to produce a single % in the final format string.
	*/

	//sprintf_s(
	//			char* format_array, sizeof(format_array),
	//			"%%%ds" base format string, str_length - 1 Length of string -1 becouse we have to make room for null character '\0'
	//			)
	sprintf_s(format, sizeof(format), "%%%ds", str_length - 1);
	result = scanf(format, str);
	return result;
}

int input_string_safely(char* str, unsigned int str_length) {
	char format[64];
	int result = 0;

	sprintf_s(format, sizeof(format), "%%%ds", str_length - 1);
	result = scanf_s(format, str, str_length);
	return result;
}

int input_int(int* p_number) {
	int result = 0;
	result = scanf("%d", p_number);
	return result;
}

int input_int_safely(int* p_number) {
	int result = 0;
	result = scanf_s("%d", p_number);
	return result;
}

int input_double(double* p_number) {
	int result = 0;
	result = scanf("%lf", p_number);
	return result;
}

int input_double_safely(double* p_number) {
	int result = 0;
	result = scanf_s("%lf", p_number);
	return result;
}

int main() {
	int number_of_students = 0;

#ifdef SAFE_MODE
	printf("Using SAFE_MODE\n");
	printf("How many students whoud you like to create: \n");
	input_int_safely(&number_of_students);
	stdin_clear();
#else 
	printf("Not Using SAFE_MODE\n");
	printf("How many students whoud you like to create: \n");
	input_int(&number_of_students);
	stdin_clear();
	
#endif
	Student* students = malloc(sizeof(Student) * number_of_students);
	if (students == NULL) {
		printf("Failed to allocate memory");
		return 1; // Exit if memory allocation fails
	}

	for (int i = 0; i < number_of_students; i++) {
		input_student_data(&students[i]);
	}
	all_print(students, number_of_students);
	free(students);
	students = NULL;
}

#undef SAFE_MODE
