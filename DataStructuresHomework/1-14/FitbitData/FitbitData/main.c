//Jared Kelnhofer, 1/15/22 CPT_S 122 HW no 1.

#include "header.h"            

int main(void) {

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
        printf(first_entry.patient);

        while(counter < 1440 && fgets(line, 100, data)) {   //going to use "while" becasue we won't add records that don't match the target patient.  Note that this executes fgets, and advances line to the next, well, line.
            
            FitbitData record = parse_to_fitbit(line);

            if (matches_id(first_entry, record)) {//put record in day array, if the id matches. otherwise ignore it.
                dayRecord[counter] = record;
                counter++;

            }
        }     
    }
    return 0;
}