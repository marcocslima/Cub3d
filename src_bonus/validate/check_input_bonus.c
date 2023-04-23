/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:17:20 by alida-si          #+#    #+#             */
/*   Updated: 2023/04/23 16:37:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	print_exit(char *input)
{
	print_error_msg(input);
	exit (1);
}

int	check_input(int argc, char **argv)
{
	int		len_entry;
	int		fd;
	char	*is_cub;

	len_entry = ft_strlen(argv[1]);
	if (argc != 2)
		print_exit("Wrong number of arguments\n");
	is_cub = ft_substr(argv[1], (len_entry - 4), 5);
	if (ft_strncmp(is_cub, ".cub", 5))
	{
		free(is_cub);
		print_exit("Map file needs to be .cub\n");
	}
	free(is_cub);
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		print_exit("File can´t be a directory\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_exit("Map can´t be found\n");
	return (fd);
}
