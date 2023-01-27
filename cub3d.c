/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/01/27 23:27:59 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_exit(char *input)
{
	printf("%s\n", input);
	exit (1);
}

char	**read_map(int fd)
{
	char		*line;
	char		*ret;
	char		**map;

	ret = get_next_line(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = ft_strjoin(ret, line);
		free(line);
	}
	close (fd);
	map = ft_split(ret, '\n');
	free(ret);
	return (map);
}

int	check_input(int argc, char **argv)
{
	int		len_entry;
	int		fd;
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
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		print_exit("Error: file can´t be a directory");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_exit("Error: map can´t be found");
	return (fd);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**map;
	int		i;
	
	i = -1;
	fd  = check_input(argc, argv);
	map = read_map(fd);
	while(map[++i])
	{
		printf("%s\n", map[i]);
		free(map[i]);
	}
	free(map);
	return (0);
}
