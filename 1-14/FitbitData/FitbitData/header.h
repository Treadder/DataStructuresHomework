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
    char patient[5];
    char minute[9];
    double calories;
    double distance;
    unsigned int floors;
    unsigned int heartRate;
    unsigned int steps;
    Sleep sleepLevel;

} FitbitData;

//++++++++++++++++++++++++++++++++++++++++++++FUNCTIONS FOR CSV FILE++++++++++++++++++++++++++++++++++    

FitbitData parse_to_fitbit(char record[100])
{
    FitbitData blank = { "0000", "00000000", 0.0, 0.0, 0, 0, 0, NONE };

    FitbitData return_struct = blank;

    char *pointer = strtok(record, ",");
    int counter = 0;

    while (pointer)
    {
        //if string is empty, leave default value in place

        if (pointer[0] != "\0") {  //thanks to https://stackoverflow.com/questions/15485179/how-to-check-if-c-string-is-empty  answer by nabroyan

            switch (counter) {                                 //assign each slice of the string to it's proper place depenging on the counter.

            case 0:
                
                for (int i = 0; i < strlen(pointer); i++) {    //disastrously dirty and horrible, but I'm running low on time so...
                    
                    return_struct.patient[i] = pointer[i];
                }
                return_struct.patient[strlen(pointer)] = 0;    //terminate the string
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
                return_struct.floors = (unsigned int)pointer;
                break;
            case 5:
                return_struct.heartRate = (unsigned int)pointer;
                break;
            case 6:
                return_struct.steps = (unsigned int)pointer;
                break;
            case 7:
                return_struct.sleepLevel = (Sleep)pointer;
                break;
            }
        }
        pointer = strtok(NULL, ",");
        counter++;
    }
    if (counter < 7) { //check if there were missing commas (so, missing fields.) Return default struct if so, as values could have been modified up to the last, and un-sevenly comma.

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


unsigned int max_minute_steps(FitbitData input_arr[1440]) {

    unsigned int total = 0;

    for (int i = 0; i < 1440; i++) {
        if (input_arr[i].steps >= total) {
            total = input_arr[i].steps; 
        }
    }
    return total;
}
/*
void replacestr(char *a[9], char *b[9]) {         //TODO it's broken!

    for (int j = 0; j < 9; j++) {
        
        (*a)[j] = '7';//(*b)[j];
    }
}
*/

void worst_sleep_range(FitbitData input_arr[1440], char *start_minute[9], char *end_minute[9]){//accepts a pointer to an array which to modify. It'll be 2d, so [2][9] and hold 2 minutes, start and end. 

    char tentative_start_minute[9] = { '0', '0', '0', '0', '0', '0', '0', '0', '\0' };
    char tentative_end_minute[9] = { '0', '0', '0', '0', '0', '0', '0', '0', '\0' };

    unsigned int biggest_count = 0;
    unsigned int current_count = 0;

    bool counting = false;

    for (int i = 0; i < 1440; i++) {

        if (input_arr[i].sleepLevel > 1)
        {

            if (counting) //we're counting in the middle of a stream of bad sleep. We need to continue counting up the bad sleep, let the counting continue, and not meddle with the tentative start/ends.
            {
                current_count += input_arr[i].sleepLevel;

            }

            else//we're hitting the start of a stream of bad sleep, and are not counting yet. We need to update tentative start string and begin counting sleep level in total for this stream.
            {

                counting = true;
                
                //replacestr(&tentative_start_minute, &input_arr[i].minute);
                for (int j = 0; j < 9; j++) {
                    tentative_start_minute[j] = input_arr[i].minute[j];
                }


                current_count += input_arr[i].sleepLevel;
            }
        }

        else
        {
            if (counting) //we're at the end of a stream of bad sleep, and need to stop counting. We need to update the tentative final minute, and check if the total sleep score was greater or eql to greatest total counts, 
            {

                counting = false;

                //replacestr(&tentative_end_minute, &input_arr[i].minute);
                for (int j = 0; j < 9; j++) {
                    tentative_end_minute[j] = input_arr[i].minute[j];
                }

                if (current_count >= biggest_count)//we've found the current biggest, or equal and newest ream of bad sleep. Update biggest total count, start and end minute. and set current count to 0
                {
                    biggest_count = current_count;
                   // replacestr(&start_minute, &tentative_start_minute);
                    for (int j = 0; j < 9; j++) {
                        //printf(start_minute);
                        printf("F");
                        printf(input_arr[i].minute);
                        start_minute[j] = input_arr[i].minute[j];
                    }

                    //replacestr(&end_minute, &tentative_end_minute);
                    for (int j = 0; j < 9; j++) {
                        end_minute[j] = input_arr[i].minute[j];
                    }
                    current_count = 0;
                }
                else//we found a stream of bad sleep that wasn't bigger than the biggest one we had seen, or even equal to it. We need to set current_count to zero to prep for next stream.
                {
                    current_count = 0;
                }
            }

            else
            {
                //we're in the middle of a stream of good sleep and are not counting. Nothing needs to happen.
            }
        }
    }
}
