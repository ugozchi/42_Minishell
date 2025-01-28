/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:21 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 18:02:38 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_just_spaces(char *arg)
{
	while (*arg)
	{
		if (!ft_isspace(*arg++))
			return (0);
	}
	return (1);
}

t_token	*init_new_token(t_type type, t_quote quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("malloc error");
		return (NULL);
	}
	new->type = type;
	new->quote = quote;
	new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*new_token(char *start, char *end, t_type type, t_quote quote)
{
	t_token	*new;

	new = init_new_token(type, quote);
	if (!new)
	{
		free(start);
		return (NULL);
	}
	if (start && end && end >= start)
	{
		new->value = extract_token_value(start, end, quote);
		if (!new->value)
		{
			free(new);
			free(start);
			return (NULL);
		}
	}
	return (new);
}

char	*extract_token_value(char *start, char *end, t_quote quote)
{
	char	*temp;

	if (quote == DQ)
	{
		temp = ft_substr(start, 0, end - start + 1);
		if (!temp)
		{
			perror("token value malloc");
			return (NULL);
		}
		return (ft_strdup(temp));
	}
	else
	{
		temp = ft_substr(start, 0, end - start + 1);
		if (start)
			free(start);
		start = NULL;
		return (temp);
	}
}

void	lst_token_add_back(t_data *data, t_token *new)
{
	t_token	*tmp;

	if (!data->token)
	{
		new->prev = NULL;
		data->token = new;
		return ;
	}
	else
	{
		tmp = data->token;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}
