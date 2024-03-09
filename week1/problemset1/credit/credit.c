#include <cs50.h>
#include <stdio.h>

int calcualte_first_line_sum(long long number);
int calculate_second_line_sum(long long number);
void print_validation_message(bool isValid, long long number);
int get_card_start_digits(long long number);
int get_card_number_lenght(long long number);

int main(void)
{
    long long card_number;

    do
    {
        card_number = get_long_long("Number: ");
    }
    while (card_number < 1);

    int total_digit_sum = 0;

    total_digit_sum +=
        calcualte_first_line_sum(card_number) + calculate_second_line_sum(card_number);

    bool isValid = (total_digit_sum % 10) == 0;

    print_validation_message(isValid, card_number);
}

void print_validation_message(bool isValid, long long number)
{
    if (isValid)
    {
        string card_provider;
        int start_numbers = get_card_start_digits(number);
        int card_length = get_card_number_lenght(number);

        if ((start_numbers == 34 || start_numbers == 37) && card_length == 15)
        {
            card_provider = "AMEX";
        }
        else if ((start_numbers == 51 || start_numbers == 52 || start_numbers == 53 ||
                  start_numbers == 54 || start_numbers == 55) &&
                 card_length == 16)
        {
            card_provider = "MASTERCARD";
        }
        else if (((start_numbers / 10) == 4) && (card_length == 13 || card_length == 16))
        {
            card_provider = "VISA";
        }
        else
        {
            card_provider = "INVALID";
        }

        printf("%s\n", card_provider);
    }
    else
    {
        printf("INVALID\n");
    }
}

int calcualte_first_line_sum(long long number)
{
    int sum = 0;

    while (number >= 10)
    {
        number /= 10;
        int every_other_digit = (number % 10) * 2;

        if (every_other_digit >= 10)
        {
            sum += (every_other_digit % 10) + (every_other_digit / 10);
        }
        else
        {
            sum += every_other_digit;
        }
        number /= 10;
    }

    return sum;
}

int calculate_second_line_sum(long long number)
{
    int sum = 0;

    while (number >= 10)
    {
        sum += (number % 10);
        number /= 100;
    }

    if (number > 0 && number < 10)
    {
        sum += number;
    }

    return sum;
}

int get_card_start_digits(long long number)
{
    while (number > 100)
    {
        number /= 10;
    }

    return number;
}

int get_card_number_lenght(long long number)
{
    int count = 0;

    while (number > 0)
    {
        number /= 10;
        count++;
    }

    return count;
}
