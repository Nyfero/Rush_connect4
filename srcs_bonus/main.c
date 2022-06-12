/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:36 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 16:48:31 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

int main(int ac, char **av) {
	int		line, column, gi;
	t_grid	*grid;
	t_mlx	*data;

	if (ac != 4)
		return (errorArgNbr());
	if (!isInt(av[1]) || !isInt(av[2]) || !isInt(av[3]))
		return(errorArgVal());
	line = ft_atoi(av[1]);
	column = ft_atoi(av[2]);
	gi = ft_atoi(av[3]);
	if (line < 6 || column < 7)
		return (errorArgVal());
	grid = NULL;
	initGrid(&grid, line, column);
	if (!grid)
		return (errorMalloc());
	data = NULL;
	if (gi == 1)//Si l'interface graphique est utilisé
	{
		if (initMlx(&data, column, line, grid))
		{
			freeMlx(data);
			return (errorMlx());
		}
		startGameBonus(data);		
		freeMlx(data);
	}
	else//Si l'interface graphique n'est pas activé
	{
		startGame(grid);
		freeGrid(grid);
	}
	return (0);
}
