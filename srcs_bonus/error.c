/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:30 by gsap              #+#    #+#             */
/*   Updated: 2022/06/12 20:42:01 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

long long	ft_strtoll(const char *str, char **end)
{
	unsigned long long	result;
	int					i;
	int					j;
	int					sign;

	i = 0;
	j = 0;
	result = 0;
	sign = 1 - (2 * (str[i] == '-'));
	i += (str[i] == '-' || str[i] == '+');
	while (ft_isdigit(str[i + j]))
	{
		result = result * 10 + str[i + j++] - '0';
		if (result > (unsigned long long)(LONG_MAX + (sign == -1)))
			j = 0;
		if (result > (unsigned long long)(LONG_MAX + (sign == -1)))
			break ;
	}
	if (end && !j)
		*end = (char *)str;
	else if (end)
		*end = (char *)(str + i + j);
	return (result * sign);
}

int	errorArgNbr(void) {
	ft_putstr_fd("The grid size must be taken as parameters to the program + an argument to activate or not the graphical interface.\nEx: ./connect4_bonus 8 10 1\n", 2);
	return (1);
}

int	errorArgVal(void) {
	ft_putstr_fd("The minimum size is 6 lines and 7 columns.\n", 2);
	return (1);
}

int	errorMalloc(void) {
	ft_putstr_fd("Malloc failed :(\n", 2);
	return (1);
}

int	errorMlx(void) {
	ft_putstr_fd("Mlx failed :(\n", 2);
	return (1);
}
