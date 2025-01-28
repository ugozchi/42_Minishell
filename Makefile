# ###############################################################################
# #                        MAKEFILE POUR MINISHELL                             #
# ###############################################################################

# # Compiler targets and libraries
# NAME        = minishell
# CC          = cc

# CFLAGS      = -Wall -Werror -Wextra -g -MMD -MP  -fsanitize=address

# READLINE_DIR= $(shell brew --prefix readline)
# # On ajoute au CFLAGS la recherche de headers pour readline
# CFLAGS     += -I$(READLINE_DIR)/include
# # Idem pour LDFLAGS => recherche de la lib dans $(READLINE_DIR)/lib
# LDFLAGS    += -L$(READLINE_DIR)/lib
# # Lire la lib
# READLINE    = -lreadline -lcurses

# # Directories
# SRC_DIR     = ./sources/
# HEAD_DIR    = ./includes/
# LIBFT_DIR   = ./libft/
# OBJ_DIR     = ./objects/

# # Sources
# SRC         =   main.c \
#                 0_utils/init_env.c \
#                 0_utils/init.c \
#                 0_utils/signals_here_doc.c \
#                 0_utils/signals.c \
#                 0_utils/utils.c \
#                 1_lexer/lexer_define_tokens.c \
# 				1_lexer/lexer_main.c \
# 				1_lexer/lexer_quotes.c \
#                 1_lexer/lexer_utils.c \
#                 2_parser/expander/expander_main.c \
#                 2_parser/expander/expander_utils.c \
# 				2_parser/expander/expander_dollars.c \
# 				2_parser/expander/expander_more_utils.c \
#                 2_parser/heredoc/here_doc.c \
#                 2_parser/parser/parser_main.c \
#                 2_parser/parser/parser_utils.c \
#                 2_parser/parser/parser_command_concate.c \
#                 2_parser/parser/parser_command_populate.c \
# 				2_parser/parser/syntaxe_line.c \
#                 3_executer/command_executer.c \
#                 3_executer/executer_main.c \
#                 3_executer/fd_manager.c \
#                 3_executer/pipeline_execute.c \
#                 3_executer/pipes_builder.c \
#                 4_builtins/builtins_utils.c \
#                 4_builtins/cd.c \
#                 4_builtins/echo.c \
#                 4_builtins/env.c \
#                 4_builtins/exit.c \
#                 4_builtins/export_utils.c \
#                 4_builtins/export.c \
# 				4_builtins/get_env_export.c \
#                 4_builtins/pwd.c \
# 				4_builtins/syntaxe_export.c \
#                 4_builtins/unset.c \
#                 5_free/free_all.c \
#                 5_free/free_mem_btw_cmd.c \
#                 5_free/free_utils.c \
#                 6_tests/here_doc_tests.c \
#                 6_tests/lexer_tests.c \
#                 6_tests/parser_tester.c

# SRCS        = $(addprefix $(SRC_DIR), $(SRC))
# SRC_NB      = $(words $(SRCS))

# LIBFT       = libft.a

# # Objects
# OBJS        = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# # Couleurs, symboles et utils...
# RESET       = \033[0m
# CYAN        = \033[1;36m
# YELLOW      = \033[1;33m
# ROSE        = \033[38;5;216m
# BOLD        = \033[1m
# INFO        = ⓘ
# OK          = ✓

# ###############################################################################
# #                               REGLES PRINCIPALES                            #
# ###############################################################################

# all: project_logo $(OBJ_DIR)
# 	@make -s $(LIBFT)
# 	@make -s $(NAME)

# $(LIBFT):
# 	@echo "$(CYAN)\nCOMPILING $$(echo $(LIBFT) | tr '[:lower:]' '[:upper:]')$(RESET)"
# 	make -C $(LIBFT_DIR)

# $(NAME): entry_message $(OBJS)
# 	@$(CC) $(CFLAGS) $(OBJS) -I$(HEAD_DIR) $(LDFLAGS) $(READLINE) \
# 		$(LIBFT_DIR)$(LIBFT) -o $(NAME)
# 	@echo "$(YELLOW)\nCompilation complete, $(NAME) executable at the root of the directory$(RESET)\n"

# ###############################################################################
# #                               REGLES D'OBJETS                               #
# ###############################################################################

# $(OBJ_DIR):
# 	@if [ ! -d "$(OBJ_DIR)" ]; then \
# 		mkdir -p "$(OBJ_DIR)"; \
# 	fi

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -I$(HEAD_DIR) -c $< -o $@
# 	@echo "Compiled $<"

# ###############################################################################
# #                                 REGLES CLEAN                                 #
# ###############################################################################
# clean:
# 	@make -sC $(LIBFT_DIR) clean >/dev/null 2>&1
# 	@if [ ! -d "$(OBJ_DIR)" ]; then \
# 		echo "$(YELLOW)$(INFO) Repo .o already clean$(RESET)"; \
# 	else \
# 		echo "$(RED)Removing all .o files$(RESET)"; \
# 		rm -r $(OBJ_DIR); \
# 	fi

# fclean: clean
# 	@make -sC $(LIBFT_DIR) fclean >/dev/null 2>&1
# 	@if [ -f "$(NAME)" ] || [ -f "$(LIBFT)" ]; then \
# 		echo "$(RED)Removing $(NAME) and $(LIBFT) files from root$(RESET)"; \
# 		rm -f $(NAME) $(LIBFT); \
# 	else \
# 		echo "$(YELLOW)$(INFO) $(NAME) and $(LIBFT) already removed$(RESET)"; \
# 	fi

# re: fclean all

# ###############################################################################
# #                       AFFICHAGE (LOGO + MESSAGES)                            #
# ###############################################################################
# project_logo:
# 	@echo "																						   "
# 	@echo "$(ROSE)   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗        $(RESET)"
# 	@echo "$(ROSE)   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║        $(RESET)"
# 	@echo "$(ROSE)   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║        $(RESET)"
# 	@echo "$(ROSE)   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        $(RESET)"
# 	@echo "$(ROSE)   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗   $(RESET)"
# 	@echo "$(ROSE)   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   $(RESET)"
# 	@echo "			a 42 Project by MOTYLEWSKI Melina & ZANCHI Ugo								   "

# entry_message:
# 	@echo "$(CYAN)\nCOMPILING $$(echo $(NAME) | tr '[:lower:]' '[:upper:]')\n$(RESET)$(BOLD)Compiling necessary .o files out of $(SRC_NB).c files in total$(RESET)"

# ###############################################################################
# #                             PHONY TARGETS                                    #
# ###############################################################################
# .PHONY: all clean fclean re project_logo entry_message

# # Inclusion des dépendances auto-générées
# -include $(OBJ_DIR)/*.d



###############################################################################
#                                  LINUX                                      #
###############################################################################

# Compiler targets and libraries
NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g3 -MMD -MP
LIBFT		=	libft.a
READLINE	=	-lreadline

# Directories
SRC_DIR		=	./sources/
OBJ_DIR		=	.o/
HEAD_DIR	=	./includes/
LIBFT_DIR	=	./libft/

# Colours, symbols and utils
RESET	=	\033[0m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
CYAN	=	\033[1;36m
RED		=	\033[0;31m
ROSE	=	\033[38;5;216m
BOLD	=	\033[1m

# Symbols
OK		=	✓
INFO	=	ⓘ

# Sources
SRC         =   main.c \
                0_utils/init_env.c \
                0_utils/init.c \
                0_utils/signals_here_doc.c \
				0_utils/signal_child.c \
                0_utils/signals.c \
                0_utils/utils.c \
                1_lexer/lexer_define_tokens.c \
                1_lexer/lexer_define_tokens2.c \
				1_lexer/lexer_main.c \
				1_lexer/lexer_quotes.c \
                1_lexer/lexer_utils.c \
                2_parser/expander/expander_main.c \
                2_parser/expander/expander_utils.c \
				2_parser/expander/expander_dollars.c \
				2_parser/expander/expander_more_utils.c \
                2_parser/heredoc/here_doc.c \
                2_parser/parser/parser_main.c \
                2_parser/parser/parser_utils.c \
                2_parser/parser/parser_command_concate.c \
                2_parser/parser/parser_command_populate.c \
				2_parser/parser/syntaxe_line.c \
                3_executer/command_executer.c \
                3_executer/executer_main.c \
                3_executer/fd_manager.c \
                3_executer/pipeline_execute.c \
				3_executer/pipeline_execute2.c \
                3_executer/pipes_builder.c \
				3_executer/env_to_execve.c \
                4_builtins/builtins_utils.c \
                4_builtins/cd.c \
                4_builtins/echo.c \
                4_builtins/env.c \
                4_builtins/exit.c \
                4_builtins/export_utils.c \
                4_builtins/export.c \
				4_builtins/get_env_export.c \
                4_builtins/pwd.c \
				4_builtins/syntaxe_export.c \
                4_builtins/unset.c \
                5_free/free_all.c \
                5_free/free_mem_btw_cmd.c \
                5_free/free_utils.c \
				6_for_tests/debug.c 

SRCS		=	$(addprefix ${SRC_DIR}, ${SRC})
OBJS		=	$(addprefix ${OBJ_DIR}, $(SRC:.c=.o))
DEPS		=	$(OBJS:.o=.d)

# Rules
all:		project_logo ${OBJ_DIR} ${LIBFT} ${NAME}

# Create the object directory
${OBJ_DIR}:
	@mkdir -p ${OBJ_DIR}
	@echo "${CYAN}Created object directory: ${OBJ_DIR}${RESET}"

# Compile libft
${LIBFT}:
	@echo "${CYAN}\nCOMPILING $$(echo ${LIBFT} | tr '[:lower:]' '[:upper:]')${RESET}"
	@make -C ${LIBFT_DIR}

# Compile Minishell
${NAME}: ${LIBFT} ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -I${HEAD_DIR} ${LIBFT_DIR}${LIBFT} ${READLINE} -o ${NAME}
	@echo "${YELLOW}${NAME} successfully compiled${RESET}"

# Rule to compile .c files into .o files
${OBJ_DIR}%.o: ${SRC_DIR}%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -I${HEAD_DIR} -c $< -o $@
	@echo "${GREEN}Compiled $< to $@${RESET}"

# Clean rules
clean:
	@make -C ${LIBFT_DIR} clean
	@rm -rf ${OBJ_DIR}
	@echo "${GREEN}Cleaned object files${RESET}"

fclean: clean
	@make -C ${LIBFT_DIR} fclean
	@rm -f ${NAME}
	@echo "${RED}Removed ${NAME} executable${RESET}"

re: fclean all

# Project logo
project_logo:
	@echo "																						   "
	@echo "${ROSE}   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗        ${RESET}"
	@echo "${ROSE}   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║        ${RESET}"
	@echo "${ROSE}   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║        ${RESET}"
	@echo "${ROSE}   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        ${RESET}"
	@echo "${ROSE}   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗   ${RESET}"
	@echo "${ROSE}   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   ${RESET}"
	@echo "			a 42 Project by MOTYLEWSKI Melina & ZANCHI Ugo								   "

# Include dependency files
-include $(DEPS)

.PHONY: all clean fclean re project_logo