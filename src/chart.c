#include <ncurses.h>
#include "chart.h"
#include <string.h>
void initNcurses() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color(); // Enable color support
    curs_set(0);  // Hide cursor

    // Define color pairs
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);}

void drawBarChart(int data[], int num_data, int chart_width, char process_name[256]) {
    // Draw the bar chart
    int total_width = 0;
    for (int i = 0; i < num_data; i++) {
        attron(COLOR_PAIR(i + 1)); // Set color based on data point
        int data_width = (data[i] * chart_width) / 100;
        for (int j = 0; j < data_width; j++) {
            mvaddch(1, total_width + j + strlen(process_name) + 2, '='); // Draw visible bar segment with color
        }
        attroff(COLOR_PAIR(i + 1));
        total_width += data_width;
    }
}

void drawLegend(const char process_name[256]) {
    // Print the process name
    
    mvprintw(1, 1, "%s", process_name);
    //mvprintw(1, (COLS - len) / 2, "%s", process_name);
}

void drawTime(int hours, int minutes, int distance){
    //length of the legend text
    mvprintw(1, distance, "%d:%d", hours, minutes);
}

void endNcurses() {
    // End ncurses
    endwin();
}
