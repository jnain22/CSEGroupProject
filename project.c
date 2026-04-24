#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structs.h"



//Function for clearing input buffer in case of misinput or mixed input
void clearbuffer(void)
{
    char ch; 
    while((ch = getchar()) != '\n');
}




void mylower(char *string)
{
    for (int i = 0; string[i] != '\n'; i++)
    {
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            string[i] = string[i] + 32;
        }
    }
    string[strlen(string)-1] = '\0'; //Removing the '\n' from the string
}




//Function for getting the current date
void getdate(int *day, int *month, int *year)
{
    time_t clock = time(NULL);
    struct tm *tm_info = localtime(&clock);
    *day = tm_info -> tm_mday;
    *month = tm_info -> tm_mon + 1;
    *year = tm_info -> tm_year + 1900;
}





//Function for converting height units
float conversion(int height_ft, int height_inch, int conv)
{
    float converted_height = 0;
    /* 0 will equal to converting ft and inch to cm 
       1 will equal to converting ft and inch to meter */
    switch(conv)
    {
        case 0: converted_height = (height_ft * 30) + (height_inch * 2.54); break;
        case 1: converted_height = ((height_ft * 30) + (height_inch * 2.54))/100; break;

        default: return -1; break;
    }

    return converted_height;
}




//function for calculating bmi
float bmi(float weight, int height_ft, int height_inch)
{
    float height = conversion(height_ft, height_inch, 1); //1 means feet and inch to meter
    float result = weight / (height * height);

    if (result < 1) {return -1;}
    return result;
}





//function for calculating BMR
float bmr(float weight, int height_ft, int height_inch, int age, int gender)
{
    float result = 0;
    float height = conversion(height_ft, height_inch, 0); //0 means feet and inch to cm

    switch(gender) //0 will equal to male and 1 will equal to female
    {
        case 0: result = (10 * weight) + (6.25 * height) - (5 * age) + 5; break;
        case 1: result = (10 * weight) + (6.25 * height) - (5 * age) - 161; break;
    }

    return result;
}




//Function for recording users.
int user_record(char *name, char *gender, int height_ft, int height_inch, int age, float weight)
{
    //Assigning values to user from input
    user new;
    new.height_ft = height_ft; new.height_inch = height_inch;
    new.weight = weight; new.age = age;
    new.bmi = bmi(weight, height_ft, height_inch); mylower(gender);
    strcpy(new.username, name); strcpy(new.gender, gender);
    if (strcmp(new.gender, "male") == 0)
    {

        new.bmr = bmr(weight, height_ft, height_inch, age, 0);
    }
    else if (strcmp(new.gender, "female") == 0)
    {
        new.bmr = bmr(weight, height_ft, height_inch, age, 1);
    }
    else {
        printf("\nInvalid gender input\n");
        return -1; //a return of -1 means error occurred
    }

    //Saving the user profile in users.dat file
    FILE *fp = fopen("users.dat", "a+b");
    fwrite(&new, sizeof(new), 1, fp);
    fclose(fp);
    return 0;

}





//Function for showing profile
int show_profile(char *name)
{
    user profile;
    FILE *fp = fopen("users.dat", "r+b");

    if (fp == NULL)
    {
        return -1;
    }

    while(fread(&profile, sizeof(user), 1, fp) == 1)
    {
        if (strcmp(profile.username, name) == 0)
        {
            printf("\nName: %s\nGender: %s\nAge: %d\tHeight: %dft %din\nWeight: %.2f\nBMI: %.2f\tBMR: %.2f\n",profile.username, profile.gender, profile.age, profile.height_ft, profile.height_inch, profile.weight, profile.bmi, profile.bmr);
        }
    }
    fclose(fp);
    return 0;
}




//Function for making a new profile
void makeprofile()
{
    char name[100];
    char gender[10];
    int age; float weight; int ft, in;
    printf("Input name: "); fgets(name, sizeof(name), stdin);
    printf("Gender: "); fgets(gender, sizeof(gender), stdin);
    printf("Input age: "); scanf("%d",&age); clearbuffer();
    printf("Input weight (kg): "); scanf("%f",&weight); clearbuffer();
    printf("Input height (ft and inches): "); scanf("%d %d",&ft, &in);

    int val = user_record(name, gender, ft, in, age, weight);

    if (val == 0)
    {
        printf("\nNew profile created successfully!\n");
        show_profile(name);
    }
    else 
    {
        printf("\nERROR: Could not create new profile\n");
        return;
    }
}





//Function for recording food
void record_food(int cals, char *username, char *food_name) //Will ask the user for username when recording food
{
    int day, month, year;
    getdate(&day, &month, &year); 
    food input; 
    strcpy(input.name, food_name);
    input.cal = cals;
    strcpy(input.username, username);
    input.day = day; input.month = month; input.year = year;
    

    FILE *fp = fopen("food_record.dat","a+b");
    fwrite(&input, sizeof(food), 1, fp);

    fclose(fp);
}





//Function for recording the total calories in a day
void record_daily(int cals, char *username) //Will ask the user for username when recording food
{
    int day, month, year;
    getdate(&day, &month, &year); 
    daily input;
    
    FILE *fp = fopen("daily_record.dat", "r+b");
    if (fp == NULL)
    {   
        strcpy(input.username, username); input.calrecord = cals; input.day = day; input.month = month; input.year = year;
        fp = fopen("daily_record.dat", "a+b");
        fwrite(&input, sizeof(daily), 1, fp);
        fclose(fp);
        return;
    }


    fseek(fp, -1*(long)sizeof(daily), SEEK_END); //Setting the pointer to end of file
    for (int i = 1; fread(&input, sizeof(daily), 1, fp) == 1; i++)
    {
        fseek(fp, -1*i*(long)sizeof(daily), SEEK_END);
        if (strcmp(input.username, username) == 0 && input.day == day)
        {
            input.calrecord += cals;
            fwrite(&input, sizeof(daily), 1, fp);
            fclose(fp);
            return;
        }
        fseek(fp, -1*(i+1)*(long)sizeof(daily), SEEK_END);
    }

    strcpy(input.username, username); input.calrecord = cals; input.day = day; input.month = month; input.year = year;
    fp = fopen("daily_record.dat", "a+b");
    fwrite(&input, sizeof(daily), 1, fp);
    fclose(fp);
    return;
}






//Function for showing food history
void foodhistory(char *username, int day, int month, int year)
{
    food var;
    FILE *fp = fopen("food_record.dat", "r+b");

    if (fp == NULL)
    {
        printf("\nNo records... yet\n");
        return;
    }

    while(fread(&var, sizeof(food), 1, fp) == 1)
    {
        if (strcmp(var.username, username) == 0 && var.day == day && var.month == month && var.year == year)
        {
            printf("\n%s | Calories: %d | Date: %d/%d/%d\n", var.name, var.cal, var.day, var.month, var.year);
        }
    }
    fclose(fp);
}





//Function for showing recorded daily calorie intake from a particular month
void dayhistory(char *username, int month, int year)
{
    daily var;

    FILE *fp = fopen("daily_record.dat", "r+b");

    if (fp == NULL)
    {
        printf("\nNo records... yet\n");
        return;
    }

    while(fread(&var, sizeof(daily), 1, fp) == 1)
    {
        if (strcmp(var.username, username) == 0 && var.month == month && var.year == year)
        {
            printf("\nCalories: %d | Date: %d/%d/%d\n", var.calrecord, var.day, var.month, var.year);
        }
    }

    fclose(fp);
}






//Main menu
void main()
{
    FILE *fp = fopen("users.dat","r+b");
    if (fp == NULL)
    {
        printf("No user profile found, do you want to create a new one? (Yes or No) ");
        char response[5]; fgets(response, sizeof(response), stdin); mylower(response);
        if (strcmp(response, "yes") == 0)
        {
            makeprofile();
        }
        else if (strcmp(response, "no") == 0)
        {
            exit(0);
        }
        else {
        printf("\nInvalid Input (%s). Exiting program...", response);
        exit(-1);
        }

        
        
    }

    printf("\n\nWELCOME TO YOUR NEW CLI CALORIE TRACKING APPLICATION!\n\n");
    while(1)
    {
            int response;
            printf("\nWhat would you like to do?\n");
            printf("\n1) Add new food record\n2) Show recorded food history\n3) Show recorded daily calorie intake\n4) Add new user profile\n5) Show saved user profiles\n6) Delete saved calorie data\n7) Delete all user data\n8) Exit program\n\n >>>>>>>>>> ");
            
            scanf("%d",&response);
            clearbuffer(); //Clearing the input buffer
            switch(response)
            {
                case 1: {
                    char foodname[100]; int calories; char username[100];
                    printf("Enter food name: "); fgets(foodname, sizeof(foodname), stdin);
                    printf("Enter calories: "); scanf("%d",&calories); clearbuffer();
                    printf("Enter username: "); fgets(username, sizeof(username), stdin);

                    record_food(calories, username, foodname);
                    record_daily(calories, username);
                    break;
                }

                case 2: {
                    int day, month, year;
                    char username[100];
                    printf("Enter username: "); fgets(username, sizeof(username), stdin);
                    printf("Enter date (dd mm yyyy): "); scanf("%d %d %d",&day, &month, &year);

                    foodhistory(username, day, month, year);
                    break;
                }

                case 3: {
                    int day, month, year; char username[100];
                    printf("Enter username: "); fgets(username, sizeof(username), stdin);
                    printf("Enter date (mm yy): "); scanf("%d %d",&month, &year);

                    dayhistory(username, month, year);
                    break;
                }

                case 4: makeprofile(); break;

                case 5: {
                    FILE *fp = fopen("users.dat","r+b");
                    if (fp == NULL)
                    {printf("\nNo user data exists...\n"); break;}

                    char name[100];
                    printf("Input a profile name: "); fgets(name, sizeof(name), stdin);
                    show_profile(name); break;
                }

                case 6: remove("daily_record.dat"); remove("food_record.dat"); break;

                case 7: remove("users.dat"); break;

                case 8: exit(0); break;

                default: exit(0); break;
            }
    }
}