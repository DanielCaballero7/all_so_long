#include "../inc/so_long.h"

void	free_t_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window (mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display (mlx->mlx);
		free (mlx->mlx);
		free (mlx);
	}
	if (mlx->img)
		mlx_destroy_image (mlx->mlx, mlx->img);
}

void	free_t_map(t_map *map)
{
	if (map->map)
		free (map->map);
	if (map->map_2d)
		ft_free_split(map->map_2d);
	if (map)
		free (map);
}

void	free_t_imgs(t_imgs **imgs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (imgs[i] && imgs[i]->img)
		{
			mlx_destroy_image (mlx->mlx, imgs[i]->img);
			free (imgs[i]->img);
		}
		i++;
	}
}

void	free_all(t_mlx *mlx, t_map *map, t_imgs **imgs, char *str)
{
	free_t_imgs(imgs, mlx);
	free_t_mlx(mlx);
	free_t_map(map);
	ft_error(str);
}

void	init_params(t_links *params, t_mlx *mlx, t_map *map, t_imgs **imgs)
{
	map->exit_deleted = 0;
	map->end = 0;
	params->mlx = mlx;
	params->map = map;
	params->imgs = imgs;
}