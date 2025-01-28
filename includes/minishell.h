/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:11:42 by melinamotyl       #+#    #+#             */
/*   Updated: 2025/01/24 15:34:57 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "messages.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>

/********************************MACROS***************************************/
# define SUPPORTED_SYMBOLS "<|>"
# define FDX_NONE -1 // Aucun fd paticulier ne doit etre open
# define FDX_OR 0    // Seul entre pipe read reste ouverte
# define FDX_OW 1    // Seule la sortie pipe write reste ouvert
# define FDX_RW 2    // Les deux (entree et sortie doivent rester ouvert)

# ifndef GLOBALS_H
#  define GLOBALS_H

extern int	g_waiting;

# endif

/******************************DATA_STRUCTURE**********************************/
typedef enum e_quote
{
	NQ,
	SQ,
	DQ,
}						t_quote;

typedef enum e_type
{
	CMD,
	ARG,
	OUTPUT,
	INPUT,
	APPEND,
	HEREDOC,
	LIM,
	PIPE,
	FLAG,
	STDIN,
	STDOUT,
	ARG_IN_OUT,
}						t_type;

typedef struct s_list
{
	char				*value;
	t_quote				quote;
	struct s_list		*next;
}						t_list;

typedef struct s_commands
{
	char				*command;
	char				**final_group;

	t_list				*flag;
	t_list				*arg;
	t_quote				command_quote;

	struct s_commands	*next;
}						t_commands;

typedef struct s_token
{
	char				*value;

	t_type				type;
	t_quote				quote;

	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_in_out
{
	int					fd;
	char				*value;
	t_type				type;
	t_quote				quote;
}						t_in_out;

typedef struct s_env
{
	char				*type;
	char				equal;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_redir
{
	int					infile;
	int					outfile;
	int					fds_doc[2];
	int					heredoc;
}						t_redir;

typedef struct s_pipes
{
	int					nb_pipe;
	int					**fds;
	pid_t				*pid;
	int					orig_fds[2];
}						t_pipes;

typedef struct s_data
{
	char				wich_quote_err;
	char				**env;
	char				**new_env;
	char				*expanded_str;

	char				**path;
	char				*full_path;
	char				*line;
	int					exit_status;

	int					*fd_pipes;
	int					nb_pipe;
	pid_t				*pid;

	int					heredoc_fds[256];
	int					heredoc_count;

	t_env				*cpy_env;
	t_env				*export;

	t_commands			*command;
	t_token				*token;
	t_in_out			input;
	t_in_out			output;
	t_redir				*redir;
	t_pipes				*pipex;
}						t_data;

struct					s_data_extended
{
	t_data				base;
	t_redir				*redir;
	t_pipes				*pipex;
};

/********************************FUNCTIONS*************************************/
/**************************       0_utils       *******************************/
/*init_env.c*/
void					ft_get_env(char **env, t_data *data);
void					get_shlvl_env(t_data *data);
void					add_cpy_env(char *type, char *value, t_env **env,
							t_data *data);
t_env					*last_value(t_env *env);

/*init.c*/
int						init_data(t_data *data, char **env);
void					init_io(t_data *data);
char					*init_full_path(char **env);

/*signals.c*/
void					signal_handlers(void);
void					reset_signal_handler(t_data *data);
void					child_signal_handler(void);
void					heredoc_signal_handler(void);

/*signals_here_doc.c*/
void					signals_heredoc(void);
void					heredoc_interrupt(int signum);

/*utils.c*/
int						perror_return(char *str);
int						ft_printf_exit_code(char *str, int exit_code);
int						add_new_list_node(t_list **list, t_token *token);
void					ft_lst_addback(t_list *list, t_list *new);

/**************************       1_lexer       *******************************/
/*lexer_main.c*/
int						lexer(t_data *data, int is_new_command);
int						lexer_finalize(t_data *data, t_quote current_quote,
							char **current_token, int is_new_command);
int						lexer_core(t_data *data, t_quote *current_quote,
							char **current_token, int *is_new_command);
char					*append_char(char *str, char c);
int						check_double_tokens(char *str);

/*lexer_define_tokens.c*/
t_type					get_token_type(t_data *data, char symbol,
							int *is_new_command);
int						add_symbol_token(t_data *data, char symbol,
							int *is_new_command);
t_token					*define_arg_type(t_token *token);
t_token					*define_tokens_exit_echo(t_token *token);
char					*resolve_symbol_value(t_data *data, char symbol,
							int *is_new_command, t_type *type);

/*lexer_define_tokens2.c*/
int						create_and_add_symbol_token(t_data *data, char *value,
							t_type type);
t_token					*mark_heredoc_tokens(t_token *token);
t_token					*mark_input_tokens(t_token *token);

/*lexer_quotes.c*/
t_token					*create_and_add_token(t_data *data, char *value,
							int *is_new_command);
int						no_quote(t_data *data, t_quote *current_quote,
							char **current_token, int *is_new_command);
int						double_quote(t_data *data, t_quote *current_quote,
							char **current_token);
int						single_quote(t_data *data, t_quote *current_quote,
							char **current_token);

/*lexer_utils.c*/
int						is_just_spaces(char *arg);
t_token					*init_new_token(t_type type, t_quote quote);
t_token					*new_token(char *start, char *end, t_type type,
							t_quote quote);
char					*extract_token_value(char *start, char *end,
							t_quote quote);
void					lst_token_add_back(t_data *data, t_token *new);

/**************************       2_parser      *******************************/
/******* Expander *******/
/*expander_main.c*/
int						expander(t_data *data);
char					*expan_var(char *str, t_data *data);
char					*process_expansion(char *str, t_data *data, int *i);
char					*process_character(t_data *data, char *str, int *i);
char					*expand_var_or_exit(t_data *data, char *var, int *i);

/*expand_dollars.c*/
int						is_finish_expand(char *str, t_data *data, int count,
							int *i);
char					*expand_dollar_sequence(char **str, int *i,
							t_data *data);
char					*peer_odd_dollar(int dollar_count, char *result,
							char *pid_str, char *temp);
int						dollar_in_str(char *str);

/*expander_utils.c*/
char					*ft_strjoin_char(char *str, char c);
int						is_in_single_quotes(char *str, int index);
int						is_exist_in_env(char *var, t_data *data);
size_t					get_var_len(char *str);

/*expander_more_utils.c*/
void					failed_mess(t_data *data, char *mess, int code);
char					*ft_concatenate(char *before, char *in_var);
char					*extract_var(char *str, int *i);
char					*give_me_inside_var(char *var, t_data *data);
// int						is_in_double_quotes(char *str, int index);

/******* Heredoc ********/
int						populate_here_doc(int write_fd, char *delimiter);
int						here_doc(t_data *data, char *delimiter);

/******** Parser ********/
/*parser_main.c*/
int						open_redirection_fd(t_data *data, t_in_out *redir,
							t_token *token, int oflag);
int						parser_helper_redirections(t_data *data,
							t_token *token);
int						parser_helper_others(t_data *data, t_token *token,
							int *create_new_node);
int						parser(t_data *data);

/*parser_command_concate.c*/
size_t					get_number_of_command_elements(t_commands *node);
int						add_cmd_to_final_group(t_commands *command_ptr,
							size_t *i);
int						add_args_to_final_group(t_commands *command_ptr,
							size_t *i);
int						add_flags_to_final_group(t_commands *command_ptr,
							size_t *i);
int						concate_final_group_commands(t_data *data);

/*parser_utils.c*/
t_commands				*add_new_command_node(t_data *data);
void					ft_commandlst_addback(t_data *data, t_commands *new);
int						comp_value_token(t_data *data, t_token *token);

/*parser_command_populate*/
// int						populate_command(t_data *data, t_token *token);
int						populate_node_command(t_commands *node, t_token *token);
int						populate_node_flag(t_commands *node, t_token *token);
int						populate_node_argument(t_commands *node,
							t_token *token);

/*syntaxe_line.c*/
void					syntaxe_line(char *line, t_data *data);

/**************************      3_executer     *******************************/
/*command_executer.c*/
char					**env_extract_paths(t_env *env);
char					*search_cmd_path(t_data *data, t_commands *cmd);
int						command_executer(t_commands *command, t_data *data);

/*executer_main.c*/
int						cmd_count(t_commands *cmds);
int						executer(t_data *data);

/*fd_manager.c*/
int						close_fd(int *fd);
int						close_unused_fd(int *fd_pipes, int len);
int						finalize_child_processes(pid_t *pid, int num,
							t_data *data, int *fd_pipes);

/*pipeline_execute.c*/
int						execute_builtin(int *fd_pipes, int pos,
							t_commands *command, t_data *data);
int						execute_pipeline(int *fd_pipes, pid_t *pid,
							t_data *data);

/*pipeline_execute2.c*/
int						execute_env(int *fd_pipes, int pos, int *pid,
							t_data *data);

/*pipes_builder.c*/
int						*build_pipes(int fd_out, int fd_in, int cmds_num);

/* env_to_execve */
char					**env_to_tab(t_env *env);

/**************************      4_builtins     *******************************/
/*builtins_utils.c*/
int						command_is_a_builtin(t_commands *node);
int						launch_builtin(t_data *data, t_commands *node,
							t_token *token, int fd);

/*cd.c*/
int						builtin_cd(t_commands *commands, t_data *data);

/*echo.c*/
int						builtin_echo(t_commands *commands, t_data *data);

/*env.c*/
int						builtin_env(t_data *data, t_token *tok, int fd_out);
void					putchar_fd(t_data *data, char *str_err, char c, int fd);
void					putstr_fd(t_data *data, char *str_err, char *s, int fd);

/*exit.c*/
int						builtin_exit(t_commands *command, t_data *data);

/*export.c*/
int						find_key_index(t_data *data, char *key);
int						is_valid_name(char *name);
int						export_with_arg(t_commands *command, t_data *data);
int						builtin_export(t_data *data, t_token *token, int fd);
t_env					*sort_list(t_env *cpy,
							int (*cmp)(const char *, const char *));
/*export_utils.c*/
int						is_valid_name(char *name);
char					*export_key(char *arg);
void					add_env_node(t_data *data, char *value);
void					modif_env_node(t_data *data, char *value, int j);
int						find_if_env_exist(t_env *env, char *value);

/*syntaxe_export.c*/
t_env					*sort_list(t_env *cpy, int (*cmp)(const char *,
								const char *));
int						check_syntax_export(char *value, t_data *data);
void					no_equal_in_export(t_data *data, char *value);
void					modif_export_node(t_data *data, char *value, int exist);
void					modif_export(t_data *data, char *value);

/*get_env_export.c*/
void					get_env_for_export(char **env, t_data *data);
void					get_shlvl_export(t_data *data);
void					add_export(char *type, char *value, t_env **env,
							t_data *data);

/*pwd.c*/
// char					*find_env_value(t_env *env, const char *key);
int						builtin_pwd(t_commands *commands, t_data *data);
char					*find_env_value(t_data *data, const char *key);

/*unset.c*/
int						builtin_unset(t_data *data, t_token *token);

/*************************        5_free       *******************************/
/*free_mem_btw_cmd.c*/
void					free_mem_between_cmd(t_data *data);
void					free_command(t_data *data);
void					free_in_out(t_data *data);
void					free_token(t_data *data);

/*free_utils.c*/
void					free_decomposed_str(char **str1, char **str2,
							char **str3);
void					free_env_list(t_env *list);
void					free_list(t_list *list);
void					free_char_array(char **array);
void					close_fds_recursive(int fd);

/*free_all.c*/
void					free_all_memory(t_data *data);
void					free_env(t_data *data, t_env *env, int cpy);

/**************************        MAIN        ********************************/
void					exit_minishell(t_data *data, int exit_status);

/*************************        6_for_tests       **************************/
/*debug.c*/
void					print_final_group(t_commands *cmd);
const char				*get_type_name(t_type type);
void					print_tokens(t_token *token);

#endif

/*
valgrind --leak-check=full --track-fds=yes --track-origins=yes
--show-leak-kinds=all --trace-children=yes --suppressions=readline.supp
./minishell
*/