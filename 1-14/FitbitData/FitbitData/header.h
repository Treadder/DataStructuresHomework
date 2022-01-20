//#pragma once
#define _CRT_SECURE_NO_WARNINGS     //hide errors

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//++++++++++++++++++++++++++++++++++++++CUSTOM DATA TYPES++++++++++++++++++++++++++++++++++++++++++++

typedef enum sleep      //define the Sleep data type (enum for state) (source: handout.)
{
    NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit   //define the line-holding data type  (source: handout.)
{
    char patient[10];
    char minute[9];
    double calories;
    double distance;
    unsigned int floors;
    unsigned int heartRate;
    unsigned int steps;
    Sleep sleepLevel;

} FitbitData;

//++++++++++++++++++++++++++++++++++++++++++++FUNCTIONS FOR CSV FILE++++++++++++++++++++++++++++++++++    todo how would I make a string equaliyy checker without knowing size? this hinders reusability of code in the extreme!

FitbitData parse_to_fitbit(char record[100])
{

    FitbitData return_struct = { "000000000", "00000000", 0.0, 0.0, 0, 0, 0, NONE };

    char *pointer = strtok(record, ",");
    int counter = 0;

    while (pointer)
    {
        //CHECK IF STRING IS EMPTY: IF SO, LEAVE THE RECORDED ENTRY WITH DEFAULT VALUES. UGLY BUT EFFECTIVE.
        if (pointer[0] != "\0") {  //thanks to https://stackoverflow.com/questions/15485179/how-to-check-if-c-string-is-empty  answer by nabroyan

            switch (counter) { //assign each slice of the string to it's proper place depenging on the counter.

            case 0:
                for (int i = 0; i < strlen(pointer); i++) {  //disastrously dirty and horrible, but I'm running low on time so...
                    return_struct.patient[i] = pointer[i];
                }
                return_struct.patient[strlen(pointer)] = 0;  //terminate the string
                break;
            case 1:
                for (int i = 0; i < strlen(pointer); i++) {
                    return_struct.minute[i] = pointer[i];
                }
                return_struct.patient[strlen(pointer)] = 0;
                break;
            case 2:
                return_struct.calories = (double)*pointer;
                break;
            case 3:
                return_struct.distance = (double)*pointer;
                break;
            case 4:
                return_struct.floors = (unsigned int)*pointer;
                break;
            case 5:
                return_struct.heartRate = (unsigned int)*pointer;
                break;
            case 6:
                return_struct.steps = (unsigned int)*pointer;
                break;
            case 7:
                return_struct.sleepLevel = (Sleep)*pointer;
                break;
            }
        }
        pointer = strtok(NULL, ",");
        counter++;
    }
    if (counter < 7) {//check if there were missing commas (so, missing fields.) Return default struct if so, as values could have been modified up to the last, and un-sevenly comma.
        FitbitData blank = { "000000000", "00000000", 0.0, 0.0, 0, 0, 0, NONE };

        return blank;
    }
    return return_struct;
}

//+++++++++++++++++++++++++++++++++FUNCTIONS FOR FITBITDATA STRUCTS (GENERAL)+++++++++++++++++++++++++++++++++++++++++++++

bool matches_id(FitbitData target_record, FitbitData test_record)
{
    for (int i = 0; i < strlen(target_record.patient); i++) {
        if (target_record.patient[i] != test_record.patient[i]) {

            return false;
        }
    }
    return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++FUNCTIONS FOR WORKING WITH THE FINAL DAY ARRAY+++++++++++++++++++++++++++

//-      You must compute the total calories burned, distance walked in miles, floors walked, and steps taken            <<<<        

double total_calories(FitbitData input_arr[1440]) { //seriously annoying to have to specify size. How to make this dynamic? A global DAY_RECORD_SIZE variable seems messy.

    double total = 0.0;

    for (int i = 0; i < 1440; i++) {
        total += input_arr[i].calories;
    }
    return total;
}

double total_miles_walked(FitbitData input_arr[1440]) { 
    
    double total = 0.0;

    for (int i = 0; i < 1440; i++) {
        total += input_arr[i].distance;
    }
    return total;
}

unsigned int total_floors_walked(FitbitData input_arr[1440]) { 
    
    unsigned int total = 0;

    for (int i = 0; i < 1440; i++) {
        total += input_arr[i].floors;
    }
    return total;


}

unsigned int total_steps_taken(FitbitData input_arr[1440]) { 
    
    unsigned int total = 0;

    for (int i = 0; i < 1440; i++) {
        total += input_arr[i].steps;
    }
    return total;
}

double avg_heart_rate(FitbitData input_arr[1440]) {

    unsigned int total = 0;

    for (int i = 0; i < 1440; i++) {
        total += input_arr[i].heartRate;
    }
    return (double)total/1440;
}

