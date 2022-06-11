/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:51 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 15:11:07 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <time.h>

typedef struct s_grid
{
	char	**map;
	int		line;
	int		column;
}	t_grid;

//	game.c
int		pickPlayer(void);
void	startGame(t_grid *grid);
int		mapFull(t_grid const grid);
int		endOfGame(t_grid const grid);

//	player.c
void	playerAction(t_grid *grid, int const action);
int		askPlayer(t_grid const grid);
int		isInt(char const *input);
int		isInGrid(char const *input, t_grid const grid);

//	init.c
void	initGrid(t_grid **grid, int line, int column);
void	freeGrid(t_grid *grid);

//	display.c
void	displayStart(void);
void	displayGrid(t_grid const grid);
void	displayTurn(int	const turn);
void	displayEndOfGame(t_grid const grid);

//	error.c
int		errorArgNbr(void);
int		errorArgVal(void);
int		errorMalloc(void);

#endif
