#include <stdio.h>
#include "../../lib/cs50.h"

int main(void){

    string first_name = get_string("What's your first name? ");
    string last_name = get_string("What's your last name? ");
    int age = get_int("How old are you? ");
    string phone_number = get_string("What's your phone number ");

    printf("First name: %s\nLast name: %s\nAge: %i\nPhone number %s\n", first_name, last_name, age, phone_number);
}