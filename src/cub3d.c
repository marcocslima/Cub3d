/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/11 16:12:29 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_file(char **file)
{
	free_matrix(file);
	file = NULL;
}

void	verify_empty_lines(char *file, t_game **game)
{
	int	i;
	int	k;
	int	flag;

	i = -1;
	k = 0;
	flag = 0;
	while(file[++i])
	{
		if(file[i] == '\n'
			&& (file[i + 1] == ' ' || file[i + 1] == '0'
			|| file[i + 1] == '1'))
				flag++;
		if(flag > 0 && file[i + 1] == '\n')
			k++;
	}
	if (k - flag > 0)
	{
		free(file);
		print_error_exit(game, "find error on map...\n");
	}
}

void	**read_file(int fd, t_game **game)
{
	char		*line;
	char		*ret;
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
	verify_empty_lines(ret, game);
	if (check_flag == 0)
		(*game)->file = ft_split(ret, '\n');
	free(ret);
}

void	verify_head_and_foot(t_game **game)
{
	t_map	*map;

	map = (*game)->map;
	if (ft_strchr(map->map[0], '0') != NULL)
		print_error_exit(game, "find error on map...\n");
	if (ft_strchr(map->map[map->map_higth - 1], '0') != NULL)
		print_error_exit(game, "find error on map...\n");
}

int	verify_position(t_map *map, int j, int i)
{
	if (map->map[j - 1][i] && map->map[j - 1][i] == ' ')
		return (0);
	if (map->map[j - 1][i - 1] && map->map[j - 1][i - 1] == ' ')
		return (0);
	if (map->map[j - 1][i + 1] && map->map[j - 1][i + 1] == ' ')
		return (0);
	if (map->map[j + 1][i] && map->map[j + 1][i] == ' ')
		return (0);
	if (map->map[j + 1][i - 1] && map->map[j + 1][i - 1] == ' ')
		return (0);
	if (map->map[j + 1][i + 1] && map->map[j + 1][i + 1] == ' ')
		return (0);
	if (map->map[j][i - 1] && map->map[j][i - 1] == ' ')
		return (0);
	if (map->map[j][i + 1] && map->map[j][i + 1] == ' ')
		return (0);
	return (1);
}

void	verify_holes(t_game **game)
{
	int		i;
	int		j;
	t_map	*map;

	j = 1;
	map = (*game)->map;
	while (j < map->map_higth - 1)
	{
		i = 0;
		while (i < map->map_width)
		{
			if (map->map[j][i] == '0')
			{
				if (!verify_position(map, j, i))
					print_error_exit(game, "find error on map...\n");
			}
			i++;
		}
		j++;
	}
}

void	verify_sides(t_game **game)
{
	t_map	*map;
	int		i;

	map = (*game)->map;
	i = -1;
	while (++i < map->map_higth)
	{
		if (map->map[i][0] == '0' || map->map[i][map->map_width - 1] == '0')
			print_error_exit(game, "find error on map...\n");
	}
}

void	verify_map(t_game **game)
{
	verify_head_and_foot(game);
	verify_sides(game);
	verify_holes(game);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	*game;

	fd = check_input(argc, argv);
	init_data(&game);
	read_file(fd, &game);
	if (game->file != NULL)
	{
		get_map(game->file, &game->map);
		get_header(&game);
		verify_map(&game);
		print_whole_map(game);
	}
	free_cub3d(&game);
	return (0);
}
