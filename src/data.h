#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef DATA_H
#define DATA_H

typedef struct {
    int ghours;
    int gminutes;
    int gseconds;
} Hms;

extern Hms hms;

#endif
