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

void read_data() {
    struct stat stats;
    stat("pop_data", &stats);
    
    int len = stats.st_size / sizeof(struct pop_entry);
    struct pop_entry entries[len];
    
    int file = open("pop_data", O_RDONLY, 0);
    
    read(file, entries, stats.st_size);
    
    int i;
    for (i = 0; i < len; i++) {
        printf("Entry | Year: %d, Population: %d, Borough: %s\n", entries[i].year, entries[i].population, entries[i].boro);
    }
}

void write_file(struct pop_entry *entries, int len) {
    int file = open("pop_data", O_CREAT | O_WRONLY, 0644);
    write(file, entries, sizeof(struct pop_entry) * len);
    close(file);
}

void read_csv(char *file_path) {
    int csv_file = open(file_path, O_RDONLY, 0);
    
    struct pop_entry all_entries[1000];
    int index = 0;
    
    if (csv_file >= 0) {
        char buffer;
        int bytes_read = read(csv_file, &buffer, sizeof(char));
        
        char line[1000];
        char l_index = 0;
        
        int lines_read = 0;
        
        char boro_names[5][100] = {
            "Manhattan",
            "Brooklyn",
            "Queens",
            "Bronx",
            "Staten Island"
        };
        
        while (bytes_read) {
            if (buffer == '\n') {
                if (lines_read > 0) {
                    line[l_index] = '\0';
   
                    int year;
                    int boro_pops[5];
                    
                    sscanf(
                        line,
                        "%d,%d,%d,%d,%d,%d",
                        &year,
                        &boro_pops[0],
                        &boro_pops[1],
                        &boro_pops[2],
                        &boro_pops[3],
                        &boro_pops[4]
                    );
                    
                    int i;
                    for (i = 0; i < 5; i++) {
                        struct pop_entry pop;
                        pop.year = year;
                        pop.population = boro_pops[i];
                        strcpy(pop.boro, boro_names[i]);
                        all_entries[index] = pop;
                        
                        index++;
                    }
                }
                
                l_index = 0;
                lines_read++;
                bytes_read = read(csv_file, &buffer, sizeof(char));
            } else {
                line[l_index] = buffer;
                l_index++;
                bytes_read = read(csv_file, &buffer, sizeof(char));
            }
        }
        
        write_file(all_entries, index);
    }
}
