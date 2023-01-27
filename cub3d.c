/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/01/27 06:59:51 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_exit(char *input)
{
	printf("%s\n", input);
	exit (1);
}

char *check_input(int argc, char **argv)
{
	int		len_entry;
	char	*is_cub;

	len_entry = ft_strlen(argv[1]);
	
	if(argc != 2)
		print_exit("Error: wrong number of arguments");
	is_cub = ft_substr(argv[1], (len_entry - 4), 5);
	if (ft_strncmp(is_cub, ".cub", 5))
	{
		free(is_cub);
		print_exit("Error: map file needs to be .cub");
	}
	free(is_cub);
	return (argv[1]);
}

int	main(int argc, char *argv[])
{
	char *map;
	
	map  = check_input(argc, argv);
	printf("%s\n", map);
	return (0);
}
