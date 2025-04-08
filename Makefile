#Define colour
DF = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
MAGENTA = \033[0;95m
YELLOW = \033[0;93m
CYAN =\033[0;96m
WHITE = \033[0;97m
BOLD = \033[91m
ORANGE = \033[38;5;208m

# Compiler and flags
SHELL := bash
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
INCLUDE = -I./inc 

# Executable name
NAME = game

# Source files
SRC_DIR = ./src
OBJ_DIR = ./obj

SRCS = get_next_line.c \
       get_next_line_utils.c \
       main.c \
       utils.c \
       parsing.c \
       free_utils.c\
       floodfill.c \
       test.c \
       str_utils.c

# Object files
OBJS = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS)))


define progress_bar
	i=0
	while [[ $$i -le $(words $(SRCS)) ]]; do \
		printf " "; \
		((i = i + 1)); \
	done	
	printf "$(BOLD)\r$(GREEN)"
endef

# Default target
all: launch $(NAME)

# Build executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

launch: 
	@$(call progress_bar)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ 
	@printf "█"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJS)

# Clean object files and executable
fclean: clean
	@rm -f $(NAME)

# Rebuild project
re: fclean all

