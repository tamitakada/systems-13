#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

void read_csv(char *file_path) {
  int csv_file = open(file_path, O_RDONLY, 0);
  
  struct stat stats;
  stat(file_path, &stats);
  int size = stats.st_size;
  
  if (csv_file >= 0) {
    int bytes_read = 0;
    int lines_read = 0;
    
    int index = 0;
    char buffer;

    char ***full_data = malloc(100);

    while (bytes_read < size) {
      char **all_data = malloc(100);
      char data[100];

      int a_index = 0;
      int d_index = 0;
    
      while (buffer != '\n') {
	if (buffer == ',') {
	  data[d_index] = '\0';
	  char *dest = malloc(d_index * sizeof(char));
	  strcpy(dest, data);
	  printf("%s\n", data);

	  all_data[a_index] = dest;
	
	  a_index++;
	  d_index = 0;
	}
      
	bytes_read += read(csv_file, &buffer, sizeof(char));
	printf("%c\n", buffer);
	data[d_index] = buffer;
	d_index++;
      }

      full_data[lines_read] = all_data;
      lines_read++;
    }

    /*
    int i;
    for (i = 0; i < 10; i++) {
      printf("%s\n", all_data[i]);
    }
    */
    
    // int data_file = open("data.txt", O_CREAT | O_WRONLY, 0644);
    // write(data_file, buffer, 100);
  }
}
