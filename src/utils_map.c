#include "../inc/so_long.h"

void	split_map(t_map *map)
{
	int	i;

	map->height = 1;
	map->width = 0;
	i = 0;
	while (map->map[i] != '\n')
	{
		map->width++;
		i++;
	}
	while (map->map[i] != '\0')
	{
		if (map->map[i] == '\n')
			map->height++;
		i++;
	}
	map->map_2d = ft_split(map->map, '\n');
	if (!map->map_2d)
	{
		free_map(map);
		ft_error("Error\nCould not split map");
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_2d[i])
	{
		free(map->map_2d[i]);
		i++;
	}
	free(map->map_2d);
}

void	draw_map(t_mlx *mlx, t_map *map, t_imgs **imgs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		while (j < map->width)
		{
			if (map->map_2d[i][j] == '1')
				print_data_img(imgs[0], mlx, 80 * i, 80 * j);
			else if (map->map_2d[i][j] == '0')
				print_data_img(imgs[1], mlx, 80 * i, 80 * j);
			else if (map->map_2d[i][j] == 'C')
				print_data_img(imgs[3], mlx, 80 * i, 80 * j);
			else if (map->map_2d[i][j] == 'E')
				print_data_img(imgs[4], mlx, 80 * i, 80 * j);
			else if (map->map_2d[i][j] == 'P')
				print_data_img(imgs[2], mlx, 80 * i, 80 * j);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	change_map(t_map *map, int y, int x, char a, char b)
{
	if (map->exit_deleted == 1)
	{
		map->map_2d[map->init_pos_y][map->init_pos_x] = 'E';
		map->map_2d[map->init_pos_y + y][map->init_pos_x + x] = b;
		map->exit_deleted = 0;
	}
	else
	{
		map->map_2d[map->init_pos_y][map->init_pos_x] = a;
		map->map_2d[map->init_pos_y + y][map->init_pos_x + x] = b;
	}
	map->init_pos_y += y;
	map->init_pos_x += x;
}

int	move(t_map *map, int y, int x)
{
	if (map->map_2d[map->init_pos_y + y][map->init_pos_x + x] == '0')
		change_map(map, y, x, '0', 'P');
	else if (map->map_2d[map->init_pos_y + y][map->init_pos_x + x] == 'C')
	{
		change_map(map, y, x, '0', 'P');
		map->collectibles_nbr--;
	}
	else if (map->map_2d[map->init_pos_y + y][map->init_pos_x + x] == 'E')
	{
		if (map->collectibles_nbr == 0)
		{
			printf("You win!\n");
			map->end = 1;
			return (1);
		}
		else
			printf("Collect all the collectibles!\n");
		change_map(map, y, x, '0', 'P');
		map->exit_deleted = 1;
	}
	return (0);
}
