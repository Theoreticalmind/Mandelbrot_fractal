#ifndef MANDELBROT_H
#define MANDELBROT_H

/**
 * @brief Generates a Mandelbrot set image and saves it to a file.
 *
 * @param width The width of the output image in pixels.
 * @param height The height of the output image in pixels.
 * @param filename The name of the output PNG file.
 * @param choice An integer selecting the region and palette.
 */
void generate_mandelbrot(int width, int height, const char* filename, int choice);

#endif // MANDELBROT_H