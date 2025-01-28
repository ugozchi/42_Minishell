/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:31 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/22 10:45:55 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var_or_exit(t_data *data, char *var, int *i)
{
	char	*before;
	char	*in_var;

	before = ft_strdup(data->expanded_str);
	if (!before)
		return (failed_mess(data, "malloc failed", 1), NULL);
	if (ft_strcmp(var, "$?") == 0)
	{
		in_var = ft_itoa(data->exit_status);
		(*i) += 2;
	}
	else if (is_exist_in_env(var, data))
		in_var = give_me_inside_var(var, data);
	else
		in_var = ft_strdup("");
	free(var);
	free(data->expanded_str);
	data->expanded_str = ft_concatenate(before, in_var);
	free(before);
	free(in_var);
	if (!data->expanded_str)
		return (failed_mess(data, "malloc failed", 1), NULL);
	return (data->expanded_str);
}

char	*process_character(t_data *data, char *str, int *i)
{
	char	*tmp;

	tmp = ft_strdup(data->expanded_str);
	if (!tmp)
		return (failed_mess(data, "malloc failed", 1), NULL);
	free(data->expanded_str);
	data->expanded_str = ft_strjoin_char(tmp, str[*i]);
	free(tmp);
	if (!data->expanded_str)
		return (failed_mess(data, "malloc failed", 1), NULL);
	(*i)++;
	return (data->expanded_str);
}

char	*process_expansion(char *str, t_data *data, int *i)
{
	char	*var;

	if (str[*i] == '$' && str[*i + 1] == '?' && !is_in_single_quotes(str, *i))
	{
		var = ft_strdup("$?");
		if (!var)
			return (failed_mess(data, "malloc failed", 1), NULL);
		return (expand_var_or_exit(data, var, i));
	}
	if (str[*i] == '$' && !is_in_single_quotes(str, *i))
	{
		var = extract_var(str + *i, i);
		if (!var)
			return (failed_mess(data, "Failed to extract variable", 1), NULL);
		return (expand_var_or_exit(data, var, i));
	}
	return (process_character(data, str, i));
}

char	*expan_var(char *str, t_data *data)
{
	int	i;

	i = 0;
	data->expanded_str = ft_strdup("");
	if (!data->expanded_str)
		return (NULL);
	while (str[i])
	{
		data->expanded_str = process_expansion(str, data, &i);
		if (!data->expanded_str)
		{
			free(data->expanded_str);
			return (NULL);
		}
	}
	return (data->expanded_str);
}

int	expander(t_data *data)
{
	if (!data->line)
		return (EXIT_FAILURE);
	data->expanded_str = NULL;
	if (dollar_in_str(data->line))
	{
		expan_var(data->line, data);
		if (!data->expanded_str)
			return (EXIT_FAILURE);
		free(data->line);
		data->line = data->expanded_str;
		if (!data->line)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
