/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:41:00 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/22 10:47:07 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_new_env(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		tmp = env->next;
		i++;
		env = tmp;
	}
	return (i);
}

static char	*recup_line_env(t_env *env, char **env_to_tab, int i)
{
	char	*temp;

	if (env->type)
	{
		env_to_tab[i] = ft_strdup(env->type);
		if (!env_to_tab[i])
			return (NULL);
	}
	if (env->value)
	{
		temp = ft_strjoin(env_to_tab[i], "=");
		free(env_to_tab[i]);
		if (!temp)
			return (NULL);
		env_to_tab[i] = ft_strjoin(temp, env->value);
		free(temp);
		if (!env_to_tab[i])
			return (NULL);
	}
	return (env_to_tab[i]);
}

static char	**recup_env(t_env *env, t_env *tmp, char **env_to_tab)
{
	int	i;

	i = 0;
	while (env)
	{
		tmp = env->next;
		env_to_tab[i] = recup_line_env(env, env_to_tab, i);
		if (!env_to_tab[i])
			return (NULL);
		i++;
		env = tmp;
	}
	env_to_tab[i] = NULL;
	return (env_to_tab);
}

char	**env_to_tab(t_env *env)
{
	t_env	*tmp;
	char	**env_to_tab;

	tmp = env;
	if (!len_new_env(env))
	{
		env_to_tab = (char **)malloc(sizeof(char *) * 1);
		if (!env_to_tab)
			return (NULL);
		env_to_tab[0] = "\0";
		return (env_to_tab);
	}
	env_to_tab = (char **)malloc(sizeof(char *) * (len_new_env(env) + 1));
	if (!env_to_tab)
		return (NULL);
	tmp = env;
	recup_env(env, tmp, env_to_tab);
	return (env_to_tab);
}
