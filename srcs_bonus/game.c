/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:56:47 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 12:05:04 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

/*
**	1: tour du joueur
**	0: tour de l'IA
*/

int	pickPlayer(void) {
	srand(time(NULL));
	int	turn = rand() % 2;
	if (turn)
		ft_putstr("\e[93mThe player start\e[39m\n");
	else
		ft_putstr("\e[91mThe IA start\e[39m\n");
	return (turn);
}

void	startGame(t_grid *grid) {
	displayStart();
	displayGrid(*grid);
	ft_putchar('\n');
	
	int	turn;
	int	action;
	// turn = pickPlayer();
	turn = 1;
	while (1)
	{
		displayTurn(turn);
		if (turn)
		{
			// evalWholeGrid(grid, 1);
			action = askPlayer(*grid);
			playerAction(grid, action);
			displayGrid(*grid);
			turn = 0;
		}
		else
		{
			//IA do something
			// evalWholeGrid(grid, 0);
			action = askPlayer(*grid);
			botAction(grid, action);
			displayGrid(*grid);
			turn = 1;
		}
		if (endOfGame(*grid, action))
			break;
	}
	displayEndOfGame(*grid, action, turn);
}

int	mapFull(t_grid const grid) {
	for(int i = 0; i < grid.column; i++)
		if (grid.map[i][0] == '.')
			return (0);
	return (1);
}

int	endOfGame(t_grid const grid, int const action) {
	if (mapFull(grid))
		return (1);
	if (someoneWin(grid, action))
		return (1);
	return (0);
}

int	someoneWin(t_grid const grid, int const action) {
	int		i = 0;
	char	pion;
	
	while (grid.map[action - 1][i] == '.')
		i++;
	pion = grid.map[action - 1][i];
	if (checkIfWin(pion, grid, action - 1, i))
		return (1);
	return (0);
}
