#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "record.h"
#include "showhistory.h"
#include "userprofile.h"


void main()
{
    FILE *fp = fopen("users.dat","r+b");
    if (fp == NULL)
    {
        printf("No user profile found, do you want to create a new one? (Y for yes, N for no) ");
        char response; scanf("%c",&response);
        getchar();
        if (response == 'Y')
        {
            makeprofile();
        }
        else 
        {
            exit(0);
        }

        
        
    }
    while(true)
    {
            int response;
            printf("\nWELCOME TO YOUR NEW CLI CALORIE TRACKING APPLICATION!\nWhat would you like to do?\n");
            printf("\n1. Add new food record\n2. Show recorded food history\n3. Show recorded daily calorie intake\n4. Add new user profile\n5. Show saved user profiles\n6. Exit program\n\n >>>>>>>>>> ");
            
            scanf("%d",&response);
            getchar();
            switch(response)
            {
                case 1: {
                    char foodname[100]; int calories; int id;
                    printf("Enter food name: "); fgets(foodname, sizeof(foodname), stdin);
                    printf("Enter calories: "); scanf("%d",&calories);
                    printf("Enter user ID: "); scanf("%d",&id);

                    record_food(calories, id, foodname);
                    record_daily(calories, id);
                    break;
                }

                case 2: {
                    int id, day, month, year;
                    printf("Enter user ID: "); scanf("%d",&id);
                    printf("Enter date (dd/mm/yy): "); scanf("%d %d %d",&day, &month, &year);

                    foodhistory(id, day, month, year);
                    break;
                }

                case 3: {
                    int id, day, month, year;
                    printf("Enter user ID: "); scanf("%d",&id);
                    printf("Enter date (dd/mm/yy): "); scanf("%d %d %d",&day, &month, &year);

                    dayhistory(id, month, year);
                    break;
                }

                case 4: makeprofile(); break;

                case 5: {
                    char name[100];
                    printf("Input a profile name: "); fgets(name, sizeof(name), stdin);
                    show_profile(name); break;
                }

                case 6: exit(0); break;

                default: exit(0); break;
            }
    }
}