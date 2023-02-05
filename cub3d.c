/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/05 15:37:19 by alida-si         ###   ########.fr       */
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
	*map = (t_map *) malloc(sizeof(t_map));
	(*map)->map_higth = 0;
	(*map)->map_width = 0;
	(*map)->map = NULL;
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**file;
	t_map	*map;
	int		i;

	i = 0;
	fd = check_input(argc, argv);
	file = read_file(fd);
	if (file != NULL)
	{
		init_data(&map);
		get_map(file, &map);
		while(map->map[++i])
			printf("%s\n", map->map[i]);
		free_matrix(map->map);
		free_matrix(file);
		free(map);
	}
	return (0);
}
