


#define _CRT_SECURE_NO_WARNINGS  /*hide errors*/

#include <stdio.h>     /*reqs something for file openings*/
#include<string.h>

typedef struct student {   //well make an array of structs to hold the lines we read

	char lastname[25];
	char firstname[25];
	int ID;
	double GPA;

}Student;    //typedef allows us to not declare instances with "struct Student", but only "student"




int main(void) {

	enum cars{ BMW, Honda, Toyota };

	enum cars j;

	j = BMW;

	int non_pointer = 1004;
	int *pointer = &non_pointer;

	printf(non_pointer);
	printf(pointer);
	printf(*pointer);
	printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHh");










	if NULL{




		FILE* infile = fopen("data.csv", "r");   /*try to open file*/
		char line[100] = "";   //this is iffy as a line could be > 100 char. We init line[0] to '\0' null
		Student studentData[100] = { {"", "", 0, 0.0} }; //set the first? array index to default Student we can hold 100 students
		int lineCoutn = 0;

		if (infile != NULL) {  /*check if the file opened or not*/


			//1: read header line
			fgets(line, 100, infile);    //name of an array in C is the address of the first array index
			puts(line);
			//If array contiguous, add 1 to address to get to next index

			//read data lines
			//read data lines
			while (fgets(line, 100, infile) != NULL) {  //while we have lines to read, fgets not returning null 
				puts(line);


				/*
				store the line into the struct at current index in proper places.
				strtok () to parse a line; .csv file
				*/







			}
			fclose(infile);//close our file.


		}	
	}//if null

	//return 0;
}

/*reading from a file is inefficient compared to memory. Line-by-line > value by value becuase
it's easier to handle a mallfoermed line with an algorighmn than have an algo for grabbing vaues.*/

/*learn why we use ruleset when making txt files*/
/* doubele vs single quotes*/
