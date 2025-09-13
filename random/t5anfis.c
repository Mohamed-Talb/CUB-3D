#include "cub3d.h"

typedef struct s_cos
{
    void *mlx;
    void *win;
} t_cos;

t_cos *app;

int my_round(float number)
{
    number += 0.5;
    return ((int)number);
}

void drawlineH(int x0, int y0, int x1, int y1)
{   
    if (x0 > x1)
    {
        int tmp;
        tmp = x0; x0 = x1; x1 = tmp;
        tmp = y0; y0 = y1; y1 = tmp;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int dir = (dy < 0) ? -1 : 1;
    dy *= dir;
    int y = y0;

    if (dx != 0)
    {
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++)
        {
            mlx_pixel_put(app->mlx, app->win, x0 + i, y, 0xffffff);
            if (p >= 0)
            {
                y += dir;
                p += 2 * dy - 2 * dx;   // move in y
            }
            else
                p += 2 * dy;           // only move in x
        }
    }
}

void drawlineV(int x0, int y0, int x1, int y1)
{
    if (y0 > y1)
    {
        int tmp;
        tmp = x0; x0 = x1; x1 = tmp;
        tmp = y0; y0 = y1; y1 = tmp;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int dir = (dx < 0) ? -1 : 1;
    dx *= dir;
    int x = x0;

    if (dy != 0)
    {
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++)
        {
            mlx_pixel_put(app->mlx, app->win, x, y0 + i, 0xffffff);
            if (p >= 0)
            {
                x += dir;
                p += 2 * dx - 2 * dy;
            }
            else
                p += 2 * dx;
        }
    }
}

void drawcos()
{
    double angle;
    int x = 0;
    int y;
    int oldy;
    
    double freq = 0.03;
    int tail = 100;
    angle = (double)(x - 400) * freq;
    oldy = tail * cos(angle) + 240;;
    x += 1;
    int count = 0;
    while (x <= 800)
    {
        if (count == 100)
        {
            count = 0;
            usleep(600);
        }
        angle = (double)(x - 400) * freq;
        y = tail * cos(angle) + 240; 
        y = 240 - (tail * cos(angle));
        if (1 > abs(y - oldy))
            drawlineH(x - 1, oldy, x, y);
        else
            drawlineV(x - 1, oldy, x, y);
        oldy = y;

        x++;
        count++;
    }
}

void drawcircle(int cx, int cy, float r)
{
    float x = 0;
    float y = -r;
    double midy = 0.0;
    while(x < -y)
    {
        midy = y + 0.5;
        if (x*x + midy*midy >= r*r)
            y++;
        mlx_pixel_put(app->mlx, app->win, (cx + x), (cy + y), 0xff0000);
        mlx_pixel_put(app->mlx, app->win, (cx - x), (cy + y), 0xff0000);
        mlx_pixel_put(app->mlx, app->win, (cx + x), (cy - y), 0xff0000);
        mlx_pixel_put(app->mlx, app->win, (cx - x), (cy - y), 0xff0000);
        mlx_pixel_put(app->mlx, app->win, (cx + y), (cy + x), 0xff0000);
        mlx_pixel_put(app->mlx, app->win, (cx - y), (cy + x), 0xff0000);
        mlx_pixel_put(app->mlx, app->win, (cx + y), (cy - x), 0xff0000);
        mlx_pixel_put(app->mlx, app->win, (cx - y), (cy - x), 0xff0000);
        x++;
    }
}

void resetwin()
{
    int x = 0;
    int y = 0;
    while (x  <= 800)
    {
        y = 0;
        while (y <= 480)
        {
            mlx_pixel_put(app->mlx, app->win, x, y, 0x000000);
            y++;
        }
        x++;
    }
}

int mouseclick(int button, int x, int y, void *param)
{
    (void)param;
    (void)y;
    (void)x;
    if (button == 1) 
    {
        resetwin();
        // drawcos();
        float i = 0;
        while (i < 100)
        {
            drawcircle(x, y, i);
            i += 0.01;
        }
    }
    return 0;
}

void drawrepair()
{
    drawlineH(0, 240, 800, 240);
    drawlineV(400, 0, 400, 480);
}




int main()
{
    app = calloc(1, sizeof(t_cos));
    app->mlx = mlx_init();
    app->win = mlx_new_window(app->mlx, 800, 480, "COS");
    drawrepair();
    drawcos();
    resetwin();
    mlx_mouse_hook(app->win, mouseclick, app);
    // mlx_put_image_to_window(app->mlx, app->win, app->screen.img, 0, 0);
    mlx_loop(app->mlx);
}



