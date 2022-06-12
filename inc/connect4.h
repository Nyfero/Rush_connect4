/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:51 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 16:03:30 by gsap             ###   ########.fr       */
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
	int		*scoreGrid;
	int		line;
	int		column;
}	t_grid;

typedef struct s_aiVal{
	int	first;
	int	second;
	int	third;
} t_aiVal;

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

//ia.c
int	getBestAction(t_grid const *grid, int const player);
void	evalWholeGrid(t_grid const *grid, int const player);
int		eval(t_grid const *grid, int const action, int const player);
t_aiVal	possibleAlign(t_grid const * grid, int const action, int const player, int const direction);
void	decrementPos(int *x, int *y, int const direction);
void	incrementPos(int *x, int *y, int const direction);

/********************/
/*		Bonus		*/
/********************/

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

typedef struct s_imge
{
	void	*img;
	int		height;
	int		width;
}	t_imge;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	
	t_imge	board;
	t_imge	red;
	t_imge	yellow;
	
	t_grid	*grid;
	int		cursor;
	int		turn;
}	t_mlx;


//	error.c
int		errorMlx(void);

//	init.c
int		initMlx(t_mlx **data, int const column, int const line, t_grid *grid);
int		initImg(t_mlx *data);
void	freeMlx(t_mlx *data);

//	mlx.c
int		keyboard(int keycode, t_mlx *data);
void	moveLeft(t_mlx *data);
void	moveRight(t_mlx *data);
int		closeGame(t_mlx *data);
void	playerTurn(t_mlx *data);
void	IATurn(t_mlx *data);

//	game.c
void	startGameBonus(t_mlx *data);

//	display.c
void	displayInterface(t_mlx *data);
void	displayHelp(void);

#endif
