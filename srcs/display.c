/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:24 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 21:40:42 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

//Affiche le début du jeu
void	displayStart(void) {
	ft_putstr("..######...#######..##....##.##....##.########..######..########.##.......\n");
	ft_putstr(".##....##.##.....##.###...##.###...##.##.......##....##....##....##....##.\n");
	ft_putstr(".##.......##.....##.####..##.####..##.##.......##..........##....##....##.\n");
	ft_putstr(".##.......##.....##.##.##.##.##.##.##.######...##..........##....##....##.\n");
	ft_putstr(".##.......##.....##.##..####.##..####.##.......##..........##....#########\n");
	ft_putstr(".##....##.##.....##.##...###.##...###.##.......##....##....##..........##.\n");
	ft_putstr("..######...#######..##....##.##....##.########..######.....##..........##.\n");
	ft_putstr("\n\n\n");
}

//Calcul la taille des espaces entres les points pour que l'aide colle avec l'affichage
int	lenInt(int column) {
	int compt = 1;
	
	while (column / 10 > 0)
	{
		column = column / 10;
		compt++;
	}
	return (compt);
}

//Affiche la grille dans le terminal
void	displayGrid(t_grid const grid) {
	int size = lenInt(grid.column);

	for(int j = 0; j < grid.line; j++)
	{
		for(int i = 0; i < grid.column; i++)
		{
			if (grid.map[i][j] == 'X')
				ft_putstr("\e[93m");
			else if (grid.map[i][j] == 'O')
				ft_putstr("\e[91m");
			ft_putchar(grid.map[i][j]);
			ft_putstr("\e[39m");
			for(int k = 0; k < size; k++)
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	displayColHelp(grid);
}

//Affiche les colonnes sur le terminal
void	displayColHelp(t_grid const grid) {
	int	size = lenInt(grid.column);

	for (int i = 0; i < grid.column - 1; i++)
	{
		if (size == 1)
			ft_putstr("--");
		else if (size == 2)
			ft_putstr("---");
	}
	ft_putstr("-\n");
	for (int i = 0; i < grid.column; i++)
	{
		ft_putnbr(i + 1);
		int	j = lenInt(i + 1);
		while (j++ < size)
			ft_putchar(' ');
		ft_putchar(' ');
	}
	ft_putstr("\n");
	for (int i = 0; i < grid.column - 1; i++)
	{
		if (size == 1)
			ft_putstr("--");
		else if (size == 2)
			ft_putstr("---");
	}
	ft_putstr("-\n");
}

//Affiche le tour actuelle
void	displayTurn(int	const turn) {
	if (turn)
		ft_putstr("\e[95mIt's your turn !\e[39m\n");
	else
		ft_putstr("\e[95mIt's IA turn !\e[39m\n");
}

//Affiche le résultat de la partie
void	displayEndOfGame(t_grid const grid, int const action, int const turn) {
	if (someoneWin(grid, action))
	{
		if (!turn)
			ft_putstr("\e[92mThe player won!\e[39m\n");
		else
			ft_putstr("\e[91mThe IA won !\e[39m\n");
		return ;
	}
	if (mapFull(grid))
	{
		ft_putstr("\e[93mThe map is full !\nIt's a draw !\e[39m\n");
		return ;
	}
}
