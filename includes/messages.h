/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:49:48 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 15:59:33 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

/*****************************COLORS**********************************/

# define RESET          "\033[0m"
# define BLACK          "\033[0;30m"
# define RED            "\033[1;31m"
# define GREEN          "\033[1;32m"
# define YELLOW         "\033[0;33m"
# define BLUE           "\033[0;34m"
# define PURPLE         "\033[1;35m"
# define CYAN           "\033[1;36m"
# define WHITE          "\033[0;37m"
# define ROSE           "\033[38;5;216m"
# define ORANGE         "\033[38;5;208m"
# define DARK_YELLOW    "\033[38;5;136m"
# define LIGHT_PURPLE   "\033[38;5;177m"
# define BOLD           "\033[1m"
# define UNDERL         "\033[4m"
# define GREY           "\033[38;2;184;134;11m"

/*****************************messages**********************************/
# define H          "minishell: syntax error: unexpected token '<<<'\n"      
# define A          "minishell: syntax error: unexpected token '>>>'\n"
# define G          "minishell: syntax error: unexpected token '<'\n"
# define P          "minishell: syntax error: unexpected token '|'\n"
# define M          "minishell: syntax error: unexpected token\n"
/*****************************PROMPT**********************************/

# define PROMPT             "\033[0;34mminishell$\033[1;35m> \033[0m"
# define HERE_DOC_PROMPT    "\033[1;35m> \033[0m"
# define PROMPTE             "minishell$ "
# define HERE_DOC_PROMPTE    "heredoc>"

/*****************************MESSAGES**********************************/

# define UNEXPECTED_PIPE "Syntax error: unexpected token '|' in argument\n"
# define UNCLOSED_QUOTE "Syntax error: unclosed quote in argument\n"
# define GET_PID "(pid)"

/*Executer*/
# define CMD_NOT_FOUND "minishell: command not found: "
# define MALLOC_ERR_PIPE "minishell: couldn't malloc pipes array"
# define PIPING_ERR "minishell: error while piping"
# define FD_ERR_CLOSE "minishell: error while closing fd"

/********************************BUILTINS*************************************/
/*cd*/
# define CD_ERR_HOME "minishell: cd: HOME not set\n"
# define CD_ERR_OLDPWD "minishell: cd: OLDPWD not set\n"
# define CD_ERR_FLAGS "minishell: cd: no options supported\n"
# define CD_ERR_ARG "minishell: cd: too many arguments\n"

/*echo*/
# define ECHO_ERR_FLAG "minishell: cd: only -n is supported\n"

/*env*/
# define ENV_ERR_ARG "minishell: env: too many arguments\n"
# define ENV_ERR_FLAGS "minishell: env: no options supported\n"
# define INVALID_ARG_ENV "minishell : env: too many arguments\n"

/*exit*/
# define EXIT_ERR_EXTRA_ARG "minishell: exit: too many arguments\n"
# define EXIT_ERR_NON_NUM_ARG "minishell: exit: numeric argument required\n"

/*export*/
# define EXPORT_ERR_FLAGS "minishell: export: no options supported\n"
# define EXPORT_ERR_ARG "minishell: export: too many arguments\n"
# define EXPORT_ERR_INVALID_NAME "minishell : export : invalid name\n"
# define EXPORT_ERR_IDENTIFIER "minishell : export : invalid identifier\n"
/*pwd*/
# define PWD_ERR_FLAGS "minishell: pwd: no options supported\n"
# define PWD_ERR_EXTRA_ARG "minishell: pwd: too many arguments\n"
# define PWD_ERR_PWD_NOT_FOUND "minishell: pwd: PWD not found in env and with\
                                getcwd\n"

/*unset*/
# define UNSET_ERR_FLAGS "minishell: unset: no options supported\n"
# define UNSET_ERR_IDENTIFIER "minishell: unset: no options supported\n"

#endif
