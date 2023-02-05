/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/05 16:39:29 by alida-si         ###   ########.fr       */
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

void	init_data(t_map **map)
{
	t_map_header	*header;

	header = (t_map_header *) malloc(sizeof(t_map_header));
	header->no = NULL;
	header->so = NULL;
	header->we = NULL;
	header->ea = NULL;
	header->f = NULL;
	header->c = NULL;
	*map = (t_map *) malloc(sizeof(t_map));
	(*map)->map_higth = 0;
	(*map)->map_width = 0;
	(*map)->init_map = 0;
	(*map)->map = NULL;
	(*map)->map_header = header;
}

void	get_header(char **file, t_map **map)
{
	int		i;
	char	**config;

	i = 0;
	while (i < (*map)->init_map)
	{
		config = ft_split(file[i], ' ');
		if (ft_strcmp_eq(config[0], "NO") || ft_strcmp_eq(config[0], "N"))
			(*map)->map_header->no = config;
		if (ft_strcmp_eq(config[0], "SO") || ft_strcmp_eq(config[0], "S"))
			(*map)->map_header->so = config;
		if (ft_strcmp_eq(config[0], "WE") || ft_strcmp_eq(config[0], "W"))
			(*map)->map_header->we = config;
		if (ft_strcmp_eq(config[0], "EA") || ft_strcmp_eq(config[0], "E"))
			(*map)->map_header->ea = config;
		if (ft_strcmp_eq(config[0], "FL") || ft_strcmp_eq(config[0], "F"))
			(*map)->map_header->f = config;
		if (ft_strcmp_eq(config[0], "CE") || ft_strcmp_eq(config[0], "C"))
			(*map)->map_header->c = config;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**file;
	t_map	*map;
	int		i;

	i = -1;
	fd = check_input(argc, argv);
	file = read_file(fd);
	if (file != NULL)
	{
		init_data(&map);
		get_map(file, &map);
		get_header(file, &map);
		//while(map->map[++i])
		//	printf("%s\n", map->map[i]);
		free_map_header(&map);
		free_matrix(map->map);
		free_matrix(file);
		free(map->map_header);
		free(map);
	}
	return (0);
}
