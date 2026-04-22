#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct 
{
    int age;
    int height_ft;
    int height_inch;
    float weight;
    float bmi;
    float bmr;
    char gender[10]; 
    char username[100];
}user;



typedef struct 
{
    char username[100];
    int calrecord;
    int day;
    int month;
    int year;
}daily;



typedef struct
{
    char username[100];
    int cal;
    char name[100];
    int day;
    int month;
    int year;
}food;


#endif 