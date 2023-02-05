/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:20:09 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/05 16:05:09 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == ' ')
				map[i][j] = 'S';
			j++;
		}
		i++;
	}
}

char	**create_map_matrix(char **file, int init_map, int map_size)
{
	int		i;
	int		j;
	char	**matrix;

	i = init_map;
	j = 0;
	matrix = (char **)malloc(((sizeof(char *)) * (map_size + 1)));
	while (file[i])
	{
		matrix[j] = ft_substr(file[i], 0, ft_strlen(file[i]));
		i++;
		j++;
	}
	*&matrix[j] = NULL;
	return (matrix);
}

void *get_map(char **file, t_map **map)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while(file[++i])
	{
		if(file[i][0] == ' ' || file[i][0] == '1')
		{
			if ((*map)->init_map == 0)
				(*map)->init_map = i;
			if ((int)ft_strlen(file[i]) > (*map)->map_width)
				(*map)->map_width = ft_strlen(file[i]);
		}
	}
	(*map)->map_higth = i - (*map)->init_map;
	(*map)->map = create_map_matrix(file, (*map)->init_map, (*map)->map_higth);
	normalize_map((*map)->map);
}
