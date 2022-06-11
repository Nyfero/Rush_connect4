/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:56:47 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 14:48:32 by gsap             ###   ########.fr       */
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
	turn = pickPlayer();
	while (1)
	{
		displayTurn(turn);
		if (turn)
		{
			action = askPlayer(*grid);
			playerAction(grid, action);
			displayGrid(*grid);
			turn = 0;
		}
		else
		{
			//IA do something
			displayGrid(*grid);
			turn = 1;
		}
	
	}
}
