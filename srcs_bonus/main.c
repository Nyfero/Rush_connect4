/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:36 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 20:51:17 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

int main(int ac, char **av) {
	int		line, column, gi;
	t_grid	*grid;
	t_mlx	mlx;

	if (ac != 4)
		return (errorArgNbr());
	line = ft_atoi(av[1]);
	column = ft_atoi(av[2]);
	gi = ft_atoi(av[3]);
	if (line < 6 || column < 7)
		return (errorArgVal());
	grid = NULL;
	initGrid(&grid, line, column);
	if (!grid)
		return (errorMalloc());
	if (gi == 1)
	{
		mlx.mlx = mlx_init();
		if (!mlx.mlx)
			return (errorMlx());
		mlx.win = mlx_new_window(mlx.mlx, column * 64, line * 64, "connect4_bonus");
		// mlx_hook(d.win3d, 33, 1L << 5, end_cub3d, &d);
		mlx_loop(mlx.mlx);
	}
	else
		startGame(grid);
	freeGrid(grid);
	return (0);
}
