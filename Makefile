#CUB SRC
CUB_SRC = \
	cub3d.c \
	parsing/parser.c utiles.c parsing/getfile.c structs_utiles.c get_next_line.c parsing/colors.c parsing/textures.c parsing/map.c \
	parsing/checkwalls.c  parsing/checkelements.c dda.c

# LIBFT SRCS
LIBFT_SRC = \
	libft/ft_cleaner/cleaner_utiles.c libft/ft_fd/ft_putchar_fd.c libft/ft_fd/ft_putendl_fd.c libft/ft_fd/ft_putnbr_fd.c \
	libft/ft_fd/ft_putstr_fd.c libft/ft_is/ft_isalnum.c libft/ft_is/ft_isalpha.c libft/ft_is/ft_isascii.c libft/ft_is/ft_isdigit.c \
	libft/ft_is/ft_isprint.c libft/ft_is/ft_iswhitespace.c libft/ft_memory/ft_memchr.c libft/ft_memory/ft_memcmp.c libft/ft_memory/ft_memcpy.c \
	libft/ft_memory/ft_memmove.c libft/ft_memory/ft_memset.c libft/ft_others/ft_close.c libft/ft_others/ft_malloc.c libft/ft_strings/ft_append.c \
	libft/ft_strings/ft_append2.c libft/ft_strings/ft_atoi.c libft/ft_strings/ft_bzero.c libft/ft_strings/ft_calloc.c libft/ft_strings/ft_freedouble.c \
	libft/ft_strings/ft_itoa.c libft/ft_strings/ft_printdouble.c libft/ft_strings/ft_putchar.c libft/ft_strings/ft_putstr.c libft/ft_strings/ft_remove.c \
	libft/ft_strings/ft_remove2.c libft/ft_strings/ft_set.c libft/ft_strings/ft_split.c libft/ft_strings/ft_strchr.c libft/ft_strings/ft_strcmp.c \
	libft/ft_strings/ft_strdup.c libft/ft_strings/ft_strdup2.c libft/ft_strings/ft_striteri.c libft/ft_strings/ft_strjoin.c libft/ft_strings/ft_strlcat.c \
	libft/ft_strings/ft_strlcpy.c libft/ft_strings/ft_strlen.c libft/ft_strings/ft_strlen2.c libft/ft_strings/ft_strmapi.c libft/ft_strings/ft_strncmp.c \
	libft/ft_strings/ft_strnstr.c libft/ft_strings/ft_strrchr.c libft/ft_strings/ft_strtrim.c libft/ft_strings/ft_substr.c libft/ft_strings/ft_tolower.c \
	libft/ft_strings/ft_toupper.c libft/ft_strings/ft_uitoa.c

# OBJECTS
CUB_OBJ = $(CUB_SRC:.c=.o)
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

# COMPILER & FLAGS
CC = cc -g3
FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -I./minilibx-linux -L./minilibx-linux -lmlx -lXext -lX11


# OUTPUT EXECUTABLE
NAME = CUB

# RULES
all: $(NAME)

$(NAME): $(CUB_OBJ) $(LIBFT_OBJ)
	@$(CC) $(CUB_OBJ) $(MLX_FLAGS) $(LIBFT_OBJ) -lm -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(CUB_OBJ) $(LIBFT_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re