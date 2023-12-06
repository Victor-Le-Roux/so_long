#include "MLX42/include/MLX42/MLX42_Int.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include "mario.h"
#include "get_next_line.h"
#include <ctype.h>

static mlx_image_t* image_mario;
static mlx_image_t* image_sol;

void displayMapFromFile(char *map, mlx_t* mlx)
{
    int fd, x = 0, y = WINDOW_HEIGHT - HEIGHT_SOL;
    char *line;

    fd = open(map, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '0')
            {
                // Affichez l'image du sol à la position (x, y)
                mlx_image_to_window(mlx, image_sol, x, y);
                x += WIDTH_SOL;
            }
            else if (isdigit(line[i]))
            {
                // Sautez l'espace pour les autres chiffres
                x += (line[i] - '0') * WIDTH_SOL;
            }
        }
        y -= HEIGHT_SOL;
        x = 0; // Réinitialisez la position x
        free(line);
    }

    if (close(fd) == -1)
    {
        perror("Error closing file");
        return;
    }
}



void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
    {
		image_mario->instances[0].x -= 3;

    }
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		image_mario->instances[0].x += 3;
}

int main(void) {
    mlx_t* mlx;
    mlx_texture_t* img_mario;
    mlx_texture_t* img_sol;

    mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Premier Niveau de Mario", false);
    if (!mlx)
        return EXIT_FAILURE;

    img_mario = mlx_load_png(MARIO_FACE_RIGHT);
    img_sol = mlx_load_png(SOL);
    if (!img_sol) {
        mlx_delete_texture(img_mario);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    if (!img_mario) {
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    image_mario = mlx_texture_to_image(mlx, img_mario);
    if (!image_mario) {
        mlx_delete_texture(img_mario);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    image_sol = mlx_texture_to_image(mlx, img_sol);
    if (!image_sol) {
        mlx_delete_texture(img_mario);
        mlx_delete_texture(img_sol);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    if (mlx_image_to_window(mlx, image_mario, 0, 500) == -1) {
        mlx_delete_texture(img_mario);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    int sol_y_position = WINDOW_HEIGHT - HEIGHT_SOL;
    if (mlx_image_to_window(mlx, image_sol, 0, sol_y_position) == -1) {
        mlx_delete_texture(img_mario);
        mlx_delete_texture(img_sol);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    displayMapFromFile("map.txt",mlx);
    mlx_loop_hook(mlx,ft_hook,mlx);
    mlx_loop(mlx);

    mlx_delete_texture(img_mario);
    mlx_delete_texture(img_sol);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
