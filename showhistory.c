#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "showhistory.h"


void foodhistory(int id, int day, int month, int year)
{
    food var;
    FILE *fp = fopen("food_record.dat", "r+b");

    while(fread(&var, sizeof(food), 1, fp) == 1)
    {
        if (var.id == id && var.day == day && var.month == month && var.year == year)
        {
            printf("\n%s | %d | %d/%d/%d\n", var.name, var.cal, var.day, var.month, var.year);
        }
    }
    fclose(fp);
}


void dayhistory(int id, int month, int year)
{
    daily var;

    FILE *fp = fopen("daily_record.dat", "r+b");

    while(fread(&var, sizeof(daily), 1, fp) == 1)
    {
        if (var.id == id && var.month == month && var.year == year)
        {
            printf("\n%d | %d/%d/%d\n", var.calrecord, var.day, var.month, var.year);
        }
    }

    fclose(fp);
}