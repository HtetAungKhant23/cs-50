// #include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char* name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char* name);
void print_winner(void);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = 3;
    printf("Number of voters: %d\n", voter_count);

    char *fakeVote = "One";
    char *fakeVote2 = "One";
    char *fakeVote3 = "Two";

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char *input = i == 0 ? fakeVote : i == 1 ? fakeVote2 : fakeVote3;
        // Check for invalid vote
        if (!vote(input))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
    return 0;
}

// Update vote totals given a new vote
bool vote(char* name)
{
    int same = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        int x = 0;
        while (candidates[i].name[x] != '\0')
        {
            if(candidates[i].name[x] != name[x]){
                same = 0;
                break;
            }
            same = 1;
            x++;
        }
        if(same){
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int x = 0;
        while (x < candidate_count - 1)
        {
            if (candidates[x].votes > candidates[x+1].votes)
            {
                candidate temp = candidates[x + 1];
                candidates[x + 1] = candidates[x];
                candidates[x] = temp;
            }
            x++;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == candidates[candidate_count-1].votes){
            printf("%s\n", candidates[i].name);
        }
    }
}