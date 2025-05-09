#Define colour
DF = \033[0;39m
D_Y = \033[1;33m
GRAY = \033[1;30m
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
INCLUDE = -I./inc  \
	  -I./minilibx-linux

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
       str_utils.c \
	   ft_atoi.c \
	   ft_split.c \
	   ft_isdigit.c \
	   ft_substr.c \
	   my_strlen.c \
	   ft_isnumber.c \
	   ft_strtrim.c \
	   my_strchr.c 

# Object files
OBJS = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS)))


define progress_bar
	i=0
	printf "$(D_Y)Cub3D is compiling...\n$(DF)"
	while [[ $$i -le $(words $(SRCS)) ]]; do \
		printf " "; \
		((i = i + 1)); \
	done	
	printf "$(BOLD)]\r[$(GREEN)"
endef

# Default target
all: launch $(NAME)
	@printf "\n$(BOLD)$(CYAN) Cub3D Game Compiled$(DF)\n"

# Build executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS)  $(MLX_FLAGS) -o $(NAME)

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
	@printf "$(CYAN)[CUB3D] Object Removed\n$(DF)"

# Clean object files and executable
fclean: clean
	@rm -f $(NAME)
	@printf "$(CYAN)[CUB3D] Everything is Removed\n$(DF)"
	@printf "$(BOLD)$(ORANGE)======== PROJECT RESET ========\n$(DF)"

# Rebuild project
re: fclean all


.PHONY: all launch clean fclean re
