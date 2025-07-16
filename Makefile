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
NAME = Cub3d

# Source files
SRC_DIR = ./src
OBJ_DIR = ./obj

SRCS = \
		init/init_data.c \
		init/init_img.c \
		init/init_mlx.c \
		init/init_texture.c \
		cub_libft/ft_atoi.c \
		cub_libft/ft_isnumber.c \
		cub_libft/ft_split.c \
		cub_libft/ft_substr.c \
		cub_libft/str_utils.c \
		cub_libft/ft_calloc.c \
		cub_libft/ft_memset.c \
		cub_libft/ft_strings.c \
		cub_libft/my_strchr.c  \
		cub_libft/ft_isdigit.c \
		cub_libft/ft_putnbr.c \
		cub_libft/my_strlen.c \
		cub_libft/ft_strtrim.c \
		parser/create_map.c \
		parser/game_map.c \
		parser/get_file_data.c \
		parser/parse_data.c \
		parser/utils.c \
		parser/validator/is_rgb_valid.c \
		parser/validator/is_valid_map_border.c \
		parser/validator/is_valid_textures.c \
		parser/validator/is_valid_file.c \
		parser/validator/is_valid_map.c \
		parser/validator/map_elem.c \
		player/direction.c \
		player/movement.c \
		player/position.c \
		player/rotation.c \
		player/user_input.c \
		render/raycasting.c \
		render/render.c \
		render/texture.c \
		render/utils.c \
		render/minimap/minimap.c \
		render/minimap/mini_map_gen.c \
		render/minimap/mini_map_utils.c \
		render/minimap/mini_map_render.c \
		utils/ft_errors.c \
		utils/clean.c \
		utils/fill_matrix.c \
		utils/configure_rgb.c \
		utils/quit_game.c \
		debug.c \
		get_next_line_utils.c \
		main.c \
		utils.c \
		parsing.c \
		free_utils.c\
		get_next_line.c \

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
