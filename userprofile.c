#include <stdio.h>
#include <string.h>
#include "userprofile.h"
#include "structs.h"
#include "calculation.h"



/*This program will handle creating, saving and showing user profiles*/




int user_record(char *name, char *gender, int height_ft, int height_inch, int age, float weight)
{
    //Assigning values to user from input
    user new;
    new.height_ft = height_ft; new.height_inch = height_inch;
    new.weight = weight; new.age = age;
    new.bmi = bmi(weight, height_ft, height_inch);
    strcpy(new.username, name); strcpy(new.gender, gender);
    if (strcmp(new.gender, "male"))
    {

        new.bmr = bmr(weight, height_ft, height_inch, age, 0);
    }
    else 
    {
        new.bmr = bmr(weight, height_ft, height_inch, age, 1);
    }

    if (new.bmi == -1 || new.bmr == -1)
    {
        printf("ERROR: BMI/BMR CALCULATION ERROR!\n");
        return -1; //A return of -1 means an error occurred
    }

    //Saving the user profile in users.dat file
    FILE *fp = fopen("users.dat", "r+b");
    if (fp == NULL)
    {
        fp = fopen("users.dat", "a+b"); //Append+binary mode, creates file if file doesn't exist
        new.id = 1;
        fwrite(&new, sizeof(user), 1, fp);
        fclose(fp);
        return 0; // A return of zero means successul execution, the caller function will check this for simple error handling
    }
    else 
    {
        user old;
        fseek(fp, -1 * (long)sizeof(user), SEEK_END); //Checks the last added user in the users.dat file
        fread(&old, sizeof(user), 1, fp);
        new.id = old.id ++; //The new user is assigned an id by incrementing 1 into the id of last user
        fwrite(&new, sizeof(user), 1, fp); //Writes in the new user
        fclose(fp);
        return 0;
    }
}





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
            printf("Name: %s\nID: %d\tAge: %d\tHeight: %dft %din\nWeight: %.2f\nBMI: %.2f\tBMR: %.2f\n",profile.username, profile.id, profile.age, profile.height_ft, profile.height_inch, profile.weight, profile.bmi, profile.bmr);
        }
    }
    fclose(fp);
    return 0;
}




void makeprofile()
{
    char name[100];
    char gender[10];
    int age; float weight; int ft, in;
    printf("Input name: "); fgets(name, sizeof(name), stdin);
    printf("Gender: "); fgets(gender, sizeof(gender), stdin);
    printf("Input age: "); scanf("%d",&age);
    printf("Input weight (kg): "); scanf("%f",&weight);
    printf("Input height (ft and inches): "); scanf("%d %d",&ft, &in);

    int val = user_record(name, gender, ft, in, age, weight);

    if (val == 0)
    {
        printf("New profile created successfully!\n");
        show_profile(name);
    }
    else 
    {
        printf("ERROR: Could not create new profile\n");
    }
}