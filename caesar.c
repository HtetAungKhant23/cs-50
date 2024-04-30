#include <stdio.h>

int checkValidInput(int inputLen,char *s);
int asciiToInt(char *ascii);
void encrypt(int step, char *plainText);

int main (int argc, char *argv[])
{
    if(checkValidInput(argc, argv[1]) == -1){
        return 1;
    }

    int step = asciiToInt(argv[1]);

    char* plainText = "This is CS50.";
    printf("plaintext: %s\n", plainText);
    encrypt(step, plainText);

    return 0;
}

int checkValidInput(int inputLen,char *s)
{
    if(inputLen != 2){
        printf("Usage: ./caesar key\n");
        return -1;
    }

    for (int i = 0; s[i] != '\0'; i++)
    {
        if(s[i] < 48 || s[i] > 57){
            printf("Usage: ./caesar key\n");
            return -1;
        }
    }
    return 1;
}

int asciiToInt(char *ascii)
{
    int res = 0;
    for (int i = 0; ascii[i] != '\0'; i++){
        res = res * 10 + ascii[i] - '0';
    }
    return res;
}

void encrypt(int step, char *plainText)
{
    int len = 0;
    while (plainText[len] != '\0')
    {
        len++;
    }
    char cipherText[len];
    for (int i = 0; i < len; i++)
    {
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            int temp = plainText[i] + step;
            cipherText[i] = temp > 'Z' ? (temp - 'Z' + '@') : temp;
        }
        else if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            int temp = plainText[i] + step;
            cipherText[i] = temp > 'z' ? (temp - 'z' + '`') : temp;
        }else{
            cipherText[i] = plainText[i];
        }
    }
    cipherText[len] = '\0';
    printf("ciphertext: %s\n", cipherText);
}