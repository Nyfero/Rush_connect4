#include "connect4.h"

//incremente une position x,y dans une direction donnée
void	incrementPos(int *x, int *y, int const direction) {

	if (direction != VERTICAL)
		(*x)++;
	if (direction == DIAG_DOWN || direction == VERTICAL)
		(*y)++;
	else if (direction == DIAG_UP)
		(*y)--;
}

//décremente une position x,y dans une direction donnée
void	decrementPos(int *x, int *y, int const direction) {

	if (direction != VERTICAL)
		(*x)--;
	if (direction == DIAG_DOWN || direction == VERTICAL)
		(*y)--;
	else if (direction == DIAG_UP)
		(*y)++;
}

/*
** Pour un coup théorique, dans une direction donnée, 
** calcule a la fois le nombre de pions qu'il connecte effectivement,
** le nombre de pions qui pourrait etre connecté a l'avenir
** et si le jeu est ouvert sur les cotés de cet alignement (déso)
*/
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

/*
** utilise la fonction possibleAlign sur une direction pour un coup donné
** et renvoie la valeur du coup avec cette priorité :
** 1/ le coup est gagnant pour l'IA
** 2/ le coup est gagnant pour le joueur adverse
** 3/ le coup donnerait un alignement de 3 ouvert des deux cotés pour le joueur adverse
** 4/ le coup donnerait un alignement de 3 ouvert des deux cotés pour l'IA
** 5/ donne une valeur a l'arrache basé sur le nb de pions alignés et le nombre d'ouvertures
*/
int	evalDir(t_grid const *grid, int const action, int const player, int const dir) {
	int	score = 0;
	int	multi;
	int	const opponent = player ? 0 : 1;
	t_aiVal ret = possibleAlign(grid, action, player, dir);
	t_aiVal ret2 = possibleAlign(grid, action, opponent, dir);

	if ( ret.third >= 4 )
		return (INT_MAX);
	else if (ret2.third >= 4 )
		return (INT_MAX - 1);
	else if (ret2.third == 3 && ret2.second == OPENBOTH)
		return (INT_MAX - 2);
	else if (ret.third == 3 && ret.second == OPENBOTH)
		return (INT_MAX - 3);
	else if (ret.first < 0)
		return (-1);
	else if ( ret.first == 4 ) {
		multi = 1;
		if (ret.second== OPENBOTH)
			multi = 3;
		else if (ret.second)
			multi = 2;
		score = ((ret.third * 5) + multi);
	}
	return score;
}

int	max(int x, int y) {
	return (x > y ? x : y);
}

// renvoit le score d'un coup (calculé plus haut)
int	eval(t_grid const *grid, int const action, int const player) {
	int	score, hz, vr, d1, d2;
	
	hz = evalDir(grid, action, player, HORIZONTAL);
	vr = evalDir(grid, action, player, VERTICAL);
	d1 = evalDir(grid, action, player, DIAG_UP);
	d2 = evalDir(grid, action, player, DIAG_DOWN);
	score = max(max(hz, vr), max(d1,d2));
	if (score < INT_MAX - 3)
		score = hz + vr + d1 + d2;
	return (score);
}

/*
** Fix de derniere minute qui choisit le deuxieme meilleur coup dans le cas ou :
** le meilleur coup est moins bon que le meilleur coup du joueur mais
** qu'on ne veut pas bloquer le joueur car c'est le meme coup
*/
int	getNonMortalMove(t_grid const *grid, int const player, int const opponentBestAction){
	int ret = opponentBestAction;
	int	playerBest = -2;
	int	playerBestAction = -2;

	for (int i = 0; i < grid->column; i++) {
		if (i != opponentBestAction) {
			int tmp = eval(grid, i, player);
			if (tmp > playerBest){
				playerBest = tmp;
				playerBestAction = i;
			}
		}
	}
	if (playerBestAction != -2)
		ret = playerBestAction;
	return ret;
}

/* 
** evalue le score de tout les coups possibles pour l'IA, garde le meilleur,
** puis fais la meme chose pour le joueur adverse
** si l'IA a un meilleur coup elle evalue alors le meilleur prochain coup du joueur :
** si celui ci est meilleur que le meilleur coup initial de l'IA alors :
** l'IA fais comme si son meilleur coup initial etait moins bon que le meilleur coup initial du joueur:
** elle bloque celui ci
*/
int	getBestAction(t_grid const *grid, int const player) {

	int const opponent = player? 0 : 1;
	int	playerBest = -2;
	int	playerBestAction;
	int	opponentBest = -2;
	int	opponentBestAction;
	char playerPiece = player ? PLAYERCHAR : IACHAR;
	for (int i = 0; i < grid->column; i++) {
		int tmp = eval(grid, i, player);
		if (tmp > playerBest){
			playerBest = tmp;
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
		int	ret;
		if (playerBest > opponentBest2)
			ret = (playerBestAction + 1);
		else {
			if (opponentBestAction != opponentBestAction2)
				ret = (opponentBestAction + 1);
			else {
				ret = getNonMortalMove(grid, player, opponentBestAction);
			}
		}
		grid->map[playerBestAction][actionY] =  '.';
		return ret;

	}
	else
		return (opponentBestAction + 1);
}
