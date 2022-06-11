#include "connect4.h"
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAG_UP 2
#define DIAG_DOWN 3

#define OPENLEFT 1
#define OPENRIGHT 2
#define OPENBOTH 3

#define PLAYERCHAR 'X'
#define IACHAR 'O'

void	incrementPos(int *x, int *y, int const direction) {

	if (direction != VERTICAL)
		(*x)++;
	if (direction == DIAG_DOWN || direction == VERTICAL)
		(*y)++;
	else if (direction == DIAG_UP)
		(*y)--;
}

void	decrementPos(int *x, int *y, int const direction) {

	if (direction != VERTICAL)
		(*x)--;
	if (direction == DIAG_DOWN || direction == VERTICAL)
		(*y)--;
	else if (direction == DIAG_UP)
		(*y)++;
}

t_aiVal	possibleAlign(t_grid const * grid, int const action, int const player, int const direction) {

	char playerPiece;
	t_aiVal	ret = {0, 0, 0};
	int	actionY;

	if (action < 0 || action >= grid->column)
		return ret;
	for (actionY = grid->line - 1 ; actionY >= 0 ; actionY--) {
		if (grid->map[action][actionY] == '.')
			break;
	}
	if (actionY < 0)
		return ret;
	if (player)
		playerPiece = PLAYERCHAR;
	else
		playerPiece = IACHAR;
	grid->map[action][actionY] = playerPiece;
	int tempY = actionY;
	int	tempX = action;
	int	count = 1;
	int	i = 0;
	while ( i < 4 && tempX >= 0 && tempY >= 0 && tempY < grid->line && (grid->map[tempX][tempY] == playerPiece || grid->map[tempX][tempY] == '.') ){
		if (ret.second == 0 && grid->map[tempX][tempY] == '.') {
			ret.second = OPENLEFT;
			count = 0;
		}
		if (count)
			ret.third++;
		decrementPos(&tempX, &tempY, direction);
		i++;
	}
	incrementPos(&tempX, &tempY, direction);
	while ( tempX != action || tempY != actionY ) {
		incrementPos(&tempX, &tempY, direction);
		ret.first++;
	}
	ret.first++;
	incrementPos(&tempX, &tempY, direction);
	count = 1;
	i = 0;
	while ( i < 4 && tempX < grid->column && tempY >= 0 && tempY < grid->line && (grid->map[tempX][tempY] == playerPiece || grid->map[tempX][tempY] == '.') ){
		if (ret.second < OPENRIGHT && grid->map[tempX][tempY] == '.') {
			ret.second += OPENRIGHT;
			count = 0;
		}
		if (count)
			ret.third++;
		incrementPos(&tempX, &tempY, direction);
		ret.first++;
	}
	if (ret.first > 4)
		ret.first = 4;
	grid->map[action][actionY] = '.';
	return ret;
}

int	eval(t_grid const *grid, int const action, int const player) {

	t_aiVal ret = possibleAlign(grid, action, player, HORIZONTAL);
	printf("HORIZONTAL ALIGN : open = ");
	switch (ret.second) {

		case OPENLEFT:
			printf("LEFT");
			break;
		case OPENRIGHT:
			printf("RIGHT");
			break;
		case OPENBOTH:
			printf("BOTH");
			break;
		default:
			printf("NONE");
			break;
	}
	printf(", max alignement : %d, current alignment : %d\n", ret.first, ret.third);
	ret = possibleAlign(grid, action, player, VERTICAL);
	printf("VERTICAL ALIGN : open = ");
	switch (ret.second) {

		case OPENLEFT:
			printf("LEFT");
			break;
		case OPENRIGHT:
			printf("RIGHT");
			break;
		case OPENBOTH:
			printf("BOTH");
			break;
		default:
			printf("NONE");
			break;
	}
	printf(", max alignement : %d, current alignment : %d\n", ret.first, ret.third);
	ret = possibleAlign(grid, action, player, DIAG_UP);
	printf("DIAGONAL UP ALIGN : open = ");
	switch (ret.second) {

		case OPENLEFT:
			printf("LEFT");
			break;
		case OPENRIGHT:
			printf("RIGHT");
			break;
		case OPENBOTH:
			printf("BOTH");
			break;
		default:
			printf("NONE");
			break;
	}
	printf(", max alignement : %d, current alignment : %d\n", ret.first, ret.third);
	ret = possibleAlign(grid, action, player, DIAG_DOWN);
	printf("DIAGONAL DOWN ALIGN : open = ");
	switch (ret.second) {

		case OPENLEFT:
			printf("LEFT");
			break;
		case OPENRIGHT:
			printf("RIGHT");
			break;
		case OPENBOTH:
			printf("BOTH");
			break;
		default:
			printf("NONE");
			break;
	}
	printf(", max alignement : %d, current alignment : %d\n", ret.first, ret.third);
	return 1;
}
