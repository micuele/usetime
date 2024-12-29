#include <stdio.h>
#include "../src/data.h"

#define MAX_PROGRAMS 100
#define MAX_NAME_LENGTH 256
#define MAX_BAR_WIDTH 50


// Function to print the ASCII graph for the program's usage time
void print_graph(const char *program_name, int hours, int minutes, int seconds) {
    int total_seconds = hours * 3600 + minutes * 60 + seconds;
    int bar_width = total_seconds / 60;  // Scale: 1 `#` for each minute

    if (bar_width > MAX_BAR_WIDTH) {
        bar_width = MAX_BAR_WIDTH;  // Limit the bar width to the max
    }

    printf("%-20s | ", program_name);  // Print program name
    for (int i = 0; i < bar_width; i++) {
        printf("#");  // Print the bar
    }
    printf(" %d:%02d:%02d\n", hours, minutes, seconds);  // Print the time
}

// Function to read programs from the config file
int read_config(const char *filename, char programs[MAX_PROGRAMS][MAX_NAME_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open config file");
        return -1;
    }

    int i = 0;
    while (fgets(programs[i], MAX_NAME_LENGTH, file) != NULL) {
        programs[i][strcspn(programs[i], "\n")] = '\0'; // Remove newline character
        i++;
        if (i >= MAX_PROGRAMS) break;
    }

    fclose(file);
    return i;  // Return the number of programs read
}

