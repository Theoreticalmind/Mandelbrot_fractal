#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> // Include OpenMP header for the function call
#include "mandelbrot.h"

int main(int argc, char *argv[]) {
    // Check for 4 arguments: program_name, width, height, filename
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <width> <height> <output.png>\n", argv[0]);
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    const char* filename = argv[3];
    int choice = 0;
    int num_threads = 0; // Variable to store the thread count

    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Width and height must be positive integers.\n");
        return 1;
    }

    // --- First Prompt: Image Selection ---
    printf("Please select an image type to generate:\n");
    printf("  1: Full View\n");
    printf("  2: Seahorse Valley\n");
    printf("  3: Elephant Valley\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        return 1;
    }

    // --- Second Prompt: Thread Count ---
    printf("Enter the number of threads to use (type any positive number if testing sequential code): ");
    if (scanf("%d", &num_threads) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        return 1;
    }

    // Set the number of threads for OpenMP if a positive number is given
    if (num_threads > 0) {
        omp_set_num_threads(num_threads);
    }

    printf("\nGenerating %dx%d Mandelbrot set, saving to %s\n", width, height, filename);
    
    // Print a confirmation of the choice and thread count
    switch(choice) {
        case 1: printf("Image type: Full View\n"); break;
        case 2: printf("Image type: Seahorse Valley\n"); break;
        case 3: printf("Image type: Elephant Valley\n"); break;
        default:
            printf("Warning: Invalid choice '%d'. Defaulting to Full View.\n", choice);
            choice = 1; // Set a safe default
            break;
    }
    if (num_threads > 0) {
        printf("Using %d threads for parallel execution.\n", num_threads);
    } else {
        printf("Using default number of threads for parallel execution.\n");
    }

    // Use a high-resolution timer
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // This function call remains the same
    generate_mandelbrot(width, height, filename, choice);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Finished in %f seconds.\n", time_spent);

    return 0;
}