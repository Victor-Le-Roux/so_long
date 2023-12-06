all	:	
	gcc main.c get_next_line*.c -I ./MLX42/include -L ./MLX42/build -lmlx42 -lglfw -lm -ldl -lpthread
