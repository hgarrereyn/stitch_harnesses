#include <stdio.h>
#define CUTE_C2_IMPLEMENTATION
#include "cute_c2.h"

int main() {
    // Define two circles and test collision
    c2Circle A, B; 
    A.p = c2V(0.0f, 0.0f); A.r = 5.0f;
    B.p = c2V(7.0f, 0.0f); B.r = 3.0f;

    int collided = c2CircletoCircle(A, B);
    printf("Collided: %d\n", collided);

    // Compute distance between two points using cute_c2 helpers
    c2v d = c2Sub(B.p, A.p);
    float len = c2Len(d);
    printf("Center distance: %.2f\n", len);

    return 0;
}
