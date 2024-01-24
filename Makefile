NAME       = fdf
CC         = cc
CFLAGS     = -Wall -Wextra -Werror
LDFLAGS    = -Lmlx -lmlx -L/opt/X11/lib -lX11 -lXext -framework OpenGL -framework AppKit
LIBRARY    = -L$(LIBFT_DIR) -lft
INCLUDE    = -I$(HDR_DIR) -I$(LIBFT_DIR)includes/ -Imlx

LIBFT      = $(LIBFT_DIR)libft.a
LIBFT_DIR  = ./libft/

HDR_LIST  = fdf.h error.h
HDR_DIR   = ./includes/
HDR       = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS       = error.c \
			 fdf.c \
			 free.c	\
			 get_map_size.c \
			 init.c \
			 parse_point.c \
			 process_map.c

SRCS_DIR   = ./srcs/
OBJS       = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBRARY) $(LDFLAGS) $(INCLUDE)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: $(ALL)

test: $(NAME)
	./$(NAME) test_maps/10-2.fdf

small: $(NAME)
	./$(NAME) test_maps/10-2.fdf
	./$(NAME) test_maps/10-70.fdf
	./$(NAME) test_maps/20-60.fdf
	./$(NAME) test_maps/42.fdf
	./$(NAME) test_maps/basictest.fdf
	./$(NAME) test_maps/elem.fdf
	./$(NAME) test_maps/elem2.fdf
	./$(NAME) test_maps/pentenegpos.fdf
	./$(NAME) test_maps/plat.fdf
	./$(NAME) test_maps/pnp_flat.fdf
	./$(NAME) test_maps/pyra.fdf

medium: $(NAME)
	./$(NAME) test_maps/50-4.fdf
	./$(NAME) test_maps/pylone.fdf

large: $(NAME)
	./$(NAME) test_maps/100-6.fdf

color: $(NAME)
	./$(NAME) test_maps/elem-col.fdf
	./$(NAME) test_maps/pyramide.fdf

fract: $(NAME)
	./$(NAME) test_maps/elem-fract.fdf

julia: $(NAME)
	./$(NAME) test_maps/julia.fdf

mars: $(NAME)
	./$(NAME) test_maps/mars.fdf

t1: $(NAME)
	./$(NAME) test_maps/t1.fdf

t2: $(NAME)
	./$(NAME) test_maps/t2.fdf

testall: $(NAME)
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
	./$(NAME) test_maps/pylone.fdf
	./$(NAME) test_maps/pyra.fdf
	./$(NAME) test_maps/pyramide.fdf
	./$(NAME) test_maps/t1.fdf
	./$(NAME) test_maps/t2.fdf

.PHONY: all clean fclean re bonus test small medium large color fract julia mars t1 t2 testall
