/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:51 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 20:59:41 by gsap             ###   ########.fr       */
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
int		endOfGame(t_grid const grid, int const action);
int		someoneWin(t_grid const grid, int const action);

//	checkWin.c
int		checkIfWin(char const pion, t_grid const grid, int const x, int const y);
int		checkWinLigne(char const pion, t_grid const grid, int const x, int const y);
int		checkWinColumn(char const pion, t_grid const grid, int const x, int const y);
int		checkWinD1(char const pion, t_grid const grid, int const x, int const y);
int		checkWinD2(char const pion, t_grid const grid, int const x, int const y);

//	player.c
void	playerAction(t_grid *grid, int const action);
void	botAction(t_grid *grid, int const action);
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
void	displayEndOfGame(t_grid const grid, int const action, int const turn);

//	error.c
int		errorArgNbr(void);
int		errorArgVal(void);
int		errorMalloc(void);

/********************/
/*		Bonus		*/
/********************/

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	
	t_img	board;
	t_img	red;
	t_img	yellow;
}	t_mlx;

//	error.c
int		errorMlx(void);

#endif
