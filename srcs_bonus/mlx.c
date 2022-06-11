/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:39:59 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 21:47:03 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

int	initImg(t_mlx mlx) {
	mlx.board.img = mlx_xpm_file_to_image(mlx.mlx, "img/empty_board.xpm",
		&mlx.board.width, &mlx.board.height);
	mlx.red.img = mlx_xpm_file_to_image(mlx.mlx, "img/IA_pion.xpm",
		&mlx.red.width, &mlx.red.height);
	mlx.yellow.img = mlx_xpm_file_to_image(mlx.mlx, "img/Player_pion.xpm",
		&mlx.yellow.width, &mlx.yellow.height);
	if (!mlx.board.img || !mlx.red.img || !mlx.yellow.img)
		return (0);
	return (1);
}

int	ft_game_event(int key, t_data *d)
{
	if (key == 65307)
		end_cub3d(d); //quitte mon programme
	if (key == 97)
		ft_deplacement_hor(d, -1, d->pl);//gauche
	if (key == 100)
		ft_deplacement_hor(d, 1, d->pl);//droite
	if (key == space)
		
	ft_3d_render(d); //affiche mon image
	return (0);
}

map->fl.img = mlx_xpm_file_to_image(map->mlx, "./img/Grass.xpm", \
&map->fl.width, &map->fl.height);

data->screen.img = mlx_new_image(data->mlx, 720, 720);

mlx_put_image_to_window(d->mlx, d->win3d, d->screen.img, -1, -1);

int	end_cub3d(t_data *data)
{
	free_img(data);
	if (data->wall)
		free(data->wall);
	mlx_clear_window(data->mlx, data->win3d);
	mlx_destroy_window(data->mlx, data->win3d);
	ft_free_ls(data->map);
	free(data->pl);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
