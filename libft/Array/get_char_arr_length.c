/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char_arr_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:25:13 by uzanchi           #+#    #+#             */
/*   Updated: 2024/12/13 12:25:14 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_get_char_arr_length(char **arr)
{
	size_t	length;

	length = 0;
	while (*arr)
	{
		length++;
		arr++;
	}
	return (length);
}
