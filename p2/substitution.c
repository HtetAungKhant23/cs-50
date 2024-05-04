#include <stdio.h>
#include <stdlib.h>

int checkValidInput(int argc, char *s);
void toUpperCase(char *input, char* output);
char *takeMalloc(char *input);
void encrypt(char *key, char *text);

int main(int argc, char *argv[])
{
    if(checkValidInput(argc,argv[1]) == 1){
        return 1;
    }

    char *plaintext = "This is CS50!";
    printf("plaintext: %s\n", plaintext);
    encrypt(argv[1], plaintext);

    return 0;
}

int checkValidInput(int argc,char *s)
{
    if(argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    if(len != 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < len; i++){
        if(s[i] <= 'A' && s[i] >= 'Z' || s[i] <= 'a' && s[i] >= 'z'){
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    return -1;
}

char* takeMalloc(char* input)
{
    int size = 0;
    while (input[size] != '\0')
    {
        size++;
    }
    return malloc(size);
}

void toUpperCase(char *input, char* output)
{
    int i;
    for (i = 0; input[i] != '\0'; i++)
    {
        if(input[i] >= 'a' && input[i] <= 'z')
        {
            output[i] = input[i] - ' ';
        }
        else
        {
            output[i] = input[i];
        }
    }
    output[i] = '\0';
}

void encrypt(char* key, char* text)
{
    char *upperCasedKey = takeMalloc(key);
    char *upperCasedText = takeMalloc(text);
    char *cipherText = takeMalloc(text);

    toUpperCase(key, upperCasedKey);
    toUpperCase(text, upperCasedText);

    for (int i = 0; upperCasedText[i] != '\0'; i++)
    {
        if(upperCasedText[i] >= 'A' && upperCasedText[i] <= 'Z')
        {
            int idx = upperCasedText[i] - 'A';
            cipherText[i] = text[i] >= 'a' && text[i] <= 'z' ? upperCasedKey[idx] + ' ' : upperCasedKey[idx];
        }else{
            cipherText[i] = upperCasedText[i];
        }
    }

    printf("ciphertext: %s\n", cipherText);

    free(upperCasedKey);
    free(upperCasedText);
    free(cipherText);
}
