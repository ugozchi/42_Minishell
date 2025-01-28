/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:56:55 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 12:06:44 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	perror_return(char *str)
{
	fprintf(stderr, "%s\n", str);
	return (EXIT_FAILURE);
}

int	ft_printf_exit_code(char *str, int exit_code)
{
	printf("%s", str);
	return (exit_code);
}

int	add_new_list_node(t_list **list, t_token *token)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (perror_return("malloc for new list node"));
	ft_memset(new, 0, sizeof(t_list));
	new->value = ft_strdup(token->value);
	if (!new->value)
		return (perror_return("malloc for new list node value"));
	new->quote = token->quote;
	if (!*list)
		*list = new;
	else
		ft_lst_addback(*list, new);
	return (EXIT_SUCCESS);
}

void	ft_lst_addback(t_list *list, t_list *new)
{
	t_list	*ptr;

	{
		ptr = list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}
