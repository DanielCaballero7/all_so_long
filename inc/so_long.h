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
}	t_map;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
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
#endif