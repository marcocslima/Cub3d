/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:18:58 by alida-si          #+#    #+#             */
/*   Updated: 2023/02/12 16:22:29 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	check_str_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
