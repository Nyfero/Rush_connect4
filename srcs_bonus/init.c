/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:22:48 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 16:50:54 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

//Initialise la grille de jeu
void	initGrid(t_grid **grid, int line, int column) {
	int		i, j;
	
	(*grid) = (t_grid *)malloc(sizeof(t_grid) * 1);
	if (!(*grid))
		return ;
	ft_memset(*grid, 0, sizeof(t_grid));
	(*grid)->map = (char **)malloc(sizeof(char *) * (column + 1));
	if (!(*grid)->map) {
		freeGrid(*grid);
		*grid = NULL;
		return ;
	}
	for (i = 0; i < column; i++)
	{
		(*grid)->map[i] = (char *)malloc(sizeof(char) * (line + 1));
		if (!(*grid)->map[i]) {
			freeGrid(*grid);
			*grid = NULL;
			return ;
		}
		for (j = 0; j < line; j++)
			(*grid)->map[i][j] = '.';
		(*grid)->map[i][j] = 0;
	}
	(*grid)->map[i] = 0;
	(*grid)->line = line;
	(*grid)->column = column;
	(*grid)->scoreGrid = (int *)malloc(sizeof(int ) * column );
	if (!(*grid)->scoreGrid){
		freeGrid(*grid);
		*grid = NULL;
		return ;
	}
	ft_memset( (*grid)->scoreGrid, 0, column );
}

//Initialise la mlx et la structure qui la contient
int	initMlx(t_mlx **data, int const column, int const line, t_grid *grid) {
	(*data) = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	if (!(*data))
		return (1);
	(*data)->mlx = mlx_init();
	if (!(*data)->mlx)
		return (1);
	if (initImg((*data)))
		return (1);
	(*data)->win = mlx_new_window((*data)->mlx, column * 64, (line + 1) * 64, "connect4_bonus");
	if (!(*data)->win)
		return (1);
	(*data)->grid = grid;
	(*data)->cursor = column / 2;
	return (0);
}

//Initialise toutes mes images
int	initImg(t_mlx *data) {
	data->board.img = mlx_xpm_file_to_image(data->mlx, "srcs_bonus/img/empty_board.xpm",
		&data->board.width, &data->board.height);
	data->red.img = mlx_xpm_file_to_image(data->mlx, "srcs_bonus/img/IA_pion.xpm",
		&data->red.width, &data->red.height);
	data->yellow.img = mlx_xpm_file_to_image(data->mlx, "srcs_bonus/img/Player_pion.xpm",
		&data->yellow.width, &data->yellow.height);
	if (!data->board.img || !data->red.img || !data->yellow.img)
		return (1);
	return (0);
}

//Libère la mémoire de ma grille
void	freeGrid(t_grid *grid) {
	if (grid->map)
		ft_free_ls(grid->map);
	if (grid->scoreGrid)
		free(grid->scoreGrid);
	if (grid)
		free(grid);
}

//Libère la mémoire de ma structure contenant la mlx
void	freeMlx(t_mlx *data) {
	if (data->board.img)
		mlx_destroy_image(data->mlx, data->board.img);
	if (data->red.img)
		mlx_destroy_image(data->mlx, data->red.img);
	if (data->yellow.img)
		mlx_destroy_image(data->mlx, data->yellow.img);
	if (data->win)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
	freeGrid(data->grid);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
}
