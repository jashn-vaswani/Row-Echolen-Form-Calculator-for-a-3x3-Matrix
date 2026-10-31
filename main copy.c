#include <stdio.h>
#include <math.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"


// Single struct for all rows so we don't need separate Subtract1 and Subtract2 functions
struct ThreeDegree {
    double x;
    double y;
    double z;
};



// Performs the elementary row operation: E2_new = E2 - (k * E1)
struct ThreeDegree Subtract(struct ThreeDegree E1, struct ThreeDegree E2, double k) {
    struct ThreeDegree Sub;

    Sub.x = (E2.x - k * E1.x);
    Sub.y = (E2.y - k * E1.y);
    Sub.z = (E2.z - k * E1.z);

    return Sub;
}

int main() {
    printf(YELLOW "[a\t b\t c]\n" RESET);
    printf(YELLOW "[d\t e\t f]\n" RESET);
    printf(YELLOW "[g\t h\t i]\n" RESET);

    struct ThreeDegree E1;
    printf(RED "what is the value of a?\n" RESET);
    scanf("%lf", &E1.x);
    printf(RED "what is the value of b?\n" RESET);
    scanf("%lf", &E1.y);
    printf(RED "what is the value of c?\n" RESET);
    scanf("%lf", &E1.z);

    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E1.x, E1.y, E1.z);
    printf(YELLOW "[d\t e\t f]\n" RESET);
    printf(YELLOW "[g\t h\t i]\n" RESET);

    struct ThreeDegree E2;
    printf(RED "what is the value of d?\n" RESET);
    scanf("%lf", &E2.x);
    printf(RED "what is the value of e?\n" RESET);
    scanf("%lf", &E2.y);
    printf(RED "what is the value of f?\n" RESET);
    scanf("%lf", &E2.z);

    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E1.x, E1.y, E1.z);
    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E2.x, E2.y, E2.z);
    printf(YELLOW "[g\t h\t i]\n" RESET);

    struct ThreeDegree E3;
    printf(RED "what is the value of g?\n" RESET);
    scanf("%lf", &E3.x);
    printf(RED "what is the value of h?\n" RESET);
    scanf("%lf", &E3.y);
    printf(RED "what is the value of i?\n" RESET);
    scanf("%lf", &E3.z);

    printf(GREEN "\nThe input matrix is:\n" RESET);
    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E1.x, E1.y, E1.z);
    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E2.x, E2.y, E2.z);
    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E3.x, E3.y, E3.z);

    printf("\n");
    printf("*************************************************************************\n");

    struct ThreeDegree Temp;
    double a, b, d;

    // STEP 1: Handle the 1st Column (x)

    // IMPORTANT: If E1.x is 0, swap E1 with E2 or E3 BEFORE dividing!
    if (E1.x == 0.0) {
        if (E2.x != 0.0) {
            Temp = E1;
            E1 = E2;
            E2 = Temp;
        } else if (E3.x != 0.0) {
            Temp = E1;
            E1 = E3;
            E3 = Temp;
        }
    }

    // Now, if E1.x is non-zero, eliminate E2.x and E3.x
    if (E1.x != 0.0) {
        a = E2.x / E1.x;
        b = E3.x / E1.x;

        E2 = Subtract(E1, E2, a); // Updates E2 in place
        E3 = Subtract(E1, E3, b); // Updates E3 in place

        // STEP 2: 1st column had a pivot, so now reduce Rows 2 and 3 (y and z)

        // If the updated E2.y is 0, try swapping E2 and E3 to get a non-zero pivot
        if (E2.y == 0.0 && E3.y != 0.0) {
            Temp = E2;
            E2 = E3;
            E3 = Temp;
        }

        // If E2.y is non-zero, eliminate E3.y using the UPDATED E2.y and E3.y
        if (E2.y != 0.0) {
            d = E3.y / E2.y;
            E3 = Subtract(E2, E3, d);
        }
        // If Both E2.y and E3.y are 0, The pivot for Row 2 moves to column z.
        else {
            if (E2.z == 0.0 && E3.z != 0.0) {
                Temp = E2;
                E2 = E3;
                E3 = Temp;
            }
            if (E2.z != 0.0) {
                d = E3.z / E2.z;
                E3 = Subtract(E2, E3, d);
            }
        }
    }
    // STEP 3: Special Case where the ENTIRE 1st column (x) was 0
    else {
        // Since E1.x, E2.x, and E3.x are all 0, find the first pivot in column y
        if (E1.y == 0.0) {
            if (E2.y != 0.0) {
                Temp = E1;
                E1 = E2;
                E2 = Temp;
            } else if (E3.y != 0.0) {
                Temp = E1;
                E1 = E3;
                E3 = Temp;
            }
        }

        // If we found a non-zero pivot in E1.y, eliminate E2.y and E3.y
        if (E1.y != 0.0) {
            a = E2.y / E1.y;
            b = E3.y / E1.y;

            E2 = Subtract(E1, E2, a);
            E3 = Subtract(E1, E3, b);

            // Then eliminate column z between Row 2 and Row 3
            if (E2.z == 0.0 && E3.z != 0.0) {
                Temp = E2;
                E2 = E3;
                E3 = Temp;
            }
            if (E2.z != 0.0) {
                d = E3.z / E2.z;
                E3 = Subtract(E2, E3, d);
            }
        }
        // If both column x AND column y are completely 0, only column z remains
        else {
            if (E1.z == 0.0) {
                if (E2.z != 0.0) {
                    Temp = E1;
                    E1 = E2;
                    E2 = Temp;
                } else if (E3.z != 0.0) {
                    Temp = E1;
                    E1 = E3;
                    E3 = Temp;
                }
            }
            if (E1.z != 0.0) {
                a = E2.z / E1.z;
                b = E3.z / E1.z;
                E2 = Subtract(E1, E2, a);
                E3 = Subtract(E1, E3, b);
            }
        }
    }

    // Print the final Row Echelon Form
    printf(BLUE "\nThe Row Echelon form of the matrix is:\n" RESET);
    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E1.x, E1.y, E1.z);
    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E2.x, E2.y, E2.z);
    printf(YELLOW "[%lf\t %lf\t %lf]\n" RESET, E3.x, E3.y, E3.z);

    return 0;
}