/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:21:27 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 16:37:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	save_value(char **header_element, char *config)
{
	if (*header_element != NULL)
		free(*header_element);
	*header_element = config;
}

int	parse_header_data(t_game **game, char **config)
{
	if (ft_strcmp_eq(config[0], "NO") || ft_strcmp_eq(config[0], "N"))
		save_value(&(*game)->header->no, config[1]);
	else if (ft_strcmp_eq(config[0], "SO") || ft_strcmp_eq(config[0], "S"))
		save_value(&(*game)->header->so, config[1]);
	else if (ft_strcmp_eq(config[0], "WE") || ft_strcmp_eq(config[0], "W"))
		save_value(&(*game)->header->we, config[1]);
	else if (ft_strcmp_eq(config[0], "EA") || ft_strcmp_eq(config[0], "E"))
		save_value(&(*game)->header->ea, config[1]);
	else if (ft_strcmp_eq(config[0], "FL") || ft_strcmp_eq(config[0], "F"))
		save_value(&(*game)->header->f, config[1]);
	else if (ft_strcmp_eq(config[0], "CE") || ft_strcmp_eq(config[0], "C"))
		save_value(&(*game)->header->c, config[1]);
	else
		return (0);
	return (1);
}

void	fill_header_struct(t_game **game)
{
	int		i;
	char	**config;

	i = 0;
	while (i < (*game)->map->init)
	{
		config = ft_split((*game)->file[i], ' ');
		if (matrix_len(config) != 2)
		{
			free_matrix(config);
			print_error_exit(game, "Invalid formatting\n");
		}
		if (!parse_header_data(game, config))
		{
			free_matrix(config);
			print_error_exit(game, "Invalid identifier\n");
		}
		free(config[0]);
		free(config);
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
