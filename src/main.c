//TODO: ADD DATABASE (sqllite)
#include "../src/main.h"
#include "../src/data.h"
#include "../src/chart.h"
#include <ncurses.h>
Hms hms;

int main() {
  
    char process_name[256];
    printf("Enter process name: ");
    scanf("%s", process_name);

    char process_pid[256];
    int result = get_process_id(process_name, process_pid);
    if (result == 0) {
//    printf("Process ID: %s\n", process_pid);
    }

    //Process start time using PID
    char start_time[256];
    if (capture_process_start_time(process_pid, start_time, sizeof(start_time)) == 0) {
//    printf("Process start time: %s\n", start_time);
    } else {
        printf("Failed to capture process start time\n");
    }
    
    char current_time[128];
    if (get_current_time(current_time, sizeof(current_time)) == 0) {
//    printf("Current time: %s\n", current_time);
    } else {
        printf("Failed to get current time.\n");
    }

    // Calcuates the time spent on a process
    int hour1, minute1, second1;
    sscanf(start_time, "%d:%d:%d", &hour1, &minute1, &second1);
    
    int hour2, minute2, second2;
    sscanf(current_time, "%d:%d:%d", &hour2, &minute2, &second2);
    
    // Calculate the time difference in seconds
    int time1 = hour1 * 3600 + minute1 * 60 + second1;
    int time2 = hour2 * 3600 + minute2 * 60 + second2;
    int timeDifference = time2 - time1;
    
    hms.ghours = timeDifference / 3600;
    hms.gminutes = (timeDifference % 3600) / 60;
    hms.gseconds = timeDifference % 60;
//    Print the time difference
//    printf("Usetime: %d hours, %d minutes, %d seconds\n", hms.ghours, hms.gminutes, hms.gseconds);




    // Initialize ncurses
    initNcurses();

    // Data for percentages
    int metric = (hms.ghours * 10) + (hms.gminutes / 10);
    int data[] = {metric};
    int num_data = sizeof(data) / sizeof(data[0]);

    // Calculate the width of the bar chart
    int chart_width = getmaxx(stdscr) - 2;

    // Normalize data to ensure total percentage does not exceed 100%
    int total_percentage = 0;
    for (int i = 0; i < num_data; i++) {
        total_percentage += data[i];
    }
    if (total_percentage > 100) {
        for (int i = 0; i < num_data; i++) {
            data[i] = (data[i] * 100) / total_percentage;
        }
    }

    // Main loop
    int ch;
    while ((ch = getch()) != 'q') {
        clear();

        // Draw the legend
        drawLegend(process_name);

        // Draw the bar chart
        drawBarChart(data, num_data, chart_width, process_name);

	drawTime(hms.ghours,hms.gminutes, chart_width/2);

        refresh();
    }

    // End ncurses
    endNcurses();




    return 0;
}
