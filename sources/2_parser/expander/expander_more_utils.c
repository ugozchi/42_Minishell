/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_more_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:35 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:57:36 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	failed_mess(t_data *data, char *mess, int code)
{
	ft_putstr_fd(mess, 2);
	if (*mess)
		ft_putstr_fd("\n", 2);
	data->exit_status += code;
}

char	*give_me_inside_var(char *var, t_data *data)
{
	char	*in_var;
	t_env	*tmp;

	in_var = NULL;
	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, var) == 0)
		{
			in_var = ft_strdup(tmp->value);
			if (!in_var)
				return (failed_mess(data, "malloc failed", 1), NULL);
			return (in_var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*extract_var(char *str, int *i)
{
	char	*var;
	size_t	var_len;

	if (!str)
		return (NULL);
	if (str[0] == '$' && str[1] == '$')
	{
		(*i) += 2;
		return (ft_strdup("$$"));
	}
	if (str[0] == '?' && (*i)++)
		return (ft_strdup("?"));
	var_len = get_var_len(str);
	if (var_len == 0)
		return (NULL);
	(*i)++;
	var = ft_substr(str, 1, var_len);
	if (!var)
		return (NULL);
	(*i) += var_len;
	return (var);
}

char	*ft_concatenate(char *before, char *in_var)
{
	char	*result;
	size_t	total_len;

	total_len = ft_strlen(before) + ft_strlen(in_var);
	result = malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	ft_strcpy(result, before);
	ft_strcat(result, in_var);
	return (result);
}
