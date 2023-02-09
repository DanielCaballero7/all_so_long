#include "../inc/so_long.h"

void	read_ber(int fd, t_map *map)
{
	char	*line;

	map->map = ft_strdup("\0");
	line = NULL;
	while (get_next_line(fd, &line) != NULL && map->map != 0)
	{
		map->map = ft_strjoin_free(map->map, line);
	}
	if (map->map == 0)
	{
		free_t_map(map);
		ft_error("Error\nMalloc failed");
	}
	if (*(map->map) == '\0')
	{
		free_t_map(map);
		ft_error("Error\nEmpty file");
	}
	close(fd);
}

int	find_init_pos(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->map_2d[y])
	{
		while (map->map_2d[y][x] != '\0')
		{
			if (map->map_2d[y][x] == 'P')
			{
				map->init_pos_x = x;
				map->init_pos_y = y;
				return (0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	free(map->map);
	ft_free_split(map->map_2d);
	free(map);
	ft_error("Error\nNo player found");
	return (-1);
}

int	find_path(char **map, int collectibles, int y, int x)
{
	static int	i;
	static int	exit;

	if (!i && !exit)
	{
		exit = 0;
		i = 0;
	}
	if (map[y][x] == '1')
		return (0);
	else if (map[y][x] == 'E')
		exit = 1;
	else if (map[y][x] == 'C')
		i++;
	map[y][x] = '1';
	if (collectibles == i && exit == 1)
		return (1);
	else if (find_path(map, collectibles, y, x + 1) == 1
		|| (find_path(map, collectibles, y, x - 1) == 1)
		|| (find_path(map, collectibles, y + 1, x) == 1)
		|| (find_path(map, collectibles, y - 1, x) == 1))
		return (1);
	return (0);
}

int	ft_key_hook(int key, void *params)
{
	t_links	*links;

	links = (t_links *)params;
	if (key == 119)
		move(links->map, -1, 0);
	else if (key == 115)
		move(links->map, 1, 0);
	else if (key == 97)
		move(links->map, 0, -1);
	else if (key == 100)
		move(links->map, 0, 1);
	if (key == 65307 || links->map->end == 1)
	{
		mlx_destroy_window(links->mlx->mlx, links->mlx->win);
		mlx_destroy_image(links->mlx->mlx, links->imgs[0]->img);
		mlx_destroy_image(links->mlx->mlx, links->imgs[1]->img);
		mlx_destroy_image(links->mlx->mlx, links->imgs[2]->img);
		mlx_destroy_image(links->mlx->mlx, links->imgs[3]->img);
		mlx_destroy_image(links->mlx->mlx, links->imgs[4]->img);
		mlx_destroy_image(links->mlx->mlx, links->mlx->img);
		free(links->imgs[0]);
		free(links->imgs[1]);
		free(links->imgs[2]);
		free(links->imgs[3]);
		free(links->imgs[4]);
		mlx_destroy_display(links->mlx->mlx);
		free(links->mlx->mlx);
		free(links->mlx);
		free(links->map->map);
		ft_free_split(links->map->map_2d);
		free(links->map);
		free(links);
		exit(0);
	}
	draw_map(links->mlx, links->map, links->imgs);
	return (0);
}

void	ft_error(char *str)
{
	perror(str);
	exit(0);
}
