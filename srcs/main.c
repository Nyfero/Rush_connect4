/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:36 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 17:48:57 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

int main(int ac, char **av) {
	int		line;
	int		column;
	t_grid	*grid;

	if (ac != 3)
		return (errorArgNbr());
	line = ft_atoi(av[1]);
	column = ft_atoi(av[2]);
	if (line < 6 || column < 7)
		return (errorArgVal());
	grid = NULL;
	initGrid(&grid, line, column);
	if (!grid)
		return (errorMalloc());
	startGame(grid);
	freeGrid(grid);
	return (0);
}
