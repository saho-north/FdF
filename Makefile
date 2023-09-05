NAME            = fdf
NAME_BONUS      = fdf_bonus

CC              = cc
CFLAGS          = -Wall -Wextra -Werror
LDFLAGS         = -lm
LIBRARY         = -L$(LIBFT_DIR) -lft
INCLUDE         = -I$(HDR_DIR) -I$(LIBFT_HDR)

LIBFT           = $(LIBFT_DIR)libft.a
LIBFT_DIR       = ./libft/
LIBFT_HDR       = $(LIBFT_DIR)libft.h

HDR_LIST        = fdf_common.h fdf.h fdf_bonus.h
HDR_DIR         = ./includes/
HDR             = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRCS_DIR        = ./srcs/
SRCS_DIR_COMMON = $(SRCS_DIR)/common/
SRCS_DIR_FDF    = $(SRCS_DIR)/mandatory/
SRCS_DIR_BONUS  = $(SRCS_DIR)/bonus/

SRCS_COMMON     = fdf_common.c
SRCS_FDF        = fdf.c
SRCS_BONUS      = fdf_bonus.c

OBJS_COMMON     = $(addprefix $(SRCS_DIR_COMMON), $(SRCS_COMMON:.c=.o))
OBJS_FDF        = $(OBJS_COMMON) $(addprefix $(SRCS_DIR_FDF), $(SRCS_FDF:.c=.o))
OBJS_BONUS      = $(OBJS_COMMON) $(addprefix $(SRCS_DIR_BONUS), $(SRCS_BONUS:.c=.o))

$(NAME): $(OBJS_FDF) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY) $(LDFLAGS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

bonus: $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_FDF) $(OBJS_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS) $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
