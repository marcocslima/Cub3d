/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:22:44 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/12 21:15:14 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_file(char **file)
{
	free_matrix(file);
	file = NULL;
}

void	free_matrix(char **ptr)
{
	int	i;

	if (ptr != NULL)
	{
		i = 0;
		while (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
	}
}

void	free_map_header(t_map_header **header)
{
	free_matrix((*header)->no);
	free_matrix((*header)->so);
	free_matrix((*header)->we);
	free_matrix((*header)->ea);
	free_matrix((*header)->f);
	free_matrix((*header)->c);
}

void	free_cub3d(t_game **game)
{
	free_map_header(&(*game)->header);
	free_matrix((*game)->map->map);
	free_matrix((*game)->file);
	free((*game)->header);
	free((*game)->map);
	free(*game);
}
