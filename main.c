#include "MLX42/include/MLX42/MLX42_Int.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include "mario.h"
#include "get_next_line.h"
#include <ctype.h>

static mlx_image_t* image_mario;
static mlx_image_t* image_sol;

static void process_line(char *line, int y, mlx_t *mlx)
{
    int x;

    x = 0;
    while (line[x] != '\0')
    {
        if (line[x] == '0')
            mlx_image_to_window(mlx, image_sol, x * WIDTH_SOL, y);
        if (line[x] == 'T')
            mlx_image_to_window(mlx, image_sol, x * WIDTH_SOL, y);    
        x++;
    }
}

void display_map(mlx_t *mlx)
{
    int fd;
    char *line;
    int line_count;
    int y;

    fd = open("map.txt", O_RDONLY);
    if (fd == -1)
        return;
    line_count = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        free(line);
        line_count++;
    }
    lseek(fd, 0, SEEK_SET);
    y = WINDOW_HEIGHT - line_count * HEIGHT_SOL;
    while ((line = get_next_line(fd)) != NULL)
    {
        process_line(line, y, mlx);
        y += HEIGHT_SOL;
        free(line);
    }
    close(fd);
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
    // if (!img_mario) {
        // mlx_terminate(mlx);
        // return EXIT_FAILURE;
    // }

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
    display_map(mlx);
    mlx_loop_hook(mlx,ft_hook,mlx);
    mlx_loop(mlx);

    mlx_delete_texture(img_mario);
    mlx_delete_texture(img_sol);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
