/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:50:34 by alida-si          #+#    #+#             */
/*   Updated: 2023/01/29 19:51:49 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_path(const char *path)
{
	int		fd;
	char	**matrix;

	fd = 0;
	matrix = ft_split(path, '\n');
	fd = open(matrix[0], O_DIRECTORY);
	if (fd != -1)
		exit_error_msg("The path to texture is invalid\n", 1);
	fd = open(matrix[0], O_RDWR);
	if (fd == -1)
	{
		printf("%s\n", matrix[0]);
		exit_error_msg("The path to texture is invalid\n", 1);
	}
	close(fd);
}

void	check_range(char *rgb)
{
	int		i;
	char	**matrix;

	i = 0;
	matrix = ft_split(rgb, ',');
	while (matrix[i])
	{
		if (ft_atoi(matrix[i]) > 255)
			exit_error_msg("Invalid RGB range\n", 1);
		i++;
	}
}

void	check_config(char *info, char *path)
{
	if (info[0] != 'F' && info[0] != 'C')
	{
		check_path(path);
	}
	else
		check_range(path);
}

void	check_identifier(char *info, char *list, char *path)
{
	int		i;
	char	**identifiers;

	i = 0;
	identifiers = ft_split(list, ',');
	while (identifiers[i])
	{
		if (ft_strcmp_eq(info, identifiers[i]) == 1)
		{
			check_config(info, path);
			return ;
		}
		i++;
	}
	exit_error_msg("Invalid identifier\n", 1);
}

void	check_file_line(char *line)
{
	int		i;
	char	**info;

	i = 0;
	if (line[0] == '1' || line[0] == ' ' || line[0] == '\n')
		return ;
	info = ft_split(line,' ');
	check_identifier(info[0], "NO,N,SO,S,WE,W,EA,E,F,FL,C,CE", info[1]);
}
