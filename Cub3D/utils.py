from dda_algo import dda
from settings import *
import pygame
import math

class Player:
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.fov = 90
        self.speed = 4
        self.width = width
        self.height = height
        self.view_angle = 90
        self.number_of_rays = WIDTH

def draw_map(screen):
    x, y = 0, 0
    for j in range(len(my_map)):
        for i in range(len(my_map[0])):
            if my_map[j][i] == 1:
                pygame.draw.rect(screen, TILES_COLOR, (i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE))
            x += 10
        y += 10

def direction_to_pos(x, y, ray_length, ray_angle):
    line_endx = x + (ray_length * math.cos(math.radians(ray_angle)))
    line_endy = y + (ray_length * math.sin(math.radians(ray_angle)))
    return line_endx - x, line_endy - y

def draw_line(player: Player, screen, x, y, line_endx, line_endy):
    # line_endx = x + (ray_length * math.cos(math.radians(ray_angle)))
    # line_endy = y + (ray_length * math.sin(math.radians(ray_angle)))
    pygame.draw.line(screen, LINE_COLOR, (x, y), (line_endx, line_endy), 1)

def draw_screen_column(screen, start, end, dist):
    line_height = HEIGHT / dist
    y = (HEIGHT - line_height) / 2
    pygame.draw.line(screen, TILES_COLOR, (start, y), (start, y + line_height), 1)

def draw_all_lines(player: Player, screen):
    player_center_x = player.x + (PLAYER_SIZE / 2)
    player_center_y = player.y + (PLAYER_SIZE / 2)
    for i in range(player.number_of_rays):
        column_angle = player.fov / player.number_of_rays
        ray_angle = (i * column_angle) + column_angle + player.view_angle
        hit_x, hit_y, map_x, map_y, dist = dda((player_center_x / TILE_SIZE), (player_center_y / TILE_SIZE), ray_angle, my_map)
        if DO_2D:
            draw_line(player, screen, player_center_x, player_center_y, hit_x * TILE_SIZE, hit_y * TILE_SIZE)
        else:
            draw_screen_column(screen, i, i, dist)

def _pos2map_tile(x, y):
    return my_map[int(y / TILE_SIZE)][int(x / TILE_SIZE)]

def update_pos(player: Player):
    player_center_x = player.x + (PLAYER_SIZE / 2)
    player_center_y = player.y + (PLAYER_SIZE / 2)
    keys = pygame.key.get_pressed()
    # if not DO_2D:
    if keys[pygame.K_LEFT]:
        player.view_angle -= 2
    if keys[pygame.K_RIGHT]:
        player.view_angle += 2
    if keys[pygame.K_UP]:
        added_x, added_y = direction_to_pos(player.x, player.y, 3, player.view_angle + 45)
        if _pos2map_tile(player_center_x + added_x, player_center_y) == 0:
            player.x += added_x
        # elif added_x < 0:
        #     print(f"adding to x: {player_center_x % TILE_SIZE}")
        #     player.x += player_center_x % TILE_SIZE
        # else:
        #     print(f"adding to x: {TILE_SIZE - player_center_x % TILE_SIZE}")
        #     player.x += TILE_SIZE - player_center_x % TILE_SIZE
        if _pos2map_tile(player_center_x, player_center_y + added_y) == 0:
            player.y += added_y
        # elif added_y < 0:
        #     print(f"adding to y: {player_center_y % TILE_SIZE}")
        #     player.y += player_center_y % TILE_SIZE
        # else:
        #     print(f"adding to y: {TILE_SIZE - player_center_y % TILE_SIZE}")
        #     player.y += TILE_SIZE - player_center_y % TILE_SIZE
    if keys[pygame.K_DOWN]:
        added_x, added_y = direction_to_pos(player.x, player.y, -3, player.view_angle + 45)
        if _pos2map_tile(player_center_x + added_x, player_center_y) == 0:
            player.x += added_x
        # elif added_x < 0:
        #     print(f"adding to x: {player_center_x % TILE_SIZE}")
        #     player.x -= player_center_x % TILE_SIZE
        # else:
        #     print(f"adding to x: {TILE_SIZE - player_center_x % TILE_SIZE}")
        #     player.x -= TILE_SIZE - player_center_x % TILE_SIZE
        if _pos2map_tile(player_center_x, player_center_y + added_y) == 0:
            player.y += added_y
        # elif added_y < 0:
        #     print(f"adding to y: {player_center_y % TILE_SIZE}")
        #     player.y -= player_center_y % TILE_SIZE
        # else:
        #     print(f"adding to y: {TILE_SIZE - player_center_y % TILE_SIZE}")
        #     player.y -= TILE_SIZE - player_center_y % TILE_SIZE
