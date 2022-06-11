/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:22:48 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 12:37:58 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

void	initGrid(t_grid **grid, int line, int column) {
	int		i;
	int		j;
	
	(*grid) = (t_grid *)malloc(sizeof(t_grid) * 1);
	if (!(*grid))
		return ;
	(*grid)->map = (char **)malloc(sizeof(char *) * (column + 1));
	if (!(*grid)->map)
		return ;
	for (i = 0; i < column; i++)
	{
		(*grid)->map[i] = (char *)malloc(sizeof(char) * (line + 1));
		if (!(*grid)->map[i])
			return ;
		for (j = 0; j < line; j++)
			(*grid)->map[i][j] = '.';
		(*grid)->map[i][j] = 0;
	}
	(*grid)->map[i] = 0;
	(*grid)->line = line;
	(*grid)->column = column;
}

void	freeGrid(t_grid *grid) {
	ft_free_ls(grid->map);
	free(grid);
}
