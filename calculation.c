#include "calculation.h"

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






float bmi(float weight, int height_ft, int height_inch)
{
    float height = conversion(height_ft, height_inch, 1); //1 means feet and inch to meter
    float result = weight / (height * height);

    return result;
}




float bmr(float weight, int height_ft, int height_inch, int age, int gender)
{
    float result = 0;
    float height = conversion(height_ft, height_inch, 0); //0 means feet and inch to cm

    switch(gender) //0 will equal to male and 1 will equal to female
    {
        case 0: result = (10 * weight) + (6.25 * height) - (5 * age) + 5; break;
        case 1: result = (10 * weight) + (6.25 * height) - (5 * age) - 161; break;

        default: return -1; break;
    }
    return result;
}




