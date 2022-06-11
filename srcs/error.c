/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:04:30 by gsap              #+#    #+#             */
/*   Updated: 2022/06/11 14:48:29 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/connect4.h"

int	errorArgNbr(void) {
	ft_putstr_fd("The grid size must be taken as parameters to the program.\nEx: ./connect4 8 10\n", 2);
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
