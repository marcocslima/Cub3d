/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/06 10:28:10 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		free_matrix(file);
		file = NULL;
	}
	return (file);
}

void	init_data(t_game **game)
{
	t_map_header	*header;
	t_map			*map;

	header = (t_map_header *) malloc(sizeof(t_map_header));
	map = (t_map *) malloc(sizeof(t_map));
	map->map_higth = 0;
	map->map_width = 0;
	map->init_map = 0;
	map->map = NULL;
	*game = (t_game *) malloc(sizeof(t_game));
	(*game)->map = map;
	(*game)->header = header;
}

void	get_header(char **file, t_game **game)
{
	int		i;
	char	**config;

	i = 0;
	while (i < (*game)->map->init_map)
	{
		config = ft_split(file[i], ' ');
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
	while(game->map->map[++i])
		printf("%s\n", game->map->map[i]);
}

void verify_map(char **map, int height, int width)
{
	int	x;
	int	y;

	x = -1;
	y = -1;

	while(++y < width)
		if(map[0][y] != '1' || map[height - 1][y] != '1')
		{
			printf("Error: map needs to be closed...\n");
			exit(1);
		}
	x = -1;
	while(++x < height)
		if(map[x][0] != '1' || map[x][width - 1] != '1')
		{
			printf("Error: map needs to be closed...\n");
			exit(1);
		}
	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
			if(map[x][y] == 'E')
			{
				printf("Error: find error on map...\n");
				exit(1);
			}
	}
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**file;
	t_game	*game;

	fd = check_input(argc, argv);
	file = read_file(fd);
	if (file != NULL)
	{
		init_data(&game);
		get_map(file, &game->map);
		verify_map(game->map->map, game->map->map_higth, game->map->map_width);
		get_header(file, &game);
		print_whole_map(game);
		free_map_header(&game);
		free_matrix(game->map->map);
		free_matrix(file);
		free(game->header);
		free(game->map);
		free(game);
	}
	return (0);
}
