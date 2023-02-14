/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:50:34 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/14 08:16:29 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_config(char *info, char *path)
{
	int	check_flag;

	check_flag = 0;
	if (info[0] != 'F' && info[0] != 'C')
		check_flag = check_path(path);
	else
		check_flag = check_rgb(path);
	return (check_flag);
}

int	check_identifier(char *info, char *list, char *path)
{
	int		i;
	char	**identifiers;

	i = 0;
	identifiers = ft_split2(list, ',');
	while (identifiers[i])
	{
		if (ft_strcmp_eq(info, identifiers[i]) == 1)
		{
			if (!check_config(info, path))
			{
				free_matrix(identifiers);
				return (0);
			}
			free_matrix(identifiers);
			return (1);
		}
		i++;
	}
	print_error_msg("Invalid identifier\n");
	free_matrix(identifiers);
	return (0);
}

int	check_file_line(char *line)
{
	char	**info;

	if (line[0] == '1' || line[0] == ' ' || line[0] == '\n' || line[0] == '0')
		return (0);
	info = ft_split2(line, ' ');
	if (!check_identifier(info[0], "NO,N,SO,S,WE,W,EA,E,F,FL,C,CE", info[1]))
	{
		free_matrix(info);
		return (0);
	}
	free_matrix(info);
	return (1);
}

void	check_header(t_game **game)
{
	int	i;

	i = 0;
	while (i < (*game)->map->init_map)
	{
		if (!check_file_line((*game)->file[i]))
		{
			free_cub3d(game);
			exit (1);
		}
		i++;
	}
}
