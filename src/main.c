//TODO: ADD DATABASE (sqllite)
#include "../src/main.h"
#include "../src/data.h"
#include "../src/graph.h"
Hms hms;

#define MAX_PROGRAMS 100
#define MAX_NAME_LENGTH 256
#define MAX_BAR_WIDTH 50


int main() {

    char programs[MAX_PROGRAMS][MAX_NAME_LENGTH];
    int num_programs = read_config("config.txt", programs);

    if (num_programs == -1) {
        return 1;  // Exit if there was an error reading the config file
    }

    for (int i = 0; i < num_programs; i++) {
//        printf("Tracking: %s\n", programs[i]);

        // Process ID and time tracking for each program
        char process_pid[256];
        int result = get_process_id(programs[i], process_pid);
        if (result == 0) {
//            printf("Process ID of %s: %s\n", programs[i], process_pid);
        }

        char start_time[256];
        if (capture_process_start_time(process_pid, start_time, sizeof(start_time)) == 0) {
//            printf("Start time of %s: %s\n", programs[i], start_time);
        } else {
//            printf("Failed to capture start time for %s\n", programs[i]);
        }

        char current_time[128];
        if (get_current_time(current_time, sizeof(current_time)) == 0) {
//            printf("Current time: %s\n", current_time);
        } else {
            printf("Failed to get current time.\n");
        }

        // Calculate the time spent on the process
        int hour1, minute1, second1;
        sscanf(start_time, "%d:%d:%d", &hour1, &minute1, &second1);

        int hour2, minute2, second2;
        sscanf(current_time, "%d:%d:%d", &hour2, &minute2, &second2);    

        int time1 = hour1 * 3600 + minute1 * 60 + second1;
        int time2 = hour2 * 3600 + minute2 * 60 + second2;
        int timeDifference = time2 - time1;

        hms.ghours = timeDifference / 3600;
        hms.gminutes = (timeDifference % 3600) / 60;
        hms.gseconds = timeDifference % 60;

   //     printf("Usetime for %s: %d hours, %d minutes, %d seconds\n", programs[i], hms.ghours, hms.gminutes, hms.gseconds);
 
        print_graph(programs[i], hms.ghours, hms.gminutes, hms.gseconds);

    }


    return 0;
}

