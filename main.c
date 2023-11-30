#include <MLX42/MLX42.h>
#include <stdlib.h>

int main(void) {
    mlx_t* mlx;
    mlx_texture_t* img;
    mlx_image_t* image;

    // Initialize MLX42
    mlx = mlx_init(800, 600, "My MLX42 Window", false);
    if (!mlx)
        return EXIT_FAILURE;

    // Load an image
    img = mlx_load_png("./mario_bros_normal.png"); // Replace with your image path
    if (!img) {
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Convert texture to image
    image = mlx_texture_to_image(mlx, img);
    if (!image) {
        mlx_delete_texture(img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Display the image in the window
    if (mlx_image_to_window(mlx, image, 0, 0) == -1) {
        mlx_delete_texture(img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Main loop to keep the window open
    mlx_loop(mlx);

    // Clean up
    mlx_delete_texture(img);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
