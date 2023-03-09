/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/03/08 20:12:30 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_file(int fd, t_game **game)
{
	char		*line;
	char		*ret;

	ret = get_next_line(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = ft_strjoin(ret, line);
		free(line);
	}
	close (fd);
	verify_empty_lines(ret, game);
	(*game)->file = ft_split(ret, '\n');
	free(ret);
}

/*void	plot_map(t_game *game)
{
	int	i;
	int	j;
	int	color;
	int	side;

	i = -1;
	//side = data->l_side;
	while(++i < game->map->map_higth)
	{
		j = -1;
		while(++j < game->map->map_width)
		{
			color = COLOR_BLACK;
			if(game->map->map[i][j] == '1')
				color = COLOR_RED;
			if(game->map->map[i][j] == '0' || game->map->map[i][j] == 'N')
				color = COLOR_YELLOW;
			render_rect(game, (t_rect){j * side, i * side, side, side, color});
			render_rect(&data->img, (t_rect){data->game->player.pos[0] * side, data->gm->player.pos[1] * side, 5, 5, RED_PIXEL});
			//render_rect(&data->img, (t_rect){data->gm->player.pos[0] * side + data->gm->player.dir[0], data->gm->player.pos[1] * side + data->gm->player.dir[1], 4, 4, BLUE_PIXEL});
			float d = 0.1;
			while(d < 1)
			{
				render_rect(&data->img, (t_rect){data->gm->player.pos[0] * side + data->gm->player.dir[0] * d, data->gm->player.pos[1] * side + data->gm->player.dir[1] * d, 2, 2, BLUE_PIXEL});
				d = d + 0.02;
			}
			//render_rect(&data->img, (t_rect){j * side, i * side, 1, side, BLUE_SKY_PIXEL});
			//render_rect(&data->img, (t_rect){j * side, i * side, side, 1, BLUE_SKY_PIXEL});
		}
	}
}*/

int	handle_events(int key_code, t_game *game)
{
	if (key_code == 65307)
		close_window(game);
	if (key_code == W)
		*&game->img_data->y_position -= 5;
	if (key_code == S)
		*&game->img_data->y_position += 5;
	if (key_code == A)
		*&game->img_data->x_position -= 5;
	if (key_code == D)
		*&game->img_data->x_position += 5;
	render(game);
	return (1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	*game;

	fd = check_input(argc, argv);
	init_data(&game);
	read_file(fd, &game);
	if (game->file != NULL)
	{
		get_map(game->file, &game->map);
		get_header(&game);
		check_header(&game);
		verify_map(&game);
		//print_whole_map(game);

		game->img_data->mlx_img = mlx_new_image(game->mlx_data->mlx_ptr, 500, 500);
		game->img_data->addr = mlx_get_data_addr(game->img_data->mlx_img, &game->img_data->bpp, &game->img_data->line_len, &game->img_data->endian);

		mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
		mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
		mlx_hook(game->mlx_data->mlx_win, 02, 1L << 0, handle_events, game);
		mlx_loop(game->mlx_data->mlx_ptr);
	}
	free_cub3d(&game);
	return (0);
}
