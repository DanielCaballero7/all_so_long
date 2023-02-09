#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../../mlx_linux/mlx.h"
# include "../../ft_printf/ft_printf/ft_printf.h"
# include "../../get_next_line/get_next_line/get_next_line.h"
# include "../../libft/libft/libft.h"
# include <errno.h>

typedef struct s_map {
	int		width;
	int		height;
	int		init_pos_x;
	int		init_pos_y;
	char	*map;
	char	**map_2d;
	int		collectibles_nbr;
	int		exit_deleted;
	int		end;
}	t_map;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size;
	int		endian;
}	t_mlx;

typedef struct s_imgs {
	void	*img;
	int		width;
	int		height;
}	t_imgs;

typedef struct s_links {
	t_map	*map;
	t_mlx	*mlx;
	t_imgs	**imgs;
}	t_links;

void	ft_mlx_init(t_mlx *mlx, t_map *map);

void	check_bad_ber(char *argv, t_map *map);

void	error_mandatory_chars(int end, int collectible, int init_pos);

void	check_bad_params(int argc, char *argv);

void	check_bad_chars(t_map *map);

void	check_mandatory_chars(t_map *map);

void	check_map_shape(t_map *map);

void	split_map(t_map *map);

void	is_closed(t_map *map);

int		find_init_pos(t_map *map);

int		find_path(char **map, int collectibles_nbr, int y, int x);

void	free_map(t_map *map);

void	draw_map(t_mlx *mlx, t_map *map, t_imgs **imgs);

int		ft_key_hook(int keycode, void *params);

void	ft_error(char *str);

void	read_ber(int fd, t_map *map);

int		move(t_map *map, int y, int x);

void	change_map(t_map *map, int y, int x, char a, char b);

int		load_imgs(t_imgs **imgs, t_mlx *mlx);

void	print_data_img(t_imgs *img, t_mlx *mlx, int y, int x);

void	split_map(t_map *map);

void	free_map(t_map *map);

void	free_t_mlx(t_mlx *mlx);

void	free_t_map(t_map *map);

void	free_t_imgs(t_imgs **imgs, t_mlx *mlx);

void	free_all(t_mlx *mlx, t_map *map, t_imgs **imgs, char *str);

void	init_params(t_links *params, t_mlx *mlx, t_map *map, t_imgs **imgs);

#endif