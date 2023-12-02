#include <MLX42/MLX42.h>
#include <stdlib.h>
#include "mario.h"


static mlx_image_t* image;


void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
    {
		image->instances[0].x -= 3;

    }
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		image->instances[0].x += 3;
}

int main(void) {
    mlx_t* mlx;
    mlx_texture_t* img;

    mlx = mlx_init(window.x, window.y, "Premier Niveau de Mario", false);
    if (!mlx)
        return EXIT_FAILURE;

    img = mlx_load_png("./mario_bros_normal.png");
    if (!img) {
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    image = mlx_texture_to_image(mlx, img);
    if (!image) {
        mlx_delete_texture(img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    if (mlx_image_to_window(mlx, image, 0, 500) == -1) {
        mlx_delete_texture(img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }


    mlx_loop_hook(mlx,ft_hook,mlx);
    mlx_loop(mlx);

    mlx_delete_texture(img);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
