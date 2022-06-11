/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:24 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 14:36:50 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

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

void	displayGrid(t_grid const grid) {
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
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	/*
	**	A revoir
	*/
	for (int i = 0; i < grid.column - 1; i++)
		ft_putstr("--");
	ft_putstr("-\n");
	for (int i = 0; i < grid.column; i++)
	{
		ft_putnbr(i + 1);
		ft_putchar(' ');
	}
	ft_putstr("\n");
	for (int i = 0; i < grid.column - 1; i++)
		ft_putstr("--");
	ft_putstr("-\n");
	/*
	** A revoir
	*/
}

void	displayTurn(int	turn) {
	if (turn)
		ft_putstr("\e[95mIt's your turn !\e[39m\n");
	else
		ft_putstr("\e[95mIt's IA turn !\e[39m\n");
}
