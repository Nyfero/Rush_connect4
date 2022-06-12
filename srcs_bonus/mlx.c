/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:39:59 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 19:04:13 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

//Lance le jeu si l'option interface graphique est activé
void	startGameBonus(t_mlx *data) {
	displayStart();
	displayGrid(*data->grid);
	ft_putchar('\n');
	displayHelp();
	
	displayInterface(data);
	
	data->turn = pickPlayer();
	displayTurn(data->turn);
	if (!data->turn)
		IATurn(data);
	//mlx action player
	mlx_hook(data->win, 02, (1L << 0), keyboard, data);
	mlx_loop(data->mlx);
}

//Récupère les inputs du joueur pour l'interface graphique
int	keyboard(int keycode, t_mlx *data) {
	if (keycode == 65307)
		closeGame(data);
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
		playerTurn(data);
		IATurn(data);
	}
	displayInterface(data);
	return (0);
}

//Effectue l'action du joueur
void	playerTurn(t_mlx *data) {
	playerAction(data->grid, data->cursor + 1);
	displayGrid(*data->grid);
	displayInterface(data);
	if (endOfGame(*data->grid, data->cursor + 1))
	{
		displayEndOfGame(*data->grid, data->cursor + 1, 0);
		closeGame(data);
	}
	displayTurn(0);
}

//Effectue l'action de l'IA
void	IATurn(t_mlx *data) {
	int action = getBestAction(data->grid, 0);

	botAction(data->grid, action);
	displayGrid(*data->grid);
	displayInterface(data);
	if (endOfGame(*data->grid, action))
	{
		displayEndOfGame(*data->grid, action, 1);
		closeGame(data);
	}
	displayTurn(1);
}

void	moveLeft(t_mlx *data) {
	if (data->cursor > 0)
		data->cursor -= 1;
}

void	moveRight(t_mlx *data) {
	if (data->cursor < data->grid->column - 1)
		data->cursor += 1;
}

int	closeGame(t_mlx *data) {
	freeMlx(data);
	exit(0);
	return (0);
}
