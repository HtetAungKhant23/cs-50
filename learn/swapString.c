#include <stdio.h>

void swap(char** a, char** b);

int main() {

    char* x = "This is";
    char* y = "CS50";

    printf("before : %s %s\n", x, y);

    printf("x point to %p\n", x);
    printf("address of x is %p\n", &x);

    swap(&x, &y);

    printf("after : %s %s\n", x, y);
    return 0;
}

void swap(char** a, char** b) {
    printf("In swap func: \n");
    printf("value of a is %p\n", *a);
    printf("a point to %p\n", a);
    printf("address of a is %p\n", &a);

    char* temp = *a;  // ? store the value of another pointer
    *a = *b;
    *b = temp;
}
