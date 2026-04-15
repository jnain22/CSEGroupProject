#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getdate.h"
#include "structs.h"
#include "record.h"






void record_food(int cals, int user_id, char *food_name) //Will ask the user for id when recording food
{
    int day, month, year;
    getdate(&day, &month, &year); 
    food input; 
    strcpy(input.name, food_name);
    input.cal = cals;
    input.id = user_id; 
    input.day = day; input.month = month; input.year = year;
    

    FILE *fp = fopen("food_record.dat","a+b");
    fwrite(&input, sizeof(food), 1, fp);

    fclose(fp);
}


void record_daily(int cals, int id) //Will ask the user for id when recording food
{
    int day, month, year;
    getdate(&day, &month, &year); 
    daily input;
    
    FILE *fp = fopen("daily_record.dat", "r+b");
    if (fp == NULL)
    {   
        input.id = id; input.calrecord = cals; input.day = day; input.month = month; input.year = year;
        fp = fopen("daily_record.dat", "a+b");
        fwrite(&input, sizeof(daily), 1, fp);
        fclose(fp);
        return;
    }


    fseek(fp, -1*(long)sizeof(daily), SEEK_END); //Setting the pointer to end of file
    for (int i = 1; fread(&input, sizeof(daily), 1, fp) == 1; i++)
    {
        fseek(fp, -1*i*(long)sizeof(daily), SEEK_END);
        if (input.id == id && input.day == day)
        {
            input.calrecord += cals;
            fwrite(&input, sizeof(daily), 1, fp);
            fclose(fp);
            return;
        }
        fseek(fp, -1*(i+1)*(long)sizeof(daily), SEEK_END);
    }

    input.id = id; input.calrecord = cals; input.day = day; input.month = month; input.year = year;
    fp = fopen("daily_record.dat", "a+b");
    fwrite(&input, sizeof(daily), 1, fp);
    fclose(fp);
    return;
}

