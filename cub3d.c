/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/01/29 07:46:01 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_exit(char *input)
{
	printf("%s\n", input);
	exit (1);
}

int	check_input(int argc, char **argv)
{
	int		len_entry;
	int		fd;
	char	*is_cub;

	len_entry = ft_strlen(argv[1]);
	if(argc != 2)
		print_exit("Error: wrong number of arguments");
	is_cub = ft_substr(argv[1], (len_entry - 4), 5);
	if (ft_strncmp(is_cub, ".cub", 5))
	{
		free(is_cub);
		print_exit("Error: map file needs to be .cub");
	}
	free(is_cub);
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		print_exit("Error: file can´t be a directory");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_exit("Error: map can´t be found");
	return (fd);
}

char	**read_file(int fd)
{
	char		*line;
	char		*ret;
	char		**file;

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
	file = ft_split(ret, '\n');
	free(ret);
	return (file);
}

char *norm_line(char *line, int width)
{
	char 	*norm_line;
	int		i;

	i = -1;
	norm_line = (char *)calloc(width + 1, sizeof(char));
	while(++i < width)
	{
		if(line[i])
			norm_line[i] = line[i];
		else
			norm_line[i] = ' ';
	}
	i = -1;
	while(++i < width)
		if(norm_line[i] == '1')
			norm_line[i] = '1';
		else if((norm_line[i] == ' ' && norm_line[i + 1] != '0')
			|| norm_line[i] == '1')
			norm_line[i] = '1';
		else if(norm_line[i] == '0')
			norm_line[i] = '0';
		else
			norm_line[i] = 'E';
	free(line);
	return(norm_line);
}

t_map *get_map(char **file)
{
	t_map	*map;
	int		i;
	int		j;
	int		init_map;

	i = -1;
	j = -1;
	init_map = 0;
	map = (t_map *)malloc(sizeof(t_map));
	map->map_width = 0;
	while(file[++i])
	{
		if(file[i][0] == ' ' || file[i][0] == '1')
		{	
			if (init_map == 0)
				init_map = i;
			if ((int)ft_strlen(file[i]) > map->map_width)
				map->map_width = ft_strlen(file[i]);
		}
	}
	map->map_higth = i - init_map;
	map->map = malloc(sizeof(char *) * map->map_higth);
	while (++j < map->map_higth)
		map->map[j] = norm_line(file[init_map++], map->map_width);
	return (map);
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
			printf("Error: map needs to be closed...");
			exit(1);
		}
	x = -1;
	while(++x < height)
		if(map[x][0] != '1' || map[x][width - 1] != '1')
		{
			printf("Error: map needs to be closed...");
			exit(1);
		}
	x = -1;
	while (++x < height)
	{
		y = -1;
		while (++y < width)
			if(map[x][y] == 'E')
			{
				printf("Error: map needs to be closed...");
				exit(1);
			}
	}
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**file;
	t_game	*game;
	int i;

	game = (t_game *)malloc(sizeof(t_game));
	fd  = check_input(argc, argv);
	file = read_file(fd);
	game->map = get_map(file);
	verify_map(game->map->map, game->map->map_higth, game->map->map_width);
	printf("\n");
	i = -1;
	while(++i < game->map->map_higth)
		free(game->map->map[i]);
	free(game->map->map);
	free(game->map);
	free(game);
	free(file[0]);
	free(file[1]);
	free(file[2]);
	free(file[3]);
	free(file[4]);
	free(file[5]);
	free(file);
	return (0);
}
