/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/01/29 20:23:29 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_file(int fd)
{
	char		*line;
	char		*ret;
	char		**file;

	ret = get_next_line(fd);
	check_file_line(ret);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		check_file_line(line);
		ret = ft_strjoin(ret, line);
		free(line);
	}
	close (fd);
	file = ft_split(ret, '\n');
	free(ret);
	return (file);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**file;
	t_map	*map;
	int		i;

	i = -1;
	fd  = check_input(argc, argv);
	file = read_file(fd);
	map = get_map(file);
	while(map->map[++i])
		printf("%s\n", map->map[i]);
	i = -1;
	//while(file[++i])
	//	free(file[i]);
	//free(file);
	return (0);
}
