#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int get_process_id(const char* process_name, char* process_pid) {
    char command[512];
    snprintf(command, sizeof(command), "ps -C %s -o pid=", process_name);
    FILE* fp_pid = popen(command, "r");
    if (fp_pid == NULL) {
        printf("Failed to execute 'ps' command\n");
        return 1;
    }
    if (fgets(process_pid, 256, fp_pid) != NULL) {
        process_pid[strcspn(process_pid, "\n")] = '\0';
    }
    pclose(fp_pid);
    return 0;
}

int capture_process_start_time(const char* process_pid, char* start_time, size_t start_time_size) {
    char command_start[512];
    snprintf(command_start, sizeof(command_start), "ps -p %s -o start=", process_pid);
    FILE* fp_start_time = popen(command_start, "r"); // Execute 'ps' command with captured PID and capture start time
    if (fp_start_time == NULL) {
        printf("Failed to execute 'ps' command with captured PID\n");
        return 1;
    }
    if (fgets(start_time, start_time_size, fp_start_time) != NULL) {
        // Remove trailing newline character from the captured output
        start_time[strcspn(start_time, "\n")] = '\0';
    }
    pclose(fp_start_time);
    return 0;
}



int get_current_time(char* current_time, size_t current_time_size) {
    char buffer[128]; // Buffer to hold the output of the shell command
    FILE* pipe = popen("date +\"%H:%M:%S\"", "r"); // Execute shell command to get date and time
    if (pipe == NULL) {
        printf("Failed to execute shell command.\n");
        return 1;
    }

    if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(current_time, buffer, current_time_size - 1); // Copy the current time to the provided buffer
    } else {
        printf("Failed to get current time from shell command.\n");
    }

    pclose(pipe); // Close the pipe
    return 0;
}

