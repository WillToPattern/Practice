#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_map
{
    int lines;
    int width;

    char empty;
    char obstacle;
    char full;

    char **map;
}t_map;


bool is_digit(int c)
{
    return (c >= '0' && c <= '9');
}

bool is_print(int c)
{
    return (c >= ' ' && c <= '~');
}

int ft_strlen(char *str)
{
    int i = -1;

    while (str[++i])
        ;
    return(i);
} 


bool ft_atoi(char *s, t_map *map)
{
    long res = 0;

    if (!s || !map || !is_digit(*s))
        return (false);
    int i = 0;
    for(;is_digit(s[i]); i++)
    {
        res = res * 10 + s[i] - '0';
        if (res > INT_MAX || res < 0)
            return (false);
    }
    if (is_print(s[i]) && is_print(s[i + 1]) && is_print(s[i + 2]) && s[i + 3] == '\0')
    {
        map->empty = s[i];
        map->obstacle = s[i + 1];
        map->full = s[i + 2];
        map->lines = (int)res;
    }
    else
        return (false);
    return (true);
}

bool parse_first(FILE *in, t_map *map) // min case : 1.ox\n
{
    char *line = NULL;
    ssize_t len = 0;
    size_t n = 0;

    len = getline(&line, &n, in);
    if (len < 0 || len < 5 || line[len - 1] != '\n')
        return (free(line), false);
    line[len - 1] = '\0';
    if(!ft_atoi(line, map))
        return (free(line), false);
    free(line);
    return (true);
}

void free_map(t_map *map)
{
    if (!map)
        return;
    int i = -1;

    while (map->map[++i])
        free(map->map[i]);
    free(map->map);
    free(map);
    
}

t_map *get_map(char *name)
{
    FILE *in = name ? fopen(name , "r") : stdin;

    if (!in)
        return (NULL);
    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return (fclose(in), NULL);
    if(!parse_first(in, map))
        return (fclose(in), free(map), NULL);
    
    char *line;
    ssize_t len = 0;
    size_t n = 0;
    map->map = calloc(map->lines + 1, sizeof(char *));
    for(int i = 0 ; i < map->lines; i++)
    {
        line = NULL;
        len = getline(&line, &n, in);
        if (len <= 0 || line[len - 1] != '\n')
            return (fclose(in), free(line) ,free_map(map), NULL);
        line[len - 1] = '\0';
        if (i == 0)
            map->width = ft_strlen(line);
        else if (ft_strlen(line) != map->width)
            return (fclose(in), free(line), free_map(map), NULL);
        map->map[i] = line;
    }
    return (map);
}

bool check_map(t_map *map)
{
    if (!map)
        return (false);
    if (map->lines < 1 || map->width < 1)
        return (free_map(map), false);
    if (map->empty == map->full || map->full == map->obstacle || map->obstacle == map->empty)
        return (free_map(map), false);

    for (int i = 0; i < map->lines; i++)
        for(int j = 0; j < map->width; j++)
            if (map->map[i][j] != map->obstacle && map->map[i][j] != map->empty)
                return (free_map(map), false);
    return (true);
}

void print_map(t_map *map)
{
    if (!map || !map->map || !*(map->map))
        return;
    for(int i = 0; i < map->lines; i++)
        printf("%s\n",map->map[i]);
}

int min3(int a, int c, int b)
{
    int min = a;
    if (c < min)
        min = c;
    if (b < min)
        min = b;
    return (min);
}

t_map *bsq_logic(t_map *map)
{
    int ** int_map = calloc(map->lines , sizeof(int *));
    int max_size = 0;
    int max_i = 0;
    int max_j = 0;

    for(int i = 0; i < map->lines; i++)
    {
        int_map[i] = calloc (map->width, sizeof(int));
        for(int j = 0; j < map->width; j++)
        {
            if (map->map[i][j] == map->obstacle)
                int_map[i][j] = 0;
            else if (!i || !j)
                int_map[i][j] = 1;
            else if (i > 0 && j > 0)
                int_map[i][j] = min3(int_map[i][j - 1], int_map[i - 1][j],int_map[i - 1][j - 1] ) + 1;
            
            if (int_map[i][j] > max_size)
            {
                max_size = int_map[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    for (int i = 0; i < map->lines; i++)
        free(int_map[i]);
    free(int_map);


    for (int i = max_i - (max_size - 1); i <= max_i; i++)
        for (int j = max_j - (max_size - 1); j <= max_j; j++)
            map->map[i][j] = map->full;
    return (map);
}

int bsq(char *name)
{
    t_map *map = get_map(name);
    if (!check_map(map))
        return (printf("Error: invalid map\n"), 1);
    map = bsq_logic(map);
    print_map(map);
    free_map(map);
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 1)
        return bsq(NULL);
    else if (ac == 2)
        return bsq(av[1]);
    else
        printf("Error: invalid map\n");
    return 1;
}