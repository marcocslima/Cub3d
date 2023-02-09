/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/08 20:18:05 by alida-si         ###   ########.fr       */
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

int	header_is_all_full(t_map_header *header)
{
	if (header->c == NULL || header->ea == NULL || header->f == NULL
		|| header->no == NULL || header->so == NULL || header->we == NULL)
		return (0);
	return (1);
}

/*void	fill_header_struct(char )
{

}*/

void	free_cub3d(t_game **game)
{
	free_map_header(&(*game)->header);
	free_matrix((*game)->map->map);
	free_matrix((*game)->file);
	free((*game)->header);
	free((*game)->map);
	free(*game);
}

void	fill_header_struct(t_game **game)
{
	int		i;
	char	**config;

	i = 0;
	while (i < (*game)->map->init_map)
	{
		config = ft_split((*game)->file[i], ' ');
		if (ft_strcmp_eq(config[0], "NO") || ft_strcmp_eq(config[0], "N"))
			(*game)->header->no = config;
		if (ft_strcmp_eq(config[0], "SO") || ft_strcmp_eq(config[0], "S"))
			(*game)->header->so = config;
		if (ft_strcmp_eq(config[0], "WE") || ft_strcmp_eq(config[0], "W"))
			(*game)->header->we = config;
		if (ft_strcmp_eq(config[0], "EA") || ft_strcmp_eq(config[0], "E"))
			(*game)->header->ea = config;
		if (ft_strcmp_eq(config[0], "FL") || ft_strcmp_eq(config[0], "F"))
			(*game)->header->f = config;
		if (ft_strcmp_eq(config[0], "CE") || ft_strcmp_eq(config[0], "C"))
			(*game)->header->c = config;
		i++;
	}
}

void	get_header(t_game **game)
{
	fill_header_struct(game);
	if (!header_is_all_full((*game)->header))
	{
		print_error_msg("Missing identifier\n");
		free_cub3d(game);
		exit(1);
	}
}

void	print_whole_map(t_game *game)
{
	int	i;

	i = -1;
	printf("HEADER\n");
	printf("%s  %s\n", game->header->no[0], game->header->no[1]);
	printf("%s  %s\n", game->header->so[0], game->header->so[1]);
	printf("%s  %s\n", game->header->we[0], game->header->we[1]);
	printf("%s  %s\n", game->header->ea[0], game->header->ea[1]);
	printf("%s   %s\n", game->header->f[0], game->header->f[1]);
	printf("%s   %s\n\n", game->header->c[0], game->header->c[1]);
	printf("MAP\n");
	while (game->map->map[++i])
		printf("%s\n", game->map->map[i]);
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
