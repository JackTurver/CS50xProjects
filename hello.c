// need cs50 package as this includes the string function
#include <stdio.h>
#include <cs50.h>

int main(void)
{
   // string name to specify the type of data type
   string name = get_string("What's your name? ");

   // printf %s as we want to include the string in the response
   printf("hello, %s\n", name);
}