/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:39:59 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 14:07:34 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

void	startGameBonus(t_mlx *data) {
	displayStart();
	displayGrid(*data->grid);
	ft_putchar('\n');
	displayHelp();
	
	displayInterface(data);
	
	int	turn;
	// turn = pickPlayer();
	turn = 1;
	displayTurn(turn);
	//mlx action player
	// displayInterface(data);
	mlx_hook(data->win, 02, (1L << 0), keyboard, data);
	mlx_loop(data->mlx);
}

int	keyboard(int keycode, t_mlx *data) {
	if (keycode == 65307)
	{
		freeMlx(data);
		exit(0);
	}
	else if (keycode == 65361)
		moveLeft(data);
	else if (keycode == 65363)
		moveRight(data);
	else if (keycode == 65293)
	{
		if (data->grid->map[data->cursor][0] != '.')
		{
			ft_putstr("\e[91mThe column is full !\e[39m\n");
			return (0);
		}
		playerAction(data->grid, data->cursor + 1);
		displayGrid(*data->grid);
		if (endOfGame(*data->grid, data->cursor))
		{	
			displayEndOfGame(*data->grid, data->cursor + 1, 0);
			freeMlx(data);
			exit(0);
		}
	}
	displayInterface(data);
	return (0);
}

void	moveLeft(t_mlx *data) {
	if (data->cursor > 0)
		data->cursor -= 1;
}

void	moveRight(t_mlx *data) {
	if (data->cursor < data->grid->column - 1)
		data->cursor += 1;
}
