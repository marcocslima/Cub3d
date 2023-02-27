/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:16:02 by mcesar-d          #+#    #+#             */
/*   Updated: 2023/02/27 03:27:17 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_file(int fd, t_game **game)
{
	char		*line;
	char		*ret;

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
	verify_empty_lines(ret, game);
	(*game)->file = ft_split(ret, '\n');
	free(ret);
}


void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			//my_mlx_pixel_put(img, j++, i, color);
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	render(t_game **game)
{
	if ((*game)->mlx_window == NULL)
		return (1);
	render_background((*game)->img_ptr, create_rgb(255, 0, 0));

	mlx_put_image_to_window((*game)->mlx, (*game)->mlx_window, (*game)->img_ptr->img, 0, 0);

	return (0);
}



void	run_game(t_game **game)
{
	(*game)->mlx = mlx_init();
	(*game)->mlx_window = mlx_new_window((*game)->mlx,WIDTH,HEIGHT,"Cub3D");
	(*game)->img_ptr = mlx_new_image((*game)->mlx,WIDTH,HEIGHT);
	(*game)->img_ptr->addr = mlx_get_data_addr((*game)->img_ptr, &(*game)->img_ptr->bpp, &(*game)->img_ptr->line_length, &(*game)->img_ptr->endian);

	mlx_loop_hook((*game)->mlx, &render, &(*game));
	mlx_loop((*game)->mlx);
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
		check_header(&game);
		verify_map(&game);
		//printf("%s\n",game->header->no[1]);
		//print_whole_map(game);
		run_game(&game);
	}
	free_cub3d(&game);
	return (0);
}
