# TODO
from cs50 import get_string
# get number as string which then can get length of with len()
number = get_string("Number: ")
length = len(number)
n = int(number)
sum = 0
# loop through number and chop off each number to be analyzed
for i in range(length):
    rem = n % 10
    # multiply every other digit by 2, starting with the number's second to last digit
    # add these digits together
    if i % 2 != 0:
        calc = int(rem) * 2
        # if number is 2 digits then add the digits together
        if (calc > 9):
            calc2 = int(calc % 10) + int((calc / 10))
            sum = sum + calc2
        else:
            sum = sum + calc
    # if even number of i then just add number to the sum
    elif i % 2 == 0 or i == 0:
        sum = sum + rem
    # save the first 2 digits of the number
    if i == length - 2:
        first2 = int(n)
    # save number as number with last digit chopped off
    n = int(n / 10)

if int(sum % 10) == 0 and (first2 == 34 or first2 == 37) and length == 15:
    print("AMEX")
elif int(sum % 10) == 0 and first2 >= 40 and first2 <= 49 and (length == 13 or length == 16):
    print("VISA")
elif int(sum % 10) == 0 and first2 >= 51 and first2 <= 55 and length == 16:
    print("MASTERCARD")
else:
    print("INVALID")