// Modified version of code from
// https://www.programiz.com/

#include <stdio.h>
#include <math.h>

int main() {
    double a = 0.0, b = 0.0, c = 0.0;
    double discriminant, root1, root2, realPart, imagPart;
    printf("Enter coefficients a, b and c seperated by a space: ");
    int result = scanf("%lf %lf %lf", &a, &b, &c);

    if(result != 3) {
        printf("Error: invalid input. only %d values read.\n", result);
        return 1;
    }

    discriminant = (b * b) - (4 * a * c);

    // condition for real and different roots
    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("root1 = %.2lf and root2 = %.2lf", root1, root2);
    } else if (discriminant = 0) { // condition for real and equal roots
        root1 = root2 = -b / (2 * a);
        printf("root1 = root2 = %.2lf;", root1);
    } else { // if roots are not real
        realPart = -b / (2 * a);
        imagPart = sqrt(-discriminant) / (2 * a);
        printf("root1 = %.2lf+%.2lfi and root2 = %.2f-%.2fi", realPart, imagPart, realPart, imagPart);
    }
    return 0;
} 