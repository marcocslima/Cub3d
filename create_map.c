/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:20:09 by alida-si          #+#    #+#             */
/*   Updated: 2023/01/29 20:21:01 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if(norm_line[i] == ' ')
			norm_line[i] = 'S';
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
