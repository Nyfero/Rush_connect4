/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:38:56 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 17:04:16 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

void	playerAction(t_grid *grid, int const action) {
	int	i = 0;

	while (grid->map[action - 1][i] == '.')
		i++;
	grid->map[action - 1][i - 1] = 'X';
}

void	botAction(t_grid *grid, int const action) {
	int	i = 0;

	while (grid->map[action - 1][i] == '.')
		i++;
	grid->map[action - 1][i - 1] = 'O';
}

int	askPlayer(t_grid const grid) {
	char	*input;
	int		ret = 0;
	
	ft_putstr("Please enter a value: ");
	input = get_next_line(0);
	while (!ret)
	{
		if (input)
		{
			if (isInt(input))
			{
				if (isInGrid(input, grid))
				{
					ret = ft_atoi(input);
					free(input);
					return (ret);
				}
			}
		}
		free(input);
		ft_putstr("Please enter a valid value: ");
		input = get_next_line(0);
	}
	return (-1);
}

int	isInt(char const *input) {
	if (input[0] != '+' && !ft_isdigit(input[0]))
		return (0);
	for(int i = 1; input[i]; i++)
		if (!ft_isdigit(input[i]))
			return (0);
	return (1);
}

int	isInGrid(char const *input, t_grid const grid) {
	int	check = ft_atoi(input);
	
	if (check - 1 >= grid.column || check <= 0)
	{
		ft_putstr("\e[91mYou play is out of the grid !\e[39m\n");
		return (0);
	}
	if (grid.map[check - 1][0] != '.')
	{
		ft_putstr("\e[91mThe column is full !\e[39m\n");
		return (0);
	}
	return (1);
}
