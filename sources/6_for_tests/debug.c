/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:35:42 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/24 12:42:28 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_final_group(t_commands *cmd)
// {
// 	if (!cmd)
// 	{
// 		printf("Commande vide.\n");
// 		return ;
// 	}
// 	printf("\n%sCommande : %s%s\n", ROSE, RESET,
// 		cmd->command ? cmd->command : "NULL");
// 	if (cmd->final_group)
// 	{
// 		printf("%sFinal Group:%s\n", BLUE, RESET);
// 		for (int i = 0; cmd->final_group[i] != NULL; i++)
// 			printf("  [%d]: %s\n", i, cmd->final_group[i]);
// 	}
// 	else
// 	{
// 		printf("Final Group est vide.\n");
// 		return ;
// 	}
// 	return ;
// }

// const char	*get_type_name(t_type type)
// {
// 	switch (type)
// 	{
// 		case CMD:
// 			return ("CMD");
// 		case ARG:
// 			return ("ARG");
// 		case OUTPUT:
// 			return ("OUTPUT");
// 		case INPUT:
// 			return ("INPUT");
// 		case APPEND:
// 			return ("APPEND");
// 		case HEREDOC:
// 			return ("HEREDOC");
// 		case LIM:
// 			return ("LIM");
// 		case PIPE:
// 			return ("PIPE");
// 		case FLAG:
// 			return ("FLAG");
// 		case STDIN:
// 			return ("STDIN");
// 		case STDOUT:
// 			return ("STDOUT");
// 		case ARG_IN_OUT:
// 			return ("ARG_OUT");
// 		default:
// 			return ("UNKNOWN");
// 	}
// }

// void	print_tokens(t_token *token)
// {
// 	const char	*color;
// 	int			token_number = 0;
// 	t_token		*start;
// 	start = token;

// 	while (token)
// 	{
// 		if (token->type == CMD || token->type == FLAG)
// 			color = BLUE;
// 		else if (token->type == ARG || token->type == ARG_IN_OUT)
// 			color = ROSE;
// 		else if (token->type == OUTPUT || token->type == INPUT
// 			|| token->type == APPEND)
// 			color = GREEN;
// 		else if (token->type == PIPE)
// 			color = CYAN;
// 		else if (token->type == HEREDOC || token->type == LIM)
// 			color = PURPLE;
// 		else
// 			color = RESET;
// 		printf("token_number = %d\n", token_number);
// 		printf("\n%s========== TOKEN %d ==========%s\n", GREEN, token_number,
// 			RESET);
// 		printf("%sType        : [%s]%s\n", color, get_type_name(token->type),
// 			RESET);
// 		printf("%sValue       : [%s]%s\n", color, token->value, RESET);
// 		printf("%s-----------------------------%s\n", ROSE, RESET);
// 		token = token->next;
// 		token_number++;
// 	}
// 	token = start;
// }
