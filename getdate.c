#include <time.h>
#include "getdate.h"

void getdate(int *day, int *month, int *year)
{
    time_t clock = time(NULL);
    struct tm *time = localtime(&clock);
    *day = time -> tm_mday;
    *month = time -> tm_mon + 1;
    *year = time -> tm_year + 1900;
}