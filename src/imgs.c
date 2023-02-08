#include "../inc/so_long.h"

int	load_imgs(t_imgs **imgs, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		imgs[i] = malloc(sizeof(t_imgs));
		if (imgs[i] == NULL)
			return (-1);
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

void	print_data_img(t_imgs *img, t_mlx *mlx, int y, int x)
{
	int		i;
	int		j;
	int		size;
	char	*data;

	i = 0;
	j = 0;
	size = 0;
	data = mlx_get_data_addr(img->img, &mlx->bpp,
			&size, &mlx->endian);
	while (i < 80)
	{
		while (j < 80)
		{
			mlx->data[(y + i) * mlx->size + (x + j) * (mlx->bpp / 8)]
				= data[i * size + j * (mlx->bpp / 8)];
			mlx->data[(y + i) * mlx->size + (x + j) * (mlx->bpp / 8) + 1]
				= data[i * size + j * (mlx->bpp / 8) + 1];
			mlx->data[(y + i) * mlx->size + (x + j) * (mlx->bpp / 8) + 2]
				= data[i * size + j * (mlx->bpp / 8) + 2];
			j++;
		}
		j = 0;
		i++;
	}
}

