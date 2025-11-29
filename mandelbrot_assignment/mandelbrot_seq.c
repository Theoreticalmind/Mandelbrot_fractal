#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mandelbrot.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAX_ITER 5000

// The function signature is updated to accept the 'choice' parameter
void generate_mandelbrot(int width, int height, const char* filename, int choice) {
    unsigned char* image = malloc(width * height * 3);
    if (!image) {
        perror("Unable to allocate memory for the image");
        return;
    }

    // Declare variables for zoom and position
    double ZOOM, CENTER_X, CENTER_Y;

    // Set the view parameters based on the user's choice
    switch (choice) {
        case 2: // Seahorse Valley
            ZOOM = 200.0;
            CENTER_X = -0.745;
            CENTER_Y = 0.12;
            break;
        case 3: // Elephant Valley
            ZOOM = 50.0;
            CENTER_X = 0.275;
            CENTER_Y = 0.005;
            break;
        case 1: // Full View
        default: // Default to full view if choice is invalid
            ZOOM = 1.0;
            CENTER_X = -0.75;
            CENTER_Y = 0.0;
            break;
    }

    // Iterate over each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate the range of the complex plane to display based on zoom
            double view_width = 4.0 / ZOOM;
            double view_height = view_width * height / width; // Maintain aspect ratio

            // Map pixel to complex plane coordinate
            double cx = CENTER_X - view_width / 2.0 + (x / (double)width) * view_width;
            double cy = CENTER_Y - view_height / 2.0 + (y / (double)height) * view_height;

            double zx = 0.0, zy = 0.0;
            int iter = 0;

            // The core Mandelbrot calculation
            while (zx * zx + zy * zy < 4.0 && iter < MAX_ITER) {
                double tmp = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tmp;
                iter++;
            }

            int pos = (y * width + x) * 3;
            // Using the smooth coloring palette
            if (iter == MAX_ITER) {
                image[pos] = 0; image[pos+1] = 0; image[pos+2] = 0;
            } else {
                double smooth_iter = iter + 1 - log(log(sqrt(zx * zx + zy * zy))) / log(2.0);
                unsigned char r = (unsigned char)(sin(0.1 * smooth_iter + 0) * 127 + 128);
                unsigned char g = (unsigned char)(sin(0.1 * smooth_iter + 2) * 127 + 128);
                unsigned char b = (unsigned char)(sin(0.1 * smooth_iter + 4) * 127 + 128);
                image[pos] = r; image[pos+1] = g; image[pos+2] = b;
            }
        }
    }

    stbi_write_png(filename, width, height, 3, image, width * 3);
    free(image);
}