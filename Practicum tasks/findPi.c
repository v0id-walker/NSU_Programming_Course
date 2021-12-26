#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POINTS 10000000

double find_pi(unsigned int all_points) {

    int circle_points = 0;
    double x, y;

    srand(time(NULL));

    for (int i = 0; i < all_points; ++i) {
        x = rand() / (float)RAND_MAX;
        y = rand() / (float)RAND_MAX;

        if ((pow(x, 2) + pow(y, 2)) <= 1.0f) {
            circle_points++;
        }
    }

    return (4 * (double)circle_points / (double)all_points);
}

int main() {

    double pi;

    printf("Количество точек   Результат Pi   Погрешность в %%\n");

    for (unsigned int i = 100; i != POINTS; i *= 10) {
        pi = find_pi(i);
        printf("%15d   %12.7f   %13f\n", i, pi, 100 - (pi / M_PI * 100));
    }

    return 0;
}
