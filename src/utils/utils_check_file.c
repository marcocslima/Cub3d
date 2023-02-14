/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:18:58 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/14 08:15:00 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_range_is_valid(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (check_str_is_number(rgb[i]))
		{
			if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

int	check_range(char *rgb)
{
	char	**matrix;
	int		valid_flag;

	valid_flag = 0;
	matrix = ft_split(rgb, ',');
	if (matrix_len(matrix) == 3)
		valid_flag = check_range_is_valid(matrix);
	free_matrix(matrix);
	return (valid_flag);
}

int	check_path(const char *path)
{
	int		fd;
	char	**matrix;
	int		valid_flag;

	fd = 0;
	valid_flag = 1;
	matrix = ft_split2(path, '\n');
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

int	check_rgb(char *info)
{
	char	**rgb;

	rgb = ft_split2(info, '\n');
	if (rgb[0] != NULL)
	{
		if (check_range(rgb[0]))
		{
			free_matrix(rgb);
			return (1);
		}
	}
	print_error_msg("Invalid RGB range\n");
	free_matrix(rgb);
	return (0);
}
