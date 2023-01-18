#include <cs50.h>
#include <stdio.h>

// Declare the functions up at the top so that the program knows we will be using this and so we can keep them at the bottom
// This function is to calculate the number of digits of the credit number
int digits(long n);

int main(void)
{
   // Prompt user for their credit card number
   long n = get_long("Number: ");
   int number = digits(n);

   // Luhn's Algorithm
   // x variable allows us to mess with the n value in the loop while holding the number value as well of n
   long a = 0;
   int y, z, i, b;
   long x = n;
   for (i = 0; i < number; i++)
   {
      // To get the integer value of the end digit
      y = x % 10;
      // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
      if (i % 2 != 0)
      {
         z = y * 2;
         if (z > 9)
         {
            // Add the 2 digits of the number z together if its 2 digits long
            b = (z % 10) + (z / 10);
            a = a + b;
         }
         else
         {
            a = a + z;
         }
      }
      // Add the sum to the sum of the digits that weren’t multiplied by 2.
      else if (i % 2 == 0 || i == 0)
      {
         a = a + y;
      }
      // To remove the end digit and move onto next one
      x /= 10;
   }

   // p will give the first 2 digits of the card number
   long p = n;
   int j;
   int h = 0;
   for (j = 0; j < (number - 2); j++)
   {
      p /= 10;
      h = p;
   }

   // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
   // If number is less than 13 digits starting with 4 then can't be a credit number
   // Same if larger than 16 digits starting with 55 but will be 9 recurring after as this is the max valid number
   // Use a get_long not an int as it will not fit
   // American Express uses 15-digit numbers, start with 34 or 37
   // MasterCard uses 16-digit numbers, starts with 51, 52, 53, 54, or 55
   // Visa uses 13- and 16-digit numbers, start with 4
   // last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n
   if (((a % 10) == 0) && ((h == 34) || (h == 37)) && (number == 15))
   {
      printf("AMEX\n");
   }
   else if (((a % 10) == 0) && (h >= 40) && (h <= 49) && ((number == 13) || (number == 16)))
   {
      printf("VISA\n");
   }
   else if (((a % 10) == 0) && (h >= 51) && (h <= 55) && (number == 16))
   {
      printf("MASTERCARD\n");
   }
   else
   {
      printf("INVALID\n");
   }
}

int digits(long n)
{
   int count = 0;
   do
   {
      n = n / 10;
      count++;
   } while (n > 0);
   return count;
}
