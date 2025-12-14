# Cub3D

A raycasting game engine inspired by Wolfenstein 3D, developed as part of the 42 school curriculum. Renders a 3D maze from a first-person perspective using raycasting techniques.

## Requirements

### Operating System
- **Linux** (Ubuntu 20.04+, Debian 10+, or similar)
- **macOS** (10.15 Catalina or later)

### Compiler
- **GCC** 7.0 or later (or Clang 10.0+ on macOS)
- Must support C99 standard

### Dependencies
- **GNU Make** 3.81 or later
- **Linux:** X11 development libraries
- **macOS:** Xcode Command Line Tools
- **MiniLibX** (see installation steps)

## Installation

### 1. Clone the Repository

```bash
git clone <repository-url> Cub3d
cd Cub3d
```

### 2. Install Dependencies

Run the dependency installer (handles both macOS and Linux):

```bash
make deps
```

This will automatically install:
- **macOS:** glfw, cmake (via Homebrew)
- **Linux:** cmake, libglfw3-dev (via apt/dnf/pacman)

**Note for macOS:** Requires [Homebrew](https://brew.sh). Install it first if needed:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 3. Build the Project

```bash
make
```

The Makefile automatically:
- Detects your operating system (Linux or macOS)
- Downloads and builds MLX42 graphics library
- Compiles the game

This produces the `cub3D` executable.

## Usage

```bash
./cub3D <map_file.cub>
```

**Examples:**
```bash
# macOS (Apple Silicon & Intel)
./cub3D maps/macos/simple.cub
./cub3D maps/macos/demo.cub

# Linux
./cub3D maps/linux/works.cub
```

## Controls

| Key       | Action           |
|-----------|------------------|
| `W`       | Move forward     |
| `S`       | Move backward    |
| `A`       | Strafe left      |
| `D`       | Strafe right     |
| `←`       | Rotate left      |
| `→`       | Rotate right     |
| `ESC`     | Exit game        |

## Map File Format (.cub)

Map files define textures, colors, and the maze layout.

**Example:**
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
1111111110000000011000001110001
100000000011000001100000111000111111111
11110111111111011100000010001
11110111111111011101010010001
1100000011010101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Elements:**
- `NO`, `SO`, `WE`, `EA` - Wall texture paths (XPM format)
- `F R,G,B` - Floor color (RGB values 0-255)
- `C R,G,B` - Ceiling color (RGB values 0-255)
- `1` - Wall
- `0` - Empty space (walkable)
- `N`, `S`, `E`, `W` - Player spawn position and direction

## Features

- Raycasting-based 3D rendering
- Textured walls (XPM format)
- Configurable floor and ceiling colors
- Minimap display
- Smooth player movement and rotation
- Map validation and error handling

## Project Structure

```
Cub3d/
├── src/
│   ├── init/          # Initialization functions
│   ├── parser/        # Map file parsing and validation
│   ├── player/        # Movement and input handling
│   ├── render/        # Raycasting and rendering
│   │   └── minimap/   # Minimap rendering
│   ├── utils/         # Utility functions
│   └── cub_libft/     # Custom C library functions
├── inc/               # Header files
├── maps/
│   ├── macos/         # Maps for macOS (Apple Silicon & Intel)
│   └── linux/         # Maps for Linux systems
├── textures/
│   ├── simple/        # Simple solid-color textures (macOS)
│   └── wolfenstein/   # Detailed textures (Linux)
└── Makefile
```

## Build Commands

| Command         | Description                          |
|-----------------|--------------------------------------|
| `make deps`     | Install dependencies (glfw, cmake)   |
| `make`          | Build the project                    |
| `make clean`    | Remove object files                  |
| `make fclean`   | Remove all build artifacts           |
| `make re`       | Clean rebuild                        |
| `make mlxclean` | Remove MLX42 directory               |
| `make ffclean`  | Full clean (including MLX42)         |

## Troubleshooting

### All Platforms

**Dependencies not installed:**
```bash
make deps
```

**MLX42 build fails:**
Make sure cmake is installed:
```bash
# macOS
brew install cmake

# Ubuntu/Debian
sudo apt install cmake
```

### Linux

**GLFW not found:**
```bash
sudo apt install libglfw3-dev
```

**Display not found:**
Make sure you're running in a graphical environment.

### macOS

**GLFW not found:**
```bash
brew install glfw
```

**Permission denied when running:**
```bash
chmod +x cub3D
```

## License

Part of 42 Project
