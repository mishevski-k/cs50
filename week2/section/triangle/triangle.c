#include <cs50.h>
#include <stdio.h>

bool valid_triangle(float x, float y, float z);

int main(void)
{
    float triangle[3];

    for(int i = 0; i < 3; i++)
    {
        triangle[i] = get_float("Side: ");
    }

    bool isValid = valid_triangle(triangle[0], triangle[1], triangle[2]);
    printf("Valid: %s\n", isValid ? "True" : "False");
}

bool valid_triangle(float x, float y, float z)
{
    // check for all positive sides
    if(x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }

    // check that sum of any two sides greater that third
    if((x + y <= z) || (y + z <= x) || (z + x <= y))
    {
        return false;
    }

    // if we passed both testes, we're good;
    return true;
}