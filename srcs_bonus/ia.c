#include "connect4.h"

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
	t_aiVal	ret = {-1, -1, -1};
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
	ft_memset(&ret, 0, sizeof(t_aiVal));
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

	int	score = 0;
	int	multi;
	int	const opponent = player ? 0 : 1;
	t_aiVal ret = possibleAlign(grid, action, player, HORIZONTAL);
	t_aiVal ret2 = possibleAlign(grid, action, opponent, HORIZONTAL);

	if ( ret.third >= 4 )
		return (INT_MAX);
	else if (ret2.third >= 4 )
		return (INT_MAX - 1);
	else if (ret.first < 0)
		return (-1);
	else if ( ret.first == 4 ) {
		multi = 1;
		if (ret.second== OPENBOTH)
			multi = 3;
		else if (ret.second)
			multi = 2;
		score += (ret.third * 5 * multi);
	}

	ret = possibleAlign(grid, action, player, VERTICAL);
	ret2 = possibleAlign(grid, action, opponent, VERTICAL);

	if ( ret.third >= 4 )
		return (INT_MAX);
	else if (ret2.third >= 4 )
		return (INT_MAX - 1);
	else if (ret.first < 0)
		return (-1);
	else if ( ret.first == 4 ) {
		multi = 1;
		if (ret.second== OPENBOTH)
			multi = 3;
		else if (ret.second)
			multi = 2;
		score += (ret.third * 5 * multi);
	}

	ret = possibleAlign(grid, action, player, DIAG_UP);
	ret2 = possibleAlign(grid, action, opponent, VERTICAL);

	if ( ret.third >= 4 )
		return (INT_MAX);
	else if (ret2.third >= 4 )
		return (INT_MAX - 1);
	else if (ret.first < 0)
		return (-1);
	else if ( ret.first == 4 ) {
		multi = 1;
		if (ret.second== OPENBOTH)
			multi = 3;
		else if (ret.second)
			multi = 2;
		score += (ret.third * 5 * multi);
	}

	ret = possibleAlign(grid, action, player, DIAG_DOWN);
	ret2 = possibleAlign(grid, action, opponent, VERTICAL);

	if ( ret.third >= 4 )
		return (INT_MAX);
	else if (ret2.third >= 4 )
		return (INT_MAX - 1);
	else if (ret.first < 0)
		return (-1);
	else if ( ret.first == 4 ) {
		multi = 1;
		if (ret.second== OPENBOTH)
			multi = 3;
		else if (ret.second)
			multi = 2;
		score += (ret.third * 5 * multi);
	}

	return score;
}

int	getBestAction(t_grid const *grid, int const player) {

	int const opponent = player? 0 : 1;
	int	playerBest = -2;
	int	playerBestAction;
	int	opponentBest = -2;
	int	opponentBestAction;
	char playerPiece = player ? PLAYERCHAR : IACHAR;
	for (int i = 0; i < grid->column; i++) {
		grid->scoreGrid[i] = eval(grid, i, player);
		if (grid->scoreGrid[i] > playerBest){
			playerBest = grid->scoreGrid[i];
			playerBestAction = i;
		}
	}
	for (int i = 0; i < grid->column; i++){
		int tmp = eval(grid, i, opponent);
		if (tmp > opponentBest) {
			opponentBest = tmp;
			opponentBestAction = i;
		}
	}
	if (playerBest == INT_MAX)
		return (playerBestAction + 1);
	else if (opponentBest == INT_MAX)
		return (opponentBestAction + 1);
	else if (playerBest > opponentBest) {

		int actionY;
		int	opponentBest2 = -2;
		int	opponentBestAction2;
		for (actionY = grid->line - 1 ; actionY >= 0 ; actionY--) {
			if (grid->map[playerBestAction][actionY] == '.')
				break;
		}
		grid->map[playerBestAction][actionY] =  playerPiece;
		for (int i = 0; i < grid->column; i++){
			int tmp = eval(grid, i, opponent);
			if (tmp > opponentBest2) {
				opponentBest2 = tmp;
				opponentBestAction2 = i;
			}
		}
		grid->map[playerBestAction][actionY] =  '.';
		if (playerBest > opponentBest2)
			return (playerBestAction + 1);
		else
			return (opponentBestAction + 1);
	}
	else
		return (opponentBestAction + 1);
}
