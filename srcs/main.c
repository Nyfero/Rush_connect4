/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:36 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 20:47:07 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

int checkArg(char **av) {
	char *end;
	long tmp;

	for(int i = 1; i < 3; i++)
	{
		tmp = ft_strtoll(av[i], &end);
		if (end == av[i] || *end || tmp > INT_MAX)
			return (errorArgVal());
	}
	return (0);
}

int main(int ac, char **av) {
	int		line;
	int		column;
	t_grid	*grid;

	if (ac != 3)
		return (errorArgNbr());
	if (!isInt(av[1]) || !isInt(av[2]))
		return(errorArgVal());
	if (checkArg(av))
		return (1);
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
