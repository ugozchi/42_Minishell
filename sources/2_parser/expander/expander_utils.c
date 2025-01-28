/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:39 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:57:41 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_len(char *str)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	i++;
	if (!str)
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	return (len);
}

int	is_exist_in_env(char *var, t_data *data)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, var) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_in_single_quotes(char *str, int index)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && i < index)
	{
		if (!str[i])
			return (in_single);
		if (str[i] == '\"' && !in_double)
			in_double = 1;
		else if (str[i] == '\"' && in_double)
			in_double = 0;
		if (str[i] == '\'' && !in_double && !in_single)
			in_single = 1;
		else if (str[i] == '\'' && !in_double && in_single)
			in_single = 0;
		i++;
	}
	return (in_single);
}

char	*ft_strjoin_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	if (!str)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
