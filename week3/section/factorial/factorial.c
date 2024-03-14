#include <cs50.h>
#include <stdio.h>

int get_factorial(int number);

int main(void)
{
    int number;

    do
    {
        number = get_int("Number: ");
    }
    while(number < 1 && number > 10);

    printf("Factorial: %i", get_factorial(number));
}

int get_factorial(int number)
{
    if(number == 1){
        return number;
    }

    return number * get_factorial(number - 1);
}