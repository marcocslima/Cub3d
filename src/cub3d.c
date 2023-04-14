/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/04/13 22:11:38 by alida-si         ###   ########.fr       */
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

void	parser(t_game **game)
{
	get_map((*game)->file, &(*game)->map);
	get_header(game);
	check_header(game);
	verify_map(game);
}

void	init_window_img(t_game **game)
{
	(*game)->img_data->mlx_img = mlx_new_image((*game)->mlx_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	(*game)->img_data->addr = mlx_get_data_addr((*game)->img_data->mlx_img,
			&(*game)->img_data->bpp, &(*game)->img_data->line_len,
			&(*game)->img_data->endian);
}

void	game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx_data->mlx_ptr, &render, game);
	mlx_hook(game->mlx_data->mlx_win, 17, 1L << 17, close_window, game);
	mlx_hook(game->mlx_data->mlx_win, 02, 1L << 0, handle_events, game);
	mlx_loop(game->mlx_data->mlx_ptr);
}

void	get_ceiling_rgb(t_game *game)
{
	char	**temp;
	int		r;
	int		g;
	int		b;

	temp = ft_split(game->header->c, ',');
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	game->texture_img->c = (r << 16 | g << 8 | b);
	free_matrix(temp);

}

void	get_floor_rgb(t_game *game)
{
	char	**temp;
	int		r;
	int		g;
	int		b;

	temp = ft_split(game->header->f, ',');
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	game->texture_img->f = (r << 16 | g << 8 | b);
	free_matrix(temp);

}

void	get_background_rgb(t_game *game)
{
	get_ceiling_rgb(game);
	get_floor_rgb(game);

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
		parser(&game);
		init_data_mlx(&game->mlx_data);
		init_window_img(&game);
		init_textures(&game);
		get_background_rgb(game);
		get_player_position(&game);
		game_loop(game);
	}
	free_cub3d(&game);
	return (0);
}
