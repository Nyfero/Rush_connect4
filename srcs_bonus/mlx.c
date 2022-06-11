int	ft_game_event(int key, t_data *d)
{
	if (key == 65307)
		end_cub3d(d);
	if (key == 65361)
		ft_rotation(1, d->pl);
	if (key == 65363)
		ft_rotation(-1, d->pl);
	if (key == 119)
		ft_deplacement_vert(d, -1, d->pl);
	if (key == 97)
		ft_deplacement_hor(d, -1, d->pl);
	if (key == 115)
		ft_deplacement_vert(d, 1, d->pl);
	if (key == 100)
		ft_deplacement_hor(d, 1, d->pl);
	if (key == 65307 || key == 65361 || key == 65363 || key == 119 || key == 97
		|| key == 115 || key == 100)
		ft_3d_render(d);
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
