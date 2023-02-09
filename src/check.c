/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaballe <dcaballe@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:49:11 by dcaballe          #+#    #+#             */
/*   Updated: 2023/02/09 19:49:13 by dcaballe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	check_bad_chars(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i] != '\0')
	{
		if (map->map[i] != 'P' && map->map[i] != 'E' && map->map[i] != 'C'
			&& map->map[i] != '1' && map->map[i] != '0' && map->map[i] != '\n')
		{
			free(map->map);
			free(map);
			ft_error("Error\nUnknown character in map");
		}
		i++;
	}
}

void	check_mandatory_chars(t_map *map)
{
	int	i;
	int	exit;
	int	init_pos;

	i = 0;
	exit = 0;
	map->collectibles_nbr = 0;
	init_pos = 0;
	while (map->map[i] != '\0')
	{
		if (map->map[i] == 'E')
			exit++;
		if (map->map[i] == 'C')
			map->collectibles_nbr++;
		if (map->map[i] == 'P')
			init_pos++;
		i++;
	}
	if (exit != 1 || map->collectibles_nbr < 1 || init_pos != 1)
	{
		i = map->collectibles_nbr;
		free(map->map);
		free(map);
		error_mandatory_chars(exit, i, init_pos);
	}
}

void	check_map_shape(t_map *map)
{
	int	i;
	int	lines;
	int	columns;

	i = 0;
	lines = 1;
	columns = 0;
	while (map->map[i] != '\0')
	{
		if (map->map[i] == '\n')
		{
			if (columns == 0)
				columns = i;
			lines++;
		}
		i++;
	}
	if (columns < 3 || lines < 3 || columns == lines)
	{
		free(map->map);
		free(map);
		ft_error("Error\nMap is incorrect");
	}
}

void	is_closed(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_2d[0][i] != '\0')
	{
		if ((map->map_2d[0][i] != '1')
			|| (map->map_2d[map->height - 1][i] != '1')
			|| (i < map->height && map->map_2d[i][0] != '1')
			|| (i < map->height && map->map_2d[i][map->width - 1] != '1'))
		{
			free_t_map(map);
			ft_error("Error\nMap is not closed");
		}
		i++;
	}
}
