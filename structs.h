#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct 
{
    int id;
    int age;
    int height_ft;
    int height_inch;
    float weight;
    float bmi;
    float bmr;
    char gender[10]; //Will do a strcmp with string input and set to 0 if male or 1 if female
    char username[100];
}user;



typedef struct 
{
    int id;
    int calrecord;
    int day;
    int month;
    int year;
}daily;



typedef struct
{
    int id;
    int cal;
    char name[100];
    int day;
    int month;
    int year;
}food;


#endif 