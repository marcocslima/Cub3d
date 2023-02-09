/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/08 20:31:18 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_file(char **file)
{
	free_matrix(file);
	file = NULL;
}

char	**read_file(int fd)
{
	char		*line;
	char		*ret;
	char		**file;
	int			check_flag;

	check_flag = 0;
	ret = get_next_line(fd);
	check_flag += check_file_line(ret);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		check_flag += check_file_line(line);
		ret = ft_strjoin(ret, line);
		free(line);
	}
	close (fd);
	file = ft_split(ret, '\n');
	free(ret);
	if (check_flag > 0)
		free_file(file);
	return (file);
}

void	verify_map(char **map, int height, int width)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < width)
	{
		if (map[0][y] != '1' || map[height - 1][y] != '1')
		{
			printf("Error: map needs to be closed...\n");
			exit(1);
		}
	}
	x = -1;
	while (++x < height)
	{
		if (map[x][0] != '1' || map[x][width - 1] != '1')
		{
			printf("Error: map needs to be closed...\n");
			exit(1);
		}
	}
	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
		{
			if (map[x][y] == 'E')
			{
				printf("Error: find error on map...\n");
				exit(1);
			}
		}
	}
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	*game;

	fd = check_input(argc, argv);
	init_data(&game);
	game->file = read_file(fd);
	if (game->file != NULL)
	{
		get_map(game->file, &game->map);
		verify_map(game->map->map, game->map->map_higth, game->map->map_width);
		get_header(&game);
		print_whole_map(game);
		free_cub3d(&game);
	}
	return (0);
}
