all	:	
	gcc main.c -I ./MLX42/include -L ./MLX42/build -lmlx42 -lglfw -lm -ldl -lpthread -o my_program | ./my_program