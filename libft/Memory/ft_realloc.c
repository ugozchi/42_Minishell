/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:22:45 by uzanchi           #+#    #+#             */
/*   Updated: 2024/12/13 12:22:46 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	**ft_realloc(void **ptr, size_t old_count, size_t new_count)
{
	void	**new_ptr;
	size_t	copy;

	new_ptr = malloc(new_count * sizeof(void *));
	if (!new_ptr)
		return (NULL);
	if (old_count < new_count)
		copy = old_count;
	else
		copy = new_count;
	ft_memcpy(new_ptr, ptr, copy * sizeof(void *));
	if (copy < new_count)
		ft_bzero(new_ptr + copy, (new_count - copy) * sizeof(void *));
	free(ptr);
	return (new_ptr);
}
