/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:20:09 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/16 13:59:47 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*norm_line(char *line, int width)
{
	char	*norm_line;
	int		i;

	i = -1;
	norm_line = (char *)ft_calloc(width + 1, sizeof(char));
	while (++i < width)
	{
		if (i < (int)ft_strlen(line))
			norm_line[i] = line[i];
		else
			norm_line[i] = ' ';
	}
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

void	get_map(char **file, t_map **map)
{
	int		i;

	i = -1;
	while (file[++i])
	{
		if (file[i][0] == ' ' || file[i][0] == '1' || file[i][0] == '0')
		{
			if ((*map)->init == 0)
				(*map)->init = i;
			if ((int)ft_strlen(file[i]) > (*map)->width)
				(*map)->width = ft_strlen(file[i]);
		}
	}
	(*map)->height = i - (*map)->init;
	(*map)->matrix = create_map_matrix(file, (*map)->init,
			(*map)->height, (*map)->width);
}
