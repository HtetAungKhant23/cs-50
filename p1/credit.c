#include <stdio.h>
#include <math.h>

int isValid(long creditNumber);
void describeCardName(long cardNumber);
int idx = 0;
int total = 0;


/* 
American Express uses 15-digit numbers, and start with 34 or 37
MasterCard uses 16-digit numbers, and start with 51, 52, 53, 54, or 55
Visa uses 13- and 16-digit numbers, and start with 4 
*/

int main()
{
    long creditNumber = 5199999999999991;

    if(isValid(creditNumber)){
        describeCardName(creditNumber);
    }else{
        printf("INVALID\n");
    }

    return 0;
}

int isValid(long creditNumber)
{
    if(creditNumber == 0){
        if((total % 10) == 0){
            return 1;
        }
        return 0;
    }
    if(idx % 2){
        int tempNumber = (creditNumber % 10) * 2;
        if(tempNumber > 9){
            total += tempNumber % 10 + tempNumber / 10;
        }else{
            total += tempNumber;
        }
    }
    else
    {
        total += (creditNumber % 10);
    }
    idx++;
    return isValid(creditNumber / 10);
}

void describeCardName(long cardNumber)
{
    int startNum = cardNumber / pow(10, (idx - 2));
    if(idx == 15 && (startNum == 34 || startNum == 37)){
        printf("AMEX\n");
    }else if(idx == 13 || idx == 16) {
        if (startNum >= 51 && startNum <=55){
            printf("MASTERCARD\n");
        }else if(startNum / 10 == 4){
            printf("VISA\n");
        }
    }else{
        printf("INVALID\n");
    }
}