#include <stdio.h>

int main() {
    int a = 15;
    int b = 5;

    int Addition = a + b;
    int Subtraction = a - b;
    float Division = (float)a / b;   
    int Multiplication = a * b;

    printf("Addition = %d\n", Addition);
    printf("Subtraction = %d\n", Subtraction);
    printf("Division = %.2f\n", Division);   
    printf("Multiplication = %d\n", Multiplication);

    return 0;
}
