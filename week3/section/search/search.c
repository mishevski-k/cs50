#include <cs50.h>
#include <stdio.h>

typedef struct {
    string name;
    int votes;
} candidate;

int main(void)
{
    const int num_candidates = 3;
    candidate candidates[num_candidates];

    candidates[0].name = "Carter";
    candidates[0].votes = 10;   

    candidates[1].name = "Yuliia";
    candidates[1].votes = 12;   

    candidates[2].name = "Inno";
    candidates[2].votes = 7;  

    candidate winner;
    winner.name = "";
    winner.votes = 0;

    for(int i = 0; i < num_candidates; i++)
    {
        if(candidates[i].votes > winner.votes)
        {
            winner = candidates[i];
        }
    } 

    printf("Winner: %s, with %i votes", winner.name, winner.votes);
}