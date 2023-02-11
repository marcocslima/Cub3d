/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:21:27 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/11 16:11:15 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_header_struct(t_game **game)
{
	int		i;
	char	**config;

	i = 0;
	while (i < (*game)->map->init_map)
	{
		config = ft_split((*game)->file[i], ' ');
		if (ft_strcmp_eq(config[0], "NO") || ft_strcmp_eq(config[0], "N"))
			(*game)->header->no = config;
		else if (ft_strcmp_eq(config[0], "SO") || ft_strcmp_eq(config[0], "S"))
			(*game)->header->so = config;
		else if (ft_strcmp_eq(config[0], "WE") || ft_strcmp_eq(config[0], "W"))
			(*game)->header->we = config;
		else if (ft_strcmp_eq(config[0], "EA") || ft_strcmp_eq(config[0], "E"))
			(*game)->header->ea = config;
		else if (ft_strcmp_eq(config[0], "FL") || ft_strcmp_eq(config[0], "F"))
			(*game)->header->f = config;
		else if (ft_strcmp_eq(config[0], "CE") || ft_strcmp_eq(config[0], "C"))
			(*game)->header->c = config;
		else
			free_matrix(config);
		i++;
	}
}

int	header_is_all_full(t_map_header *header)
{
	if (header->c == NULL || header->ea == NULL || header->f == NULL
		|| header->no == NULL || header->so == NULL || header->we == NULL)
		return (0);
	return (1);
}

void	get_header(t_game **game)
{
	fill_header_struct(game);
	if (!header_is_all_full((*game)->header))
	{
		print_error_msg("Missing identifier\n");
		free_cub3d(game);
		exit(1);
	}
}
