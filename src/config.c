#include <stdio.h>
#include <string.h>

#define MAX_PROGRAMS 100
#define MAX_NAME_LENGTH 256

// Function to read programs from the config file
int read_config(const char *filename, char programs[MAX_PROGRAMS][MAX_NAME_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open config file");
        return -1;
    }

    int i = 0;
    while (fgets(programs[i], MAX_NAME_LENGTH, file) != NULL) {
        // Remove newline character at the end of the program name
        programs[i][strcspn(programs[i], "\n")] = '\0';
        i++;
        if (i >= MAX_PROGRAMS) break;  // Avoid overflow
    }

    fclose(file);
    return i;  // Return the number of programs read
}

