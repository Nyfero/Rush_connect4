/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:22:48 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 23:35:37 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

void	initGrid(t_grid **grid, int line, int column) {
	int		i;
	int		j;
	
	(*grid) = (t_grid *)malloc(sizeof(t_grid) * 1);
	if (!(*grid))
		return ;
	ft_memset(*grid, 0, sizeof(t_grid));
	(*grid)->map = (char **)malloc(sizeof(char *) * (column + 1));
	if (!(*grid)->map) {
		freeGrid(*grid);
		*grid = NULL;
		return ;
	}
	for (i = 0; i < column; i++)
	{
		(*grid)->map[i] = (char *)malloc(sizeof(char) * (line + 1));
		if (!(*grid)->map[i]) {
			freeGrid(*grid);
			*grid = NULL;
			return ;
		}
		for (j = 0; j < line; j++)
			(*grid)->map[i][j] = '.';
		(*grid)->map[i][j] = 0;
	}
	(*grid)->map[i] = 0;
	(*grid)->line = line;
	(*grid)->column = column;
	(*grid)->scoreGrid = (int *)malloc(sizeof(int ) * column );
	if (!(*grid)->scoreGrid){
		freeGrid(*grid);
		*grid = NULL;
		return ;
	}
	ft_memset( (*grid)->scoreGrid, 0, column );
}

void	freeGrid(t_grid *grid) {
	ft_free_ls(grid->map);
	free(grid->scoreGrid);
	free(grid);
}
