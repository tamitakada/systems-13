#include "data.h"
#include <stdio.h>

int main() {
    read_csv("nyc_pop.csv");
    
    printf("Reading data first time ===================================\n");
    read_data();
    
    add_data();
    
    printf("\nReading data with new entry ===================================\n");
    read_data();
}
