NAME       = fdf
BONUS_NAME = fdf_bonus
CC         = cc
CFLAGS     = -Wall -Wextra -Werror
LDFLAGS    = -Lmlx -lmlx -L/opt/X11/lib -lX11 -lXext -framework OpenGL -framework AppKit

LIBRARY    = -L$(LIBFT_DIR) -lft
INCLUDE    = -I$(HDR_DIR) -I$(LIBFT_DIR) -Imlx

LIBFT      = $(LIBFT_DIR)libft.a
LIBFT_DIR  = ./libft/
LIBFT_HDR  = $(LIBFT_DIR)libft.h

HDR_LIST   = fdf.h
HDR_DIR    = ./includes/
HDR        = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS       = get_next_line.c test_gnl.c
SRCS_DIR   = ./srcs/
OBJS       = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBRARY) $(LDFLAGS) $(INCLUDE)

$(BONUS_NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBRARY) $(LDFLAGS) $(INCLUDE)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

bonus: $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re bonus test
