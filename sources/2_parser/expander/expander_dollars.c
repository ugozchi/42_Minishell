/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:27 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:57:28 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_in_str(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		if (str[i] == '$' && !in_single)
		{
			if (str[i + 1] == '$' || str[i + 1] == '?'
				|| ft_isalnum(str[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

static char	*append_pid(char *result)
{
	char	*temp;
	char	*pid_str;

	pid_str = ft_strdup("(pid)");
	if (!pid_str)
		return (NULL);
	if (!result)
		result = ft_strdup(pid_str);
	else
	{
		temp = ft_strjoin(result, pid_str);
		free(result);
		result = temp;
	}
	free(pid_str);
	return (result);
}

static char	*append_exit_status(char *result, int exit_status)
{
	char	*temp;
	char	*status_str;

	status_str = ft_itoa(exit_status);
	if (!status_str)
		return (NULL);
	if (!result)
		result = ft_strdup(status_str);
	else
	{
		temp = ft_strjoin(result, status_str);
		free(result);
		result = temp;
	}
	free(status_str);
	return (result);
}

char	*expand_dollar_sequence(char **str, int *i, t_data *data)
{
	char	*result;

	result = NULL;
	while ((*str)[*i] == '$')
	{
		(*i)++;
		if ((*str)[*i] == '$')
		{
			result = append_pid(result);
			(*i)++;
		}
		else if ((*str)[*i] == '?')
		{
			result = append_exit_status(result, data->exit_status);
			(*i)++;
		}
		else
		{
			if (!result)
				result = ft_strdup("$");
		}
		if (!result)
			return (NULL);
	}
	return (result);
}
