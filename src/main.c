#include "../inc/so_long.h"

void	check_bad_params(int argc, char *argv)
{
	if (argc != 2)
		ft_error("Error\nNumber of arguments incorrect");
	if (ft_strlen(argv) < 5
		|| ft_strncmp(argv + ft_strlen(argv) - 4, ".ber", 4) != 0)
		ft_error("Error\nFile extension is no ber");
}

void	error_mandatory_chars(int end, int collectible, int init_pos)
{
	if (end > 1)
		ft_error("Error\nToo many exits");
	else if (init_pos > 1)
		perror("Error\nToo many initial positions");
	else if (collectible < 1)
		perror("Error\nNo collectibles");
	else if (end < 1)
		perror("Error\nNo exit");
	else if (init_pos < 1)
		perror("Error\nNo initial position");
}

void	check_bad_ber(char *argv, t_map *map)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		free(map);
		ft_error("Error\nCould not open file");
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
		free(map->map);
		ft_free_split(map->map_2d);
		free(map);
		ft_error("Error\nNo path to exit");
	}
	free_map(map);
	split_map(map);
}

void	ft_mlx_init(t_mlx *mlx, t_map *map)
{
	mlx->win = mlx_new_window(mlx->mlx, map->width * 80,
			map->height * 80, "so_long");
	if (mlx->win == NULL)
	{
		free (mlx->mlx);
		free (mlx);
		free (map->map);
		ft_free_split(map->map_2d);
		free (map);
		ft_error("Error\nCould not create window");
	}
	mlx->img = mlx_new_image(mlx->mlx, map->width * 80, map->height * 80);
	if (mlx->img == NULL)
	{
		free (mlx->mlx);
		free (mlx);
		free (map->map);
		ft_free_split(map->map_2d);
		free (map);
		ft_error("Error\nCould not create image");
	}
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->size, &mlx->endian);
	if (mlx->data == NULL)
	{
		free (mlx->mlx);
		free (mlx);
		free (map->map);
		ft_free_split(map->map_2d);
		free (map);
		ft_error("Error\nCould not get data address");
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;
	t_imgs	*imgs[5];
	t_links	*params;

	check_bad_params(argc, argv[1]);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error("Error\nCould not allocate memory");
	check_bad_ber(argv[1], map);
	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		free (mlx->mlx);
		free (mlx);
		free (map->map);
		ft_free_split(map->map_2d);
		free (map);
		ft_error("Error\nCould not initialize mlx");
	}
	ft_mlx_init(mlx, map);
	if (load_imgs(imgs, mlx) == -1)
	{
		free (mlx->mlx);
		free (mlx);
		free (map->map);
		ft_free_split(map->map_2d);
		free (map);
		ft_error("Error\nCould not load images");
	}
	draw_map(mlx, map, imgs);
	params = malloc(sizeof(t_links));
	if (!params)
	{
		free (mlx->mlx);
		free (mlx);
		free (map->map);
		ft_free_split(map->map_2d);
		free (map);
		ft_error("Error\nCould not allocate memory");
	}
	map->exit_deleted = 0;
	map->end = 0;
	params->mlx = mlx;
	params->map = map;
	params->imgs = imgs;
	mlx_key_hook(mlx->win, ft_key_hook, (void *)params);
	mlx_loop(mlx->mlx);
	return (0);
}

/*int	main(int argc, char **argv)
{
	t_mlx	mlx;

	check_bad_params(argc, argv[1]);
	mlx.mlx = mlx_init();
	mlx_destroy_display(mlx.mlx);
	free (mlx.mlx);
}*/
