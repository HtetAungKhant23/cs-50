#include <stdio.h>

void calculateCoin(int owedCents);

const int coins[] = {25, 10, 5, 1};
const int lengthOfCoins = sizeof(coins) / sizeof(int);
int counter = 0;

int main()
{
    int changeOwed = 0;

    do
    {
        changeOwed = get_int("change owed: ");
    }while(changeOwed < 0);

    calculateCoin(changeOwed);

    return 0;
}

void calculateCoin(int owedCents)
{
    if(owedCents <= 0)
    {
        printf("%i\n", counter);
        return;
    }
    for (int i = 0; i < lengthOfCoins; i++)
    {
        if(owedCents >= coins[i]) // 11
        {
            counter++;
            owedCents -= coins[i]; // 11 - 10
            calculateCoin(owedCents);
            break;
        }
    }
}