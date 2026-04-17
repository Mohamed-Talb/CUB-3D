# CUB3D

**CUB3D** is a simple 3D RAYCASTING ENGINE built in C as part of the 42 CURRICULUM.
The goal of this project is to understand GRAPHICS RENDERING, RAYCASTING, GAME LOOP DESIGN, EVENT HANDLING, and BASIC PHYSICS SIMULATION in a 2D MAP ENVIRONMENT.

This project recreates a simplified FIRST-PERSON MAZE EXPLORER using the MINILIBX GRAPHICS LIBRARY, while respecting strict FUNCTION LIMITATIONS and MEMORY MANAGEMENT rules defined by the 42 NORM.

## **REFERENCES**

The project follows the official SUBJECT and respects THE NORM CODING STANDARD.

SUBJECT: [subject.pdf](./subject.pdf)

## **FEATURES**

CUB3D renders a 3D-LIKE VIEW of a 2D MAP using a RAYCASTING ENGINE.

It supports:

- REAL-TIME 3D RENDERING from a 2D MAP
- PLAYER MOVEMENT inside a MAZE
- ROTATION (LOOK LEFT / RIGHT)
- TEXTURE MAPPING for WALLS
- FLOOR & CEILING COLOR RENDERING
- CLEAN WINDOW EXIT HANDLING

### **CONTROLS**

1. W / A / S / D → PLAYER MOVEMENT in the MAZE
2. LEFT ARROW → LOOK LEFT
3. RIGHT ARROW → LOOK RIGHT
4. ESC → EXIT CLEANLY
5. WINDOW RED CROSS → EXIT CLEANLY

## **PROJECT STRUCTURE**

```abap
GAME/
├── cub3d.c
├── cub3d.h
├── libft/
├── Makefile
├── maps/
├── minilibx-linux/
├── parsing/
├── rendring/
└── textures/
```

## **INSTALLATION & USAGE**

**CLONE REPOSITORY**

```bash
git clone <your-repo-link>
cd GAME
```

**COMPILE MINILIBX (IMPORTANT STEP)**

Before compiling the project, you MUST build MINILIBX:

```bash
cd minilibx-linux
make
cd ..
```

**BUILD PROJECT**

```bash
make
```

**RUN PROGRAM**

```bash
./Cub3d maps/map.cub
```
