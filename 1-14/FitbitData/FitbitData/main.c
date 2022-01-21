//Jared Kelnhofer, 1/15/22 CPT_S 122 HW no 1.

#include "header.h"            

int main(void) {

    //TESTS
    
    FILE* data1 = fopen("TestStruct.csv", "r");

    if (!data1) {
        printf("File was not opened successfully!");
    }
    else {
        char line1[100];
        printf(fgets(line1, 100, data1)); //next line should be header
        printf("\n\n");

        FitbitData test_struct = parse_to_fitbit(line1);
        printf("%s%spatient: ", test_struct.patient, "\n");
        printf("%f%scalories: ", test_struct.calories, "\n");


        printf("\n\n\n");



        /*  char patient[10];
    char minute[9];
    double calories;
    double distance;
    unsigned int floors;
    unsigned int heartRate;
    unsigned int steps;
    Sleep sleepLevel;*/

    }
    
    
    
    
    










    FitbitData dayRecord[1440] = { {"000000000", "00000000", 0.0, 0.0, 0, 0, 0, NONE} };     //stores 1 day of minute entries. Init with default struct for all entries.

    FILE* data = fopen("FitbitData.csv", "r");

    if (!data) {
        printf("File was not opened successfully!");
    }
    else {
        char line[100];
        int counter = 0;
       
        printf(fgets(line, 100, data)); //first line should be target
        printf(fgets(line, 100, data)); //next line should be header
        
        FitbitData first_entry = parse_to_fitbit(fgets(line, 100, data));  //next line should be first record              
        printf("%s%s\n", "patient ID: ", first_entry.patient);

        while(counter < 1440 && fgets(line, 100, data)) {   //going to use "while" becasue we won't add records that don't match the target patient.  Note that this executes fgets, and advances line to the next, well, line.
            
            FitbitData record = parse_to_fitbit(line);

            if (matches_id(first_entry, record)) {//put record in day array, if the id matches. otherwise ignore it.
                dayRecord[counter] = record;
                counter++;

            }
        } 
        // NOW THAT dayvalue is populated we can check out some data from it

        printf("%s%f\n", "calories: ", total_calories(dayRecord));
        printf("%s%f\n", "miles walked: ", total_miles_walked(dayRecord));
        printf("%s%u\n", "floors walked: ", total_floors_walked(dayRecord));
        printf("%s%u\n", "steps taken: ", total_steps_taken(dayRecord));
        printf("%s%f\n", "avg heart rate: ", avg_heart_rate(dayRecord));
        printf("%s%u\n", "max steps taken in 1 min: ", max_minute_steps(dayRecord));

        char start_minute[9] = { '0', '0', '0', '0', '0', '0', '0', '0', '\0' };
        char end_minute[9] = { '0', '0', '0', '0', '0', '0', '0', '0', '\0' };


        //worst_sleep_range(dayRecord, &start_minute, &end_minute);

        //printf("%s%s\n", "first min of worst sleep range: ", start_minute);
        //printf("%s%s\n", "last min of worst sleep range: ", end_minute);

    }
    return 0;
}