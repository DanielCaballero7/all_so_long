#include "../inc/so_long.h"

int	check_bad_params(int argc, char *argv)
{
	if (argc != 2)
	{
		perror("Error\nNumber of arguments incorrect");
		exit(0);
	}
	if (ft_strlen(argv) < 5
		|| ft_strncmp(argv + ft_strlen(argv) - 4, ".ber", 4) != 0)
	{
		perror("Error\nFile extension is no ber");
		exit(0);
	}
	return (0);
}

int	read_ber(int fd, t_map *map)
{
	char	*line;

	map->map = ft_strdup("\0");
	line = NULL;
	while (get_next_line(fd, &line) != NULL)
	{
		map->map = ft_strjoin_free(map->map, line);
	}
	if (*(map->map) == '\0')
	{
		perror("Error\nEmpty file");
		free(map);
		exit(0);
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
			perror("Error\nUnknown character in map");
			exit(0);
		}
		i++;
	}
	return (0);
}

void	error_mandatory_chars(int end, int collectible, int init_pos)
{
	if (end > 1)
	{
		perror("Error\nToo many exits");
		exit(0);
	}
	else if (init_pos > 1)
	{
		perror("Error\nToo many initial positions");
		exit(0);
	}
	else if (collectible < 1)
	{
		perror("Error\nNo collectibles");
		exit(0);
	}
	else if (end < 1)
	{
		perror("Error\nNo exit");
		exit(0);
	}
	else if (init_pos < 1)
	{
		perror("Error\nNo initial position");
		exit(0);
	}
}

int	check_mandatory_chars(t_map *map)
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
		error_mandatory_chars(exit, map->collectibles_nbr, init_pos);
	return (0);
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
			perror("Error\nMap is not rectangular");
		else if (columns < 3 || lines < 3)
			perror("Error\nMap too small");
		exit(0);
	}
	return (0);
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
	//free(map->map);
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
	return (0);
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

void free_map(t_map *map)
{
	int i;

	i = 0;
	while (map->map_2d[i])
	{
		free(map->map_2d[i]);
		i++;
	}
	free(map->map_2d);
}

void printf_map(t_map *map)
{
	int i;

	i = 0;
	while (map->map_2d[i])
	{
		printf("%s\n", map->map_2d[i]);
		i++;
	}
}

int	check_bad_ber(char *argv, t_map *map)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nCould not open file");
		exit(0);
	}
	read_ber(fd, map);
	check_bad_chars(map);
	check_mandatory_chars(map);
	check_map_shape(map);
	split_map(map);
	is_closed(map);
	find_init_pos(map);
	if (find_path(map->map_2d, map->collectibles_nbr,
			map->init_pos_y, map->init_pos_x) == 0)
	{
		perror("Error\nNo path to exit");
		exit(0);
	}
	free_map(map);
	split_map(map);
	//free(map);
	return (0);
}

int load_imgs(t_imgs **imgs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		imgs[i] = malloc(sizeof(t_imgs));
		if (imgs[i] == NULL)
		{
			perror("Error\nCould not make imgs");
			return (-1);
		}
		i++;
	}
	imgs[0]->img = mlx_xpm_file_to_image(mlx->mlx, "imgs/wall.xpm",
			&imgs[0]->width, &imgs[0]->height);
	imgs[1]->img = mlx_xpm_file_to_image(mlx->mlx, "imgs/path.xpm",
			&imgs[1]->width, &imgs[1]->height);
	imgs[2]->img = mlx_xpm_file_to_image(mlx->mlx, "imgs/paulinol1.xpm",
			&imgs[2]->width, &imgs[2]->height);
	imgs[3]->img = mlx_xpm_file_to_image(mlx->mlx, "imgs/selene.xpm",
			&imgs[3]->width, &imgs[3]->height);
	imgs[4]->img = mlx_xpm_file_to_image(mlx->mlx, "imgs/exit.xpm",
			&imgs[4]->width, &imgs[4]->height);
	return (0);
}

int print_data_img(t_imgs *img, t_mlx *mlx, int y, int x)
{
	int i;
	int j;
	int size;
	char *data;

	i = 0;
	j = 0;
	size = 0;
	data = mlx_get_data_addr(img->img, &mlx->bits_per_pixel, &size, &mlx->endian);
	while (i < 80)
	{
		while (j < 80)
		{
			mlx->data[(y + i) * mlx->line_length + (x + j) * (mlx->bits_per_pixel / 8)] = data[i * size + j * (mlx->bits_per_pixel / 8)];
			mlx->data[(y + i) * mlx->line_length + (x + j) * (mlx->bits_per_pixel / 8) + 1] = data[i * size + j * (mlx->bits_per_pixel / 8) + 1];
			mlx->data[(y + i) * mlx->line_length + (x + j) * (mlx->bits_per_pixel / 8) + 2] = data[i * size + j * (mlx->bits_per_pixel / 8) + 2];
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int draw_map(t_mlx *mlx, t_map *map, t_imgs **imgs)
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
	return (0);
}

int	change_map(t_map *map, int y, int x, char a, char b)
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
	return (0);
}

int move(t_map *map, int y, int x)
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
			exit(0);
		}
		else
			printf("Collect all the collectibles!\n");
		change_map(map, y, x, '0', 'P');
		map->exit_deleted = 1;
	}
	return (0);
}

int key_hook(int key, void *params)
{
	t_links	*links;

	links = (t_links *)params;
	if (key == 65307)
		exit(0);
	if (key == 119)
		move(links->map, -1, 0);
	if (key == 115)
		move(links->map, 1, 0);
	if (key == 97)
		move(links->map, 0, -1);
	if (key == 100)
		move(links->map, 0, 1);
	draw_map(links->mlx, links->map, links->imgs);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;
	t_imgs	*imgs[5];
	t_links	*params;

	map = malloc(sizeof(t_map));
	if (check_bad_params(argc, argv[1]) == -1
		|| check_bad_ber(argv[1], map) == -1)
	{
		return (-1);
	}
	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = NULL;
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		perror("Error\nCould not initialize mlx");
		return (-1);
	}
	mlx->win = mlx_new_window(mlx->mlx, map->width * 80,
			map->height * 80, "so_long");
	if (mlx->win == NULL)
	{
		perror("Error\nCould not create window");
		return (-1);
	}
	mlx->img = mlx_new_image(mlx->mlx, map->width * 80, map->height * 80);
	if (mlx->img == NULL)
	{
		perror("Error\nCould not create image");
		return (-1);
	}
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (mlx->data == NULL)
	{
		perror("Error\nCould not get data address");
		return (-1);
	}
	load_imgs(imgs, mlx);
	draw_map(mlx, map, imgs);
	params = malloc(sizeof(t_links));
	params->mlx = mlx;
	params->map = map;
	params->imgs = imgs;
	mlx_key_hook(mlx->win, key_hook, (void *)params);
	mlx_loop(mlx->mlx);
	//free(mlx->mlx);
	return (0);
}

/*int	main(int argc, char **argv)
{
	check_bad_params(argc, argv[1]);
	check_bad_ber(argv[1]);
}
*/