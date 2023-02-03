#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
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
}	t_map;

#endif