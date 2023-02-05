/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/05 14:48:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_file(int fd)
{
	char		*line;
	char		*ret;
	char		**file;
	int			check_flag;

	check_flag = 0;
	ret = get_next_line(fd);
	check_flag += check_file_line(ret);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		check_flag += check_file_line(line);
		ret = ft_strjoin(ret, line);
		free(line);
	}
	close (fd);
	file = ft_split(ret, '\n');
	free(ret);
	if (check_flag > 0)
	{
		free_matrix(file);
		file = NULL;
	}
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
	while (file[i])
	{
		matrix[j] = ft_substr(file[i], 0, ft_strlen(file[i]));
		i++;
		j++;
	}
	*&matrix[j] = NULL;
	return (matrix);
}

void	normalize_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == ' ')
				map[i][j] = 'S';
			j++;
		}
		i++;
	}
}

void	init_data(t_map **map)
{
	*map = (t_map *) malloc(sizeof(t_map));
	(*map)->map_higth = 0;
	(*map)->map_width = 0;
	(*map)->map = NULL;
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	**file;
	char	**matrix_map;
	t_map	*map;
	int		i;

	i = 0;
	fd = check_input(argc, argv);
	file = read_file(fd);
	if (file != NULL)
	{
		matrix_map = create_map_matrix(file);
		normalize_map(matrix_map);
		init_data(&map);
		map->map = matrix_map;
		//map = get_map(file);
		while(map->map[++i])
			printf("%s\n", map->map[i]);
		free_matrix(matrix_map);
		free_matrix(file);
		free(map);
	}
	return (0);
}
