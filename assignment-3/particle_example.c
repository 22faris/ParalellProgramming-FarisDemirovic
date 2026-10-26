#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Define the Particle structure
struct Particle {
    double x;
    double y;
    double z;
    double mass;
};

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    // Read the number of particles
    long N = atol(argv[1]);

    if (N <= 0) {
        printf("N must be positive.\n");
        return 1;
    }

    // Allocate memory for the particles
    struct Particle *particles =
        malloc((size_t)N * sizeof(struct Particle));

    if (particles == NULL) {
        printf("Allocation failed\n");
        return 1;
    }

    // Initialize every particle
    for (long i = 0; i < N; i++) {
        particles[i].x = sin(i * 0.001);
        particles[i].y = cos(i * 0.001);
        particles[i].z = sqrt(i + 1.0);
        particles[i].mass = 1.0 + (i % 100) * 0.01;
    }

    // Start measuring execution time
    struct timespec t1, t2;

    clock_gettime(CLOCK_MONOTONIC, &t1);

    double sum = 0.0;

    // Calculate the contribution from every particle
    for (long i = 0; i < N; i++) {
        double v2 =
            particles[i].x * particles[i].x +
            particles[i].y * particles[i].y +
            particles[i].z * particles[i].z;

        sum += 0.5 * particles[i].mass * v2;
    }

    clock_gettime(CLOCK_MONOTONIC, &t2);

    // Calculate elapsed time in milliseconds
    double elapsed_ms =
        (t2.tv_sec - t1.tv_sec) * 1000.0 +
        (t2.tv_nsec - t1.tv_nsec) / 1000000.0;

    printf("Number of particles: %ld\n", N);
    printf("Calculated sum: %.6f\n", sum);
    printf("Execution time: %.3f ms\n", elapsed_ms);

    // Release memory
    free(particles);

    return 0;
}
