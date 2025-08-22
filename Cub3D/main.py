from utils import *
import pygame

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Cub3D")
clock = pygame.time.Clock()
player = Player(TILE_SIZE, TILE_SIZE, PLAYER_SIZE, PLAYER_SIZE)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            break
    
    update_pos(player)
    screen.fill(FLORE)
    draw_all_lines(player, screen)
    if DO_2D:
        draw_map(screen)
        pygame.draw.rect(screen, PLAYER_COLOR, (player.x, player.y, player.width, player.height))
    pygame.display.flip() # render

    clock.tick(60)

pygame.quit()
