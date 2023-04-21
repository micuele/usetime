#ifndef CHART_H
#define CHART_H

// Function prototypes
void initNcurses();
void drawBarChart(int data[], int num_data, int chart_width, char process_name[256]);
void drawLegend(const char process_name[256]);
void drawTime(int hours, int minutes, int distance);
void endNcurses();

#endif // CHART_H

