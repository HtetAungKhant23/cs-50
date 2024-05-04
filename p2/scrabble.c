#include <stdio.h>
#include <string.h>

int calculateScore(char *word);

int points[25] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4};

int main()
{
    char* word1 = "Scrabble";
    char* word2 = "wiNNeR";

    int score1 = calculateScore(word1);
    int score2 = calculateScore(word2);

    if(score1 > score2){
        printf("Player 1 win!\n");
    }else if(score1 < score2){
        printf("Player 2 win!\n");
    }else{
        printf("Tie!\n");
    }

    return 0;
}

int calculateScore(char* word){
    int totalScore = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        int upperCaseAsciiValue = (word[i] >= 'a' && word[i] <= 'z') ? (word[i] - ('a' - 'A')) : word[i];
        if(upperCaseAsciiValue >= 'A' && upperCaseAsciiValue <= 'Z'){
            totalScore += points[(upperCaseAsciiValue - 'A')];
        }
    }
    return totalScore;
}