#include <stdio.h>
// #include <cs50.h>

int main(void)
{
    // int n = 50;
    // int *p = &n;

    // printf("%i\n", *p);

    // string s = "HI!";
    char *s = "HI!";

    // printf("%s\n", s);
    // printf("%p\n", &s);
    // printf("%p\n", &s[0]);
    // printf("%p\n", &s[1]);
    // printf("%p\n", &s[2]);
    printf("%c", *s);
    printf("%c", *(s + 1));
    printf("%c\n", *(s + 2));
}