/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:50:34 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/12 10:11:52 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_path(const char *path)
{
	int		fd;
	char	**matrix;
	int		valid_flag;

	fd = 0;
	valid_flag = 1;
	matrix = ft_split(path, '\n');
	if (matrix[0] != NULL)
	{
		fd = open(matrix[0], O_DIRECTORY);
		if (fd != -1)
			valid_flag = 0;
		fd = open(matrix[0], O_RDWR);
		if (fd == -1)
			valid_flag = 0;
	}
	else
		valid_flag = 0;
	free_matrix(matrix);
	if (fd != -1 && fd != 0)
		close(fd);
	if (!valid_flag)
		print_error_msg("Invalid path to texture\n");
	return (valid_flag);
}

int	check_range(char *rgb)
{
	int		i;
	char	**matrix;

	i = 0;
	matrix = ft_split(rgb, ',');
	while (matrix[i])
	{
		if (ft_atoi(matrix[i]) < 0 || ft_atoi(matrix[i]) > 255)
		{
			print_error_msg("Invalid RGB range\n");
			free_matrix(matrix);
			return (0);
		}
		i++;
	}
	free_matrix(matrix);
	return (1);
}

int	check_config(char *info, char *path)
{
	int	check_flag;

	check_flag = 0;
	if (info[0] != 'F' && info[0] != 'C')
		check_flag = check_path(path);
	else
		check_flag = check_range(path);
	return (check_flag);
}

int	check_identifier(char *info, char *list, char *path)
{
	int		i;
	char	**identifiers;

	i = 0;
	identifiers = ft_split(list, ',');
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
	int		i;
	char	**info;

	i = 0;
	if (line[0] == '1' || line[0] == ' ' || line[0] == '\n' || line[0] == '0')
		return (0);
	info = ft_split(line, ' ');
	if (!check_identifier(info[0], "NO,N,SO,S,WE,W,EA,E,F,FL,C,CE", info[1]))
	{
		free_matrix(info);
		return (1);
	}
	free_matrix(info);
	return (0);
}
