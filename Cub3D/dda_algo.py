import math

def dda(ray_x, ray_y, angle_deg, game_map):
    """
    Corrected DDA raycasting algorithm for all directions.
    
    ray_x, ray_y : float -> starting position
    angle_deg    : float -> ray angle in degrees
    game_map     : 2D array (0 = empty, 1 = wall)
    
    returns: hit_x, hit_y, map_x, map_y, distance
    """
    # Convert angle to radians
    angle = math.radians(angle_deg)
    ray_dir_x = math.cos(angle)
    ray_dir_y = math.sin(angle)

    # Current map square (integer indices)
    map_x = int(ray_x)
    map_y = int(ray_y)

    # Length of ray from one x or y side to next x or y side
    delta_dist_x = abs(1 / ray_dir_x) if ray_dir_x != 0 else float("inf")
    delta_dist_y = abs(1 / ray_dir_y) if ray_dir_y != 0 else float("inf")

    # Step direction and initial sideDist
    if ray_dir_x < 0:
        step_x = -1
        side_dist_x = (ray_x - map_x) * delta_dist_x
    else:
        step_x = 1
        side_dist_x = (map_x + 1.0 - ray_x) * delta_dist_x

    if ray_dir_y < 0:
        step_y = -1
        side_dist_y = (ray_y - map_y) * delta_dist_y
    else:
        step_y = 1
        side_dist_y = (map_y + 1.0 - ray_y) * delta_dist_y

    hit = False
    side = None  # 0 = vertical, 1 = horizontal

    while not hit:
        # Jump to next map square
        if side_dist_x < side_dist_y:
            side_dist_x += delta_dist_x
            map_x += step_x
            side = 0  # vertical wall
        else:
            side_dist_y += delta_dist_y
            map_y += step_y
            side = 1  # horizontal wall

        # Check if ray hit a wall
        if game_map[map_y][map_x] == 1:
            hit = True

    # Calculate perpendicular distance to wall
    if side == 0:
        perp_dist = (map_x - ray_x + (1 - step_x) / 2) / ray_dir_x
    else:
        perp_dist = (map_y - ray_y + (1 - step_y) / 2) / ray_dir_y

    # Exact hit coordinates
    hit_x = ray_x + perp_dist * ray_dir_x
    hit_y = ray_y + perp_dist * ray_dir_y

    return hit_x, hit_y, map_x, map_y, perp_dist
