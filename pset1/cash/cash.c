#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
    int penny = 0;
    int nickel = 0;
    int dime = 0;
    int quarter = 0;
    float owed;
    do
    {
        owed = get_float("Owed $: ");
    }    
    while (owed < 0);
    owed = round(owed * 100);
    while (owed > 0)
    {  
        while (quarter + 25 <= owed)
            //calculates if quarter should be increased or calculate with lower money variables
        {
            quarter = quarter + 25 ;
        }
        owed = owed - quarter;
        while (dime + 10 <= owed)
            //calculates if dime should be increased or calculate with lower money variables
        {
            dime = dime + 10;
        }
        owed = owed - dime;
        while (nickel + 5 <= owed)
            //calculates if nickel should be increased or calculate with lower money variables
        {
            nickel = nickel + 5;
        }
        owed = owed - nickel;
        penny = owed;//in any case owed is smaller than 5 now and pennies can be used.
        owed = owed - penny;
    }
    int Penny_given = penny;
    int nickel_given = nickel / 5;
    int dime_given = dime / 10 ;
    int quarter_given = quarter / 25;
    //above total values are divided by their money values. so quantity given is calculated.
    int result = Penny_given + nickel_given + dime_given + quarter_given;
    printf("total money quantity is %i\n", result);
    

}
