#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;

    // Initialiser la MiniLibX
    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL)
        return (1);  // Échec de l'initialisation

    // Créer une fenêtre
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Ma fenêtre MiniLibX");
    if (win_ptr == NULL)
    {
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        return (1);  // Échec de la création de la fenêtre
    }

    // Lancer la boucle d'événements
    mlx_loop(mlx_ptr);
    return (0);
}
