#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string word);
int get_word_points(char c);
bool in_array(char c, const char array[], int size);

const char ten_points_array[2] = {'Z', 'Q'};
const char eight_points_array[2] = {'X', 'J'};
const char five_points_array[1] = {'K'};
const char four_points_array[5] = {'F', 'H', 'V', 'W', 'Y'};
const char three_points_array[4] = {'C', 'M', 'P', 'B'};
const char two_points_array[2] = {'D', 'G'};
const char one_point_array[10] = {'A', 'E', 'I', 'L', 'N', 'R', 'S', 'T', 'U', 'O'};

int main(void)
{
    string player_1_word = get_string("Player 1: ");
    string player_2_word = get_string("Player 2: ");

    int player_1_score = calculate_score(player_1_word);
    int player_2_score = calculate_score(player_2_word);

    if (player_1_score > player_2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player_2_score > player_1_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int calculate_score(string word)
{
    int score = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        score += get_word_points(word[i]);
    }

    return score;
}

int get_word_points(char c)
{
    c = toupper(c);

    int points = 0;

    if (in_array(c, one_point_array, 10))
    {
        points = 1;
    }
    else if (in_array(c, four_points_array, 5))
    {
        points = 4;
    }
    else if (in_array(c, three_points_array, 4))
    {
        points = 3;
    }
    else if (in_array(c, ten_points_array, 2))
    {
        points = 10;
    }
    else if (in_array(c, eight_points_array, 2))
    {
        points = 8;
    }
    else if (in_array(c, two_points_array, 2))
    {
        points = 2;
    }
    else if (in_array(c, five_points_array, 1))
    {
        points = 5;
    }

    return points;
}

bool in_array(char c, const char array[], int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        if (c == array[i])
        {
            return true;
        }
    }

    return false;
}
