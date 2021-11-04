#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

void read_csv(char *file_path) {
  int csv_file = open(file_path, O_RDONLY, 0);
  if (csv_file >= 0) {
    int index = 0;
    char *buffer;
    char *data[100];
    
    while (strcmp(buffer, "\n") != 0) {
      if (strcmp(buffer, ",") == 0) index++;
      read(csv_file, buffer, 1);
      data[index] = buffer;
    }

    int i;
    for (i = 0; i < 10; i++) {
      printf("%s\n", data[i]);
    }
    
    // int data_file = open("data.txt", O_CREAT | O_WRONLY, 0644);
    // write(data_file, buffer, 100);
  }
}
