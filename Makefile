NAME       = fdf
CC         = cc
CFLAGS     = -Wall -Wextra -Werror
LDFLAGS    = -Lmlx -lmlx -L/opt/X11/lib -lX11 -lXext -framework OpenGL -framework AppKit
LIBRARY    = -L$(LIBFT_DIR) -lft
INCLUDE    = -I$(HDR_DIR) -I$(LIBFT_DIR)includes/ -Imlx

LIBFT      = $(LIBFT_DIR)libft.a
LIBFT_DIR  = ./libft/

HDR_LIST  = *.h
HDR_DIR   = ./includes/
HDR       = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS       = *.c
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
	./$(NAME) test_maps/42.fdf

.PHONY: all clean fclean re bonus test
