/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/04 16:59:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_file(int fd)
{
	char		*line;
	char		*ret;
	char		**file;

	ret = get_next_line(fd);
	//check_file_line(ret);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		//check_file_line(line);
		ret = ft_strjoin(ret, line);
		free(line);
	}
	close (fd);
	file = ft_split(ret, '\n');
	free(ret);
	return (file);
}

char	**create_map_matrix(char **file)
{
	int		i;
	int		j;
	char	**matrix;

	i = 6;
	j = 0;
	matrix = (char **)malloc(((sizeof(char *)) * 15));
	while(file[i])
	{
		matrix[j] = ft_substr(file[i], 0, ft_strlen(file[i]));
		i++;
		j++;
	}
	*&matrix[j] = NULL;
	return(matrix);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**file;
	char	**matrix_map;
	t_map	*map;
	int		i;

	i = 0;
	fd  = check_input(argc, argv);
	file = read_file(fd);
	matrix_map = create_map_matrix(file);
	/*while(matrix_map[i])
	{
		printf("%s\n", matrix_map[i]);
		i++;
	}*/
	//map = get_map(file);
	/*while(map->map[++i])
		printf("%s\n", map->map[i]);*/
	return (0);
}
