/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:50:34 by alida-si          #+#    #+#             */
/*   Updated: 2023/01/29 15:54:46 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_identifier(char *info, char *list)
{
	int		i;
	char	**identifiers;

	i = 0;
	identifiers = ft_split(list, ',');
	while (identifiers[i])
	{
		if (ft_strcmp_eq(info, identifiers[i]) == 1)
		{
			//checa se o caminho do arquivo é válido
			//preenche a struct do cabeçalho
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
	check_identifier(info[0], "NO,N,SO,S,WE,W,EA,E,F,FL,C,CE");
}
