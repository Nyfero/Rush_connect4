/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:56:47 by gsap              #+#    #+#             */
/*   Updated: 2022/06/20 15:00:27 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

/*
**	1: tour du joueur
**	0: tour de l'IA
*/

//Choisie aléatoirement le premier joueur
int	pickPlayer(void) {
	srand(time(NULL));
	int	turn = rand() % 2;
	if (turn)
		ft_putstr("\e[93mThe player start\e[39m\n");
	else
		ft_putstr("\e[91mThe IA start\e[39m\n");
	return (turn);
}

//Lance la partie
void	startGame(t_grid *grid) {
	displayStart();
	displayGrid(*grid);
	ft_putchar('\n');
	
	int	turn;
	int	action;

	turn = pickPlayer();
	while (1)
	{
		displayTurn(turn);
		if (turn)
		{
			action = askPlayer(*grid);
			if (action == -1)
				return ;
			playerAction(grid, action);
			displayGrid(*grid);
			turn = 0;
		}
		else
		{
			//IA do something
			action = getBestAction(grid, 0);
			botAction(grid, action);
			displayGrid(*grid);
			turn = 1;
		}
		if (endOfGame(*grid, action))
			break;
	}
	displayEndOfGame(*grid, action, turn);
}

//Vérifie si la partie doit se termier
int	endOfGame(t_grid const grid, int const action) {
	if (someoneWin(grid, action))
		return (1);
	if (mapFull(grid))
		return (1);
	return (0);
}

//Vérifie si la grille est remplie
int	mapFull(t_grid const grid) {
	for(int i = 0; i < grid.column; i++)
		if (grid.map[i][0] == '.')
			return (0);
	return (1);
}

//Vérifie si le joueur ou l'IA a gagner
int	someoneWin(t_grid const grid, int const action) {
	int		i = 0;
	char	pion;
	
	while (i < grid.line && grid.map[action - 1][i] == '.')
		i++;
	pion = grid.map[action - 1][i];
	if (checkIfWin(pion, grid, action - 1, i))
		return (1);
	return (0);
}
