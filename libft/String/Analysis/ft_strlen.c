/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:21:25 by uzanchi           #+#    #+#             */
/*   Updated: 2024/12/13 12:21:26 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	if (!str)
		return (0);
	while (*str++)
		length++;
	return (length);
}
/*
#include <stdio.h>

int	main()
{
	const char *string;

	string = NULL;
	printf("%ld\n", ft_strlen(string));
}
*/
