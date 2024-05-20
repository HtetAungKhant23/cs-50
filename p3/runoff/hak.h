#include <stdio.h>

int get_int(char* desc)
{
    int value = 0;
    printf("%s", desc);
    scanf("%d", &value);
    return value;
}

char* get_string(char* desc)
{
    char value[10];
    printf("%s", desc);
    scanf("\n%[^\n]s", value);
    char *new = value;
    printf("%s\n", new);
    return new;
}