#include "../inc/so_long.h"

int	check_bad_params(int argc, char *argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nNumber of arguments incorrect", 1);
		return (-1);
	}
	if (ft_strlen(argv) < 5
		|| ft_strncmp(argv + ft_strlen(argv) - 4, ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nFile extension is no ber", 1);
		return (-1);
	}
	return (0);
}

int	read_ber(int fd, t_map *map)
{
	char	*line;

	map->map = ft_strdup("\0");
	line == NULL;
	while (get_next_line(fd, &line) > 0)
	{
		map->map = ft_strjoin_free(map->map, line);
	}
	if (*(map->map) == '\0')
	{
		ft_putstr_fd("Error\nEmpty file", 1);
		free(map);
		return (-1);
	}
	return (0);
}

int	check_bad_chars(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i] != '\0')
	{
		if (map->map[i] != 'P' && map->map[i] != 'E' && map->map[i] != 'C'
			&& map->map[i] != '1' && map->map[i] != '0' && map->map[i] != '\n')
		{
			ft_putstr_fd("Error\nUnknown character in map", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	error_mandatory_chars(int exit, int collectible, int init_pos)
{
	if (exit > 1)
		ft_putstr_fd("Error\nToo many exits", 1);
	else if (init_pos > 1)
		ft_putstr_fd("Error\nToo many initial positions", 1);
	else if (collectible < 1)
		ft_putstr_fd("Error\nNo collectibles", 1);
	else if (exit < 1)
		ft_putstr_fd("Error\nNo exit", 1);
	else if (init_pos < 1)
		ft_putstr_fd("Error\nNo initial position", 1);
}

int	check_mandatory_chars(t_map *map)
{
	int	i;
	int	exit;
	int	collectible;
	int	init_pos;

	i = 0;
	exit = 0;
	collectible = 0;
	init_pos = 0;
	while (map->map[i] != '\0')
	{
		if (map->map[i] == 'E')
			exit++;
		if (map->map[i] == 'C')
			collectible++;
		if (map->map[i] == 'P')
			init_pos++;
		i++;
	}
	if (exit != 1 || collectible < 1 || init_pos != 1)
	{
		error_mandatory_chars(exit, collectible, init_pos);
		return (-1);
	}
}

int	check_map_shape(t_map *map)
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
			lines++;
		i++;
	}
	columns = (i - lines) / lines;
	if (columns < 3 || lines < 3 || columns == lines)
	{
		if (columns == lines)
			ft_putstr_fd("Error\nMap is not rectangular", 1);
		else if (columns < 3 || lines < 3)
			ft_putstr_fd("Error\nMap too small", 1);
		return (-1);
	}
}

int	split_map(t_map *map)
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
		perror("Error\nCould not split map");
		return (-1);
	}
	free(map->map);
	return (0);
}

int	is_closed(t_map *map)
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
			perror("Error\nMap is not closed");
			return (-1);
		}
		i++;
	}
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
	return (-1);
}

int	find_path(t_map *map)
{
	find_init_pos(map);
}

int	check_bad_ber(char *argv, t_map *map)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCould not open file", 1);
		return (-1);
	}
	map = malloc(sizeof(t_map));
	read_ber(fd, map);
	check_bad_chars(map);
	check_mandatory_chars(map);
	check_map_shape(map);
	split_map(map);
	is_closed(map);
	find_path(map);
	/*while (map->height >= 0)
	{
		free(map->map_2d[map->height]);
		map->height--;
	}
	free(map->map_2d);
	free(map);
	*/
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (check_bad_params(argc, argv[1]) == -1
		|| check_bad_ber(argv[1], map) == -1)
	{
		return (-1);
	}
	return (0);
}

/*int	main(int argc, char **argv)
{
	check_bad_params(argc, argv[1]);
	check_bad_ber(argv[1]);
}
*/