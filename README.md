![Minishell logo](.media/minishell_logo.png)

![Grade badge](https://img.shields.io/badge/101_%2F_100-004d40?label=final%20grade&labelColor=151515&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIGhlaWdodD0iMjRweCIgdmlld0JveD0iMCAwIDI0IDI0IiB3aWR0aD0iMjRweCIgZmlsbD0iI0ZGRkZGRiI+PHBhdGggZD0iTTAgMGgyNHYyNEgweiIgZmlsbD0ibm9uZSIvPjxwYXRoIGQ9Ik0xMiAxNy4yN0wxOC4xOCAyMWwtMS42NC03LjAzTDIyIDkuMjRsLTcuMTktLjYxTDEyIDIgOS4xOSA4LjYzIDIgOS4yNGw1LjQ2IDQuNzNMNS44MiAyMXoiLz48L3N2Zz4=) ![Language Badge](https://img.shields.io/badge/C-fe428e?logo=C&label=language&labelColor=151515) ![Norminette Badge](https://img.shields.io/badge/passing-brightgreen?logo=42&label=norminette&labelColor=151515)![Library Badge](https://img.shields.io/badge/our_own_libft-004d40?logo=GitHub&label=library%20used&labelColor=151515)

# Minishell 👩🏼‍💻

Ce projet, développé dans le cadre de la formation à l'École 42, consiste en la création d'un shell simplifié en langage C, inspiré des fonctionnalités de Bash. L'objectif est de comprendre et d'implémenter les mécanismes fondamentaux d'un interpréteur de commandes Unix, en manipulant les processus, les redirections, les pipes et les signaux.

Objectifs
Le projet Minishell permet de renforcer les compétences en programmation système en abordant des concepts avancés comme :

- La gestion des processus : exécuter des commandes et manipuler les processus enfants.
- La redirection des entrées/sorties (I/O) : permettre les redirections standard >, >>, < et <<.
- La gestion des pipes (|) : enchaîner des commandes avec une communication entre elles.
- Les signaux : gérer l'interruption du programme avec des signaux comme Ctrl+C, Ctrl+D, etc.

Voici le [sujet](.media/en.subject.pdf).

# Télécharge et test ⬇️

Clone le projet.

```
git clone https://github.com/ugozchi/42_Minishell.git
cd 42_Minishell
```

<br>

## Options possibles ⚙️

Ici, vous pouvez utiliser les options classiques d'un Makefile (options ci-dessous) mais aussi l'option bonus qui vous permettra d'ajouter vos fonctions bonus dans votre fichier archive libft.a si vous les avez fait.  
Toute cette partie correspond à ce que l'on doit rendre pour ce faire corriger.

<br>

| Option | Description |
| --- | --- |
| `make` | Créer un fichier archive libftpritnf.a avec tous les fichiers |
| `make clean` | Supprime le dossier contenant les fichiers objets ```.o```|
| `make fclean` | Execute `clean` puis supprime le fichier archive ```.a```|
| `make re` | Execute `fclean` puis `make` |

<br>

## Explication de la structure 🏰
Minishell est construit autour de plusieurs modules principaux qui interagissent pour exécuter les commandes de l'utilisateur. Voici un aperçu des principales structures et fichiers :

### 1) Gestion des entrées et parsing

  - `lexer.c` : Analyse la ligne de commande saisie par l'utilisateur et la découpe en tokens (arguments, redirections, opérateurs...)

  - `parser.c` : Organise les tokens en une structure syntaxique exploitable, prenant en compte les priorités des opérateurs.

  - `expander.c` : Gère les variables d'environnement ($HOME, $USER...), l'expansion des jokers (*), et les substitutions.

<br>

### 2) Gestion des processus et exécution

  - `executor.c` : Exécute les commandes en tenant compte des redirections et des pipes.

  - `builtin.c` : Implémente les commandes internes comme cd, echo, exit, env, unset...

  - `redirect.c` : Gère les redirections (>, >>, <, <<) et assigne les descripteurs de fichier appropriés.

  - `pipe.c` : Gère la communication entre plusieurs processus en enchaînant des commandes via |.

<br>

### 3) Gestion des signaux

  - `signals.c` : Capture et gère les signaux système comme CTRL+C, CTRL+Z, CTRL+D pour permettre un comportement interactif du shell.

  - `handler.c` : Définit le comportement du shell face aux interruptions utilisateur.

<br>

### 4) Gestion de l'environnement et mémoire

  - `env.c` : Gère la liste des variables d'environnement et leur modification avec export et unset.

  - `memory.c` : Assure la libération correcte de la mémoire pour éviter les fuites (free_all, clear_tokens...).

<br>

## Organisation du code 🔧

### 1️⃣ Initialisation et Gestion de l'Environnement

  - `init_env.c` : Charge les variables d'environnement et ajuste SHLVL.

  - `init.c` : Initialise t_data, stocke les chemins d'exécution et configure les entrées/sorties.

  - `get_env_export.c` : Récupère les variables d'environnement pour export et les ajuste si nécessaire.

<br>

### 2️⃣ Analyse Lexicale et Parsing

  - `lexer_main.c` : Analyse la ligne de commande en tokens exploitables.

  - `lexer_define_tokens.c` : Identifie le type des tokens (commandes, arguments, redirections, etc.).

  - `lexer_quotes.c` : Gère les guillemets pour éviter les erreurs de parsing.

  - `expander_main.c` : Gère l'expansion des variables ($USER, $PWD) et le remplacement des valeurs.

  - `parser_main.c` : Organise les tokens en une structure syntaxique permettant l'exécution correcte.

  - `parser_command_populate.c` : Associe les arguments et flags aux commandes.

<br>

### 3️⃣ Gestion des Redirections et Pipes

  - `redirect.c` : Gère les redirections (>, >>, <, <<) en ouvrant et fermant les fichiers nécessaires.

  - `pipes_builder.c` : Crée et gère les pipes pour la communication entre processus.

  - `pipeline_execute.c` : Exécute les commandes enchaînées avec | et redirige les entrées/sorties.

<br>

### 4️⃣ Exécution des Commandes

  - `executer_main.c` : Coordonne l'exécution des commandes internes et externes.

  - `command_executer.c` : Recherche le chemin des commandes et les exécute avec execve.

  - `fd_manager.c` : Gère l'ouverture et la fermeture des fichiers lors de l'exécution.

<br>

### 5️⃣ Gestion des Signaux et du Contrôle du Shell

  - `signals.c` : Capture CTRL+C, CTRL+Z, CTRL+D et ajuste le comportement du shell.

  - `signals_here_doc.c` : Gère les interruptions pour heredoc.

<br>

### 6️⃣ Implémentation des Builtins

  - `builtin.c` : Contient les commandes internes (cd, exit, env, unset, export,..).

  - `echo.c` : Gère l'affichage de chaînes avec l'option -n.

  - `cd.c` : Implémente la navigation dans les répertoires avec chdir().

  - `export.c` et unset.c : Modifient les variables d'environnement.

<br>

### 7️⃣ Nettoyage et Libération de Mémoire

  - `free_mem_btw_cmd.c` : Nettoie la mémoire entre chaque commande pour éviter les fuites.

  - `free_all.c` : Libère toutes les ressources utilisées par le shell avant de quitter.

<br>

## Note Final et Commentaires 📔

<br>

| |
| --- |
| ![](.media/note.png) |


| | |
| --- | --- |
| Correcteur 1 | <img src=".media/com1.png" /> |
| Correcteur 2 | <img src=".media/com2.png" /> |
| Correcteur 3 | <img src=".media/com3.png" /> |
