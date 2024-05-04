#include <stdio.h>

void swap(int* a, int* b); // ? called pass by reference // pass address of variable as argument

int main(void) {
    int x = 1;
    int y = 2;

    printf("before swap, x is %i and y is %i\n", x, y);

    swap(&x, &y);

    printf("after swap, x is %i and y is %i\n", x, y);

    return 0;
}

void swap(int* a, int* b) {
    int temp = *a; // ? *a mean go to the address and get its value // assign the value where persist the address of variable.
    *a = *b; // ? overwrite value from b to a (actually from y to x cause of passing their memory address in this function)
    *b = temp; // ? same as here

    // ? that's why swapping value.
}



// #include <stdio.h>
// void swap(int* a, int* b);
// int main(void) {
//     int x = 1;
//     int y = 2;
//     printf("before swap, x is %i and y is %i\n", x, y);
//     swap(&x, &y);
//     printf("after swap, x is %i and y is %i\n", x, y);
//     return 0;
// }
// void swap(int* a, int* b) {
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }