/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:20:09 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/11 14:10:22 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*norm_line(char *line, int width)
{
	char	*norm_line;
	int		i;

	i = -1;
	norm_line = (char *)ft_calloc(width + 1, sizeof(char));
	while (++i < width)
	{
		if (i < ft_strlen(line))
			norm_line[i] = line[i];
		else
			norm_line[i] = ' ';
	}
	/*i = -1;
	while (++i < width)
	{
		if (i != 0 && norm_line[i - 1] == '0' && norm_line[i] == ' ')
			norm_line[i] = 'E';
		if (norm_line[i] == '1' || norm_line[i] == '0')
			continue ;
		else if (norm_line[i] == ' ' && norm_line[i + 1] != '0')
			norm_line[i] = '1';
		/else
			norm_line[i] = 'E';
	}*/
	return (norm_line);
}

char	**create_map_matrix(char **file, int init_map, int map_size, int width)
{
	int		i;
	int		j;
	char	**matrix;

	i = init_map;
	j = 0;
	matrix = (char **)malloc(((sizeof(char *)) * (map_size + 1)));
	while (file[i])
	{
		matrix[j] = norm_line(file[i], width);
		i++;
		j++;
	}
	*&matrix[j] = NULL;
	return (matrix);
}

void	*get_map(char **file, t_map **map)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (file[++i])
	{
		if (file[i][0] == ' ' || file[i][0] == '1' || file[i][0] == '0')
		{
			if ((*map)->init_map == 0)
				(*map)->init_map = i;
			if ((int)ft_strlen(file[i]) > (*map)->map_width)
				(*map)->map_width = ft_strlen(file[i]);
		}
	}
	(*map)->map_higth = i - (*map)->init_map;
	(*map)->map = create_map_matrix(file, (*map)->init_map,
			(*map)->map_higth, (*map)->map_width);
}
