# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

# Executable name
NAME = game

# Source files
SRCS = get_next_line.c \
       get_next_line_utils.c \
       main.c \
       utils.c \
       parsing.c \
       free_utils.c\
       floodfill.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(NAME)

# Build executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Rebuild project
re: fclean all

