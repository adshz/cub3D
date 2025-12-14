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

# OS detection
UNAME_S := $(shell uname -s)

# MLX42 configuration (cross-platform)
MLX_DIR = MLX42
MLX_REPO = https://github.com/codam-coding-college/MLX42.git
MLX_BUILD = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD)/libmlx42.a

ifeq ($(UNAME_S),Darwin)
    # macOS - find GLFW via Homebrew
    BREW_EXISTS := $(shell which brew 2>/dev/null)
    GLFW_PREFIX := $(shell brew --prefix glfw 2>/dev/null || echo "")
    ifeq ($(GLFW_PREFIX),)
        GLFW_PREFIX = /opt/homebrew/opt/glfw
    endif
    MLX_FLAGS = -L$(MLX_BUILD) -lmlx42 -L$(GLFW_PREFIX)/lib -lglfw \
                -framework Cocoa -framework OpenGL -framework IOKit
    INCLUDE = -I./inc -I./$(MLX_DIR)/include -I$(GLFW_PREFIX)/include
else
    # Linux
    MLX_FLAGS = -L$(MLX_BUILD) -lmlx42 -lglfw -ldl -pthread -lm
    INCLUDE = -I./inc -I./$(MLX_DIR)/include
endif

# Executable name
NAME = cub3D

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
all: $(MLX_LIB) launch $(NAME)
	@printf "\n$(BOLD)$(CYAN) Cub3D Game Compiled$(DF)\n"

# Download and build MLX42
$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		printf "$(D_Y)Downloading MLX42...$(DF)\n"; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@if [ ! -d "$(MLX_BUILD)" ]; then \
		printf "$(D_Y)Building MLX42 with CMake...$(DF)\n"; \
		cmake -S $(MLX_DIR) -B $(MLX_BUILD) -DDEBUG=1; \
		make -C $(MLX_BUILD) -j4; \
	fi

# Build executable
$(NAME): $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

launch:
	@$(call progress_bar)

# Compile source files into object files (depends on MLX being ready)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(MLX_LIB)
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

# Clean MLX42
mlxclean:
	@rm -rf $(MLX_DIR)
	@printf "$(CYAN)[CUB3D] MLX42 Removed\n$(DF)"

# Full clean including MLX42
ffclean: fclean mlxclean

# Rebuild project
re: fclean all

# Install dependencies
deps:
ifeq ($(UNAME_S),Darwin)
	@printf "$(D_Y)Installing macOS dependencies...$(DF)\n"
	@which brew > /dev/null || (printf "$(RED)Homebrew not found. Install from https://brew.sh$(DF)\n" && exit 1)
	@brew install glfw cmake
	@printf "$(GREEN)Dependencies installed successfully$(DF)\n"
else
	@printf "$(D_Y)Installing Linux dependencies...$(DF)\n"
	@if [ -f /etc/debian_version ]; then \
		sudo apt-get update && sudo apt-get install -y cmake libglfw3-dev; \
	elif [ -f /etc/fedora-release ]; then \
		sudo dnf install -y cmake glfw-devel; \
	elif [ -f /etc/arch-release ]; then \
		sudo pacman -S --noconfirm cmake glfw-wayland; \
	else \
		printf "$(RED)Unknown Linux distribution. Please install cmake and glfw manually.$(DF)\n"; \
	fi
	@printf "$(GREEN)Dependencies installed successfully$(DF)\n"
endif

.PHONY: all launch clean fclean mlxclean ffclean re deps
