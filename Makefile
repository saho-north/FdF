NAME      = fdf_tmp
CC        = cc
CFLAGS    = -Wall -Wextra -Werror
LDFLAGS   = -lm -lmlx
LIBRARY   = -L$(LIBFT_DIR) -lft
INCLUDE   = -I$(HDR_DIR) -I$(LIBFT_DIR)

LIBFT     = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HDR = $(LIBFT_DIR)libft.h

HDR_LIST  = fdf.h
HDR_DIR   = ./includes/
HDR       = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS_DIR  = ./srcs/
SRCS      = fdf.c get_next_line.c
OBJS      = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

bonus: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test: $(NAME)
	valgrind ./$(NAME) test_maps/42.fdf

.PHONY: all clean fclean re bonus
