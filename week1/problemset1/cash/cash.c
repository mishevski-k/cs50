#include <cs50.h>
#include <stdio.h>
int calcualte_coins_amount(int coin_value, int amount);

int main(void)
{
    int owed;

    do
    {
        owed = get_int("Change owed: ");
    }
    while(owed < 1);

    int total_coins = 0;

    if (owed >= 25)
    {
        int quarters = calcualte_coins_amount(25,owed);
        owed = owed % (quarters * 25);
        total_coins += quarters;
    }

    if (owed >= 10)
    {
        int dimes = calcualte_coins_amount(10, owed);
        owed = owed % (dimes * 10);
        total_coins += dimes;
    }

    if (owed >= 5)
    {
        int nickels = calcualte_coins_amount(5, owed);
        owed = owed % (nickels * 5);
        total_coins += nickels;
    }

    if (owed >= 1)
    {
        int pennies = calcualte_coins_amount(1, owed);
        owed = owed % (pennies * 1);
        total_coins += pennies;
    }

    printf("%i", total_coins);
}

int calcualte_coins_amount(int coin_value, int amount)
{
    return amount / coin_value;
}