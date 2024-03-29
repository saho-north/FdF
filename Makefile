NAME       = fdf
CC         = cc
CFLAGS     = -Wall -Wextra -Werror
DFLAGS     = -g -fsanitize=address
LDFLAGS    = -Lmlx -lmlx -L/opt/X11/lib -lX11 -lXext
LIBRARY    = -L$(LIBFT_DIR) -lft
INCLUDE    = -I$(HDR_DIR) -I$(LIBFT_DIR)includes/ -Imlx -I/opt/X11/include
LIBFT      = $(LIBFT_DIR)libft.a
LIBFT_DIR  = ./libft/
MLX        = mlx/libmlx.a
HDR_LIST   = color.h error.h fdf.h usage.h
HDR_DIR    = ./includes/
HDR        = $(addprefix $(HDR_DIR), $(HDR_LIST))
SRCS       = draw.c error.c fdf.c free.c get_map_size.c hook.c init.c key_hook.c \
			 parse_map.c parse_point.c projection.c render.c rotation.c transform.c \
			 liang_barsky.c reset.c color.c key_handler.c usage.c draw_utils.c
SRCS_DIR   = ./srcs/
OBJ_DIR    = ./obj/
OBJS       = $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBRARY) $(LDFLAGS) $(INCLUDE)

debug: $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -o $(NAME) $(LIBRARY) $(LDFLAGS) $(INCLUDE)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C mlx

all: $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HDR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

a: $(NAME)
	./$(NAME) test_maps/a.fdf

42: $(NAME)
	./$(NAME) test_maps/42.fdf

test: $(NAME)
	./$(NAME) test_maps/10-2.fdf
	./$(NAME) test_maps/10-70.fdf
	./$(NAME) test_maps/20-60.fdf
	./$(NAME) test_maps/42.fdf
	./$(NAME) test_maps/50-4.fdf
	./$(NAME) test_maps/100-6.fdf
	./$(NAME) test_maps/basictest.fdf
	./$(NAME) test_maps/elem-col.fdf
	./$(NAME) test_maps/elem-fract.fdf
	./$(NAME) test_maps/elem.fdf
	./$(NAME) test_maps/elem2.fdf
	./$(NAME) test_maps/julia.fdf
	./$(NAME) test_maps/mars.fdf
	./$(NAME) test_maps/pentenegpos.fdf
	./$(NAME) test_maps/plat.fdf
	./$(NAME) test_maps/pnp_flat.fdf
	./$(NAME) test_maps/pyra.fdf
	./$(NAME) test_maps/pyramide.fdf
	./$(NAME) test_maps/t1.fdf
	./$(NAME) test_maps/t2.fdf

.PHONY: all clean fclean re bonus 42 test
