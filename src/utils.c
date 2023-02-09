/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:49:25 by dcaballe          #+#    #+#             */
/*   Updated: 2023/02/09 19:49:27 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free(map->map);
		free(map);
		ft_error("Error\nMalloc failed");
	}
	if (*(map->map) == '\0')
	{
		free(map->map);
		free(map);
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
	t_links		*links;

	links = (t_links *)params;
	if (key == 13)
		move(links->map, -1, 0);
	else if (key == 1)
		move(links->map, 1, 0);
	else if (key == 0)
		move(links->map, 0, -1);
	else if (key == 2)
		move(links->map, 0, 1);
	if (key == 53 || links->map->end == 1)
	{
		free_all_move(links->mlx, links->map, links->imgs);
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
