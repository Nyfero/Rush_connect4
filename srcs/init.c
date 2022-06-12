/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:22:48 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 19:45:12 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

//Initialise la grille de jeu
void	initGrid(t_grid **grid, int line, int column) {
	int		i, j;
	
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
}

//Libère la mémoire de ma grille
void	freeGrid(t_grid *grid) {
	if (grid->map)
		ft_free_ls(grid->map);
	if (grid)
		free(grid);
}
