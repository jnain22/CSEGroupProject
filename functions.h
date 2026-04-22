#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// Functions for handling calculations
float conversion(int height_ft, int height_inch, int conv);

float bmi(float weight, int height_ft, int height_inch);

float bmr(float weight, int height_ft, int height_inch, int age, int gender);



//Functions for getting the date
void getdate(int *day, int *month, int *year);



//Funtions for recording food and daily calories
void record_food(int cals, int user_id, char *food_name);

void record_daily(int cals, int user_id);



//Functions for showing recorded history
void foodhistory(int id, int day, int month, int year);

void dayhistory(int id, int month, int year);

void min_cals(int id, int month, int year);

void max_cals(int id, int month, int year);




//Functions for handling userprofiles
int user_record(char *name, char *gender, int height_ft, int height_inch, int age, float weight);

int show_profile(char *name);

void makeprofile();


#endif 