#include "../cub3d.h"

static void duplicated(int tex)
{
    static int arr[6];

    if (arr[tex])
    {
        if (tex == NO)
            printf("NO component duplicated\n");
        else if (tex == SO)
            printf("SO component duplicated\n");
        else if (tex == WE)
            printf("WE component duplicated\n");
        else if (tex == EA)
            printf("EA component duplicated\n");
        else if (tex == C)
            printf("C component duplicated\n");
        else if (tex == F)
            printf("F component duplicated\n");
        exit(1);
    }
    arr[tex] = 1;
}

static void check_exist(int *arr)
{
    for (int i = 0; i < 6; i++)
    {
        if (arr[i] == 0)
        {
            if (i == NO)
                printf("NO component doesn't exist\n");
            else if (i == SO)
                printf("SO component doesn't exist\n");
            else if (i == WE)
                printf("WE component doesn't exist\n");
            else if (i == EA)
                printf("EA component doesn't exist\n");
            else if (i == C)
                printf("C component doesn't exist\n");
            else if (i == F)
                printf("F component doesn't exist\n");
            exit(1);
        }
    }
}

static int select_component(char *str)
{
    if (ft_strncmp(str, "NO", 2) == 0)
        return (NO);
    else if (ft_strncmp(str, "SO", 2) == 0)
        return (SO);
    else if (ft_strncmp(str, "WE", 2) == 0)
        return (WE);
    else if (ft_strncmp(str, "EA", 2) == 0)
        return (EA);
    else if (*str == 'C')
        return (C);
    else if (*str == 'F')
        return (F);
    else
        return (6);
}

static int check_component(t_game *cub, char *str, int *arr)
{
    int com;

    com = select_component(str);
    if (com >= 0 && com <= 3)
    {
        duplicated(com);
        arr[com] = 1;
        get_textures(cub, str, com);
    }
    else if (com == 4 || com == 5)
    {
        duplicated(com);
        arr[com] = 1;
        get_color(cub, str, com);
    }
    else
        errors("Error: Map starts before all components are defined\n", 1);
    return 1;
}

void components(t_game *cub)
{
    int i = 0;
    int found = 0;
    int *arr = ft_calloc(6, sizeof(int));
    char *str;

    while (cub->file[i])
    {
        str = cub->file[i];
        while (*str && ft_iswhitespace(*str))
            str++;
        if (*str == '\0')
        {
            i++;
            continue;
        }
        if (found < 6)
        {
            check_component(cub, str, arr);
            found++;
        }
        else
            break;
        i++;
    }
    check_exist(arr);
    cub->file = &cub->file[i];
}
