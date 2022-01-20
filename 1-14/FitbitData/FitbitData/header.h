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

//++++++++++++++++++++++++++++++++++++++++++++FUNCTIONS++++++++++++++++++++++++++++++++++++++++++++++

bool matches_id(FitbitData target_record, FitbitData test_record)
{
    for (int i = 0; i < strlen(target_record.patient); i++) {
        if (target_record.patient[i] != test_record.patient[i]) {

            return false;
        }
    }
    return true;
}

FitbitData parse_to_fitbit(char record[100])
{

    FitbitData return_struct = { "000000000", "00000000", 0.0, 0.0, 0, 0, 0, NONE };

    char *pointer = strtok(record, ",");
    int counter = 0;

    while (pointer)
    {
       
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
        pointer = strtok(NULL, ",");
        counter++;

    }
    if (counter < 7) {//check if there were missing fields  and if so return default FitBitData struct. (DOESN"T CHECK FOR BLANK FIELDS)
        FitbitData blank = { "000000000", "00000000", 0.0, 0.0, 0, 0, 0, NONE };

        return blank;
    }
    return return_struct;
}
