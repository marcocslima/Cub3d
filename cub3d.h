/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:11:12 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/08 20:32:10 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <math.h>
//# include "mlx.h"
# include "./libraries/libft/libft.h"
# include "./libraries/minilibx-linux/mlx.h"

# define WIDTH 1024
# define HEIGHT 768
# define TRUE 1
# define FALSE 0
# define PI 3.14159265359
# define TILE_SIZE 512
# define UP 1
# define DOWN 0
# define RIGHT 2
# define LEFT 3
# define W	119
# define S	115
# define D	100
# define A	97

# define RED "\033[38;2;222;56;43m"
# define RESET "\033[0m"

typedef struct s_map_header
{
	char	**no;
	char	**so;
	char	**we;
	char	**ea;
	char	**f;
	char	**c;
}	t_map_header;

typedef struct s_map
{
	int		init_map;
	int		map_width;
	int		map_higth;
	char	**map;
}	t_map;

typedef struct s_game
{
	t_map_header	*header;
	t_map			*map;
	char			**file;
}	t_game;

int		check_file_line(char *line);
int		check_input(int argc, char **argv);
void	*get_map(char **file, t_map **map);
void	print_error_exit(t_game **game, char *msg);
void	print_error_msg(char *msg);
void	free_matrix(char **ptr);
void	free_map_header(t_map_header **header);
void	init_data(t_game **game);
void	free_cub3d(t_game **game);
void	get_header(t_game **game);

//test
void	print_whole_map(t_game *game);

#endif
