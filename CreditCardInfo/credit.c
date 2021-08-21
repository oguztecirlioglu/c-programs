#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    /*  First need to get the credit card number  */

    long card = get_long("Number: ");
    int count = 1;
    int evensum = 0;
    int oddsum = 0;
    long FirstDigit = card;
    long secondDigit = card;

    if ((floor(log10(labs(card))) + 1) < 13)
    {
        printf("INVALID\n");
        exit(EXIT_SUCCESS);
    }

    while (FirstDigit >= 10)
  	{
  		FirstDigit = FirstDigit / 10;
	}

	while (secondDigit >= 100)
  	{
  		secondDigit = secondDigit / 10;
	}

    while (card > 0)
    {
        if (count % 2 == 0)
        {
            if (2 * (card % 10) >= 10)
            {
                int tempnum = 2 * (card % 10);
                evensum += (tempnum % 10);
                tempnum /= 10;
                evensum += tempnum;
            }
            else
            {
                evensum += 2*(card % 10);
            }
        }
        else
        {
            oddsum += card % 10;
        }

        count++;
        card /= 10;
    }

    bool legit;

    legit = ((oddsum + evensum) % 10 == 0) ? 1 : 0;

    if(legit)
    {
        if(FirstDigit == 4)
        {
            printf("VISA\n");
        }
        else if(secondDigit == 51 || secondDigit == 52 || secondDigit == 53 || secondDigit == 54 || secondDigit == 55)
        {
            printf("MASTERCARD\n");
        }
        else if(secondDigit == 34 || secondDigit == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }


}
