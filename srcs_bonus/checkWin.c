/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkWin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:31:09 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 17:46:01 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

//Vérifie si 4 pions sont alignés peut importe le sens
int	checkIfWin(char const pion, t_grid const grid, int const x, int const y) {
	if (checkWinLigne(pion, grid, x, y) || checkWinColumn(pion, grid, x, y)
		|| checkWinD1(pion, grid, x, y) || checkWinD2(pion, grid, x, y))
		return (1);
	return (0);
}

//Vérifie si on a une victoire sur une ligne (peut importe le sens)
int	checkWinLigne(char const pion, t_grid const grid, int const x, int const y) {
	int	i = x;
	int	compt = 0;
	
	while (i > 0 && grid.map[i - 1][y] == pion)
		i--;
	while (i < grid.column && grid.map[i][y] == pion)
	{
		i++;
		compt++;
	}
	if (compt >= 4)
		return (1);
	return (0);
}

//Vérifie si on a une victoire sur une colonne (peut importe le sens)
int	checkWinColumn(char const pion, t_grid const grid, int const x, int const y) {
	int	j = y;
	int	compt = 0;

	while (j > 0 && grid.map[x][j - 1] == pion)
		j--;
	while (j < grid.line && grid.map[x][j] == pion)
	{
		j++;
		compt++;
	}
	if (compt >= 4)
		return (1);
	return (0);
}

//Vérifie si on a une victoire sur une diagonale montante (/>)
int	checkWinD1(char const pion, t_grid const grid, int const x, int const y) {
	int	i = x;
	int	j = y;
	int	compt = 0;
	
	while (i > 0 && j < grid.line && grid.map[i - 1][j + 1] == pion)
	{
		i--;
		j++;
	}
	while (i < grid.column && j > 0 && grid.map[i][j] == pion)
	{
		i++;
		j--;
		compt++;
	}
	if (compt >= 4)
		return (1);
	return (0);
}

//Vérifie si on a une victoire sur une diagonale descendante (\>)
int	checkWinD2(char const pion, t_grid const grid, int const x, int const y) {
	int	i = x;
	int	j = y;
	int	compt = 0;
	
	while (i > 0 && j > 0 && grid.map[i - 1][j - 1] == pion)
	{
		i--;
		j--;
	}
	while (i < grid.column && j < grid.line && grid.map[i][j] == pion)
	{
		i++;
		j++;
		compt++;
	}
	if (compt >= 4)
		return (1);
	return (0);
}
