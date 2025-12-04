/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtumanya <mtumanya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:34:10 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 14:46:15 by mtumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, getenv, exit
# include <unistd.h>     // write, access, read, close,
//fork, dup, dup2, isatty, ttyname, ttyslot, getcwd, chdir
# include <sys/types.h>  // opendir, readdir, wait, waitpid,
//wait3, wait4, stat, lstat, fstat, kill, signal related
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <sys/stat.h>   // stat, lstat, fstat
# include <fcntl.h>      // open, unlink
# include <dirent.h>     // opendir, readdir, closedir
# include <string.h>     // strerror
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
# include <termios.h>    // tcsetattr, tcgetattr
# include <termcap.h>    // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>  // ioctl
# include <readline/readline.h>   // readline, rl_clear_history,
//rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>    // add_history
# include <errno.h>

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef enum e_data
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	T_REDIR_IN,
}			t_data;

typedef struct s_rsub
{
	char			*op;
	char			*arg;
	struct s_rsub	*next;
}			t_rsub;

typedef struct s_exec
{
	char			*cmd;
	char			*cmd2;
	char			*token;
	int				heredoc_fd;
	int				has_infile;
	int				has_outfile;
	struct s_exec	*next;
	t_rsub			*subs;
}			t_exec;

typedef struct s_shell
{
	char			*home;
	t_env			*t_env;
	char			*input;
	char			**tokens;
	int				tok_count;
	int				pipe_count;
	int				heredocs;
	int				redirs;
	int				stdin_backup;
	int				stdout_backup;
	t_exec			*cmds;
}			t_shell;

typedef struct s_vars
{
	int		(*pfd)[2];
	pid_t	*pids;
	int		infile;
	int		outfile;
	char	*path;
	char	**cmd;
}	t_vars;

//for expand.c
typedef struct s_exp
{
	char	*in;
	char	*out;
	size_t	i;
	size_t	j;
	size_t	cap;
	int		sq;
	int		dq;
	t_shell	*sh;
}	t_exp;

typedef struct s_cd
{
	char	*path;
	int		ccmd;
	char	*a;
	char	*oldpwd;
	char	**export_dot;
	char	*pwd_value;
	char	*tmp;
}	t_cd;

// frees.c
void	ft_free(char **arg);
void	ft_exit_perror(const char *msg);
void	ft_free_execs(t_exec *cmds);
void	free_env(t_env *env);

// init.c
void	init_shell(t_shell *shell);
void	reinit(t_shell **shell);
void	init_env(t_shell *shell, char **envp);

// signals.c
void	set_signals(void);
void	sigint_heredoc(int sig);
void	sigint_during_wait(int sig);
void	handling_signal(int signal);

// check.c
int		has_open_quote(const char *s);
int		syntax_error(t_shell *sh, int i);

// token.c
int		token(t_shell *sh, int i, int j);

// redirections.c
int		handle_redirection(t_exec *data);
int		redir_output(char *file, char *type, t_exec *cmds);

// splits.c
t_exec	*split_by_pipe(t_shell *sh, int i, t_exec *head, t_exec *cur);

// splits_2.c
t_rsub	*new_sub(char *op, char *arg);
int		is_redir_tok(char *s);
int		is_pipe_tok(char *s);
t_exec	*new_exec_node(void);
int		extract_cmd_from_cmd2(t_exec *cur, int i);

// find_path.c
int		find_path(t_env *env, char ***path);
char	*find_cmd(char *command, t_env *env, int i, char *tmp);

// minishell.c
void	redirections_execve(t_exec *cmds, t_vars *vars, int i, t_shell *sh);
int		start(t_shell *sh, int status);

// expend.c
char	*expand_vars(char *input, t_shell *shell, int cas);
char	*get_env_value(char *name, t_shell *shell);

// expend_2.c
size_t	parse_var_name(const char *s, size_t *is_qmark);
int		buf_grow(t_exp *e, size_t extra);
int		copy_heredoc(t_exp *e, char q);
int		handle_quote(t_exp *e);

// utils.c
int		is_operator(const char *s, int *len, t_data *type);
void	print_error(const char *arg, const char *msg);
void	restore_std(t_shell *sh);
char	*ft_join(char *a, char *b, char *c);
char	**env_list_to_array(t_env *env, int count);

// heredoc.c
void	herdoc_handle(t_shell *sh, t_exec **data, int count, int drosh);
char	*strip_quotes(char *s);
void	append_heredoc_extra(t_exec *cur,
			char **tmp, t_shell *sh, int drosh);

// builtins.c
int		ft_cd(t_shell *sh, char **cmd);
int		ft_unset(t_shell *sh, char **args);
int		ft_env(t_shell *sh, char **env);
int		is_builtin(char *cmd);
int		exec_builtin(t_shell *sh, char **cmd, t_exec *cmds, int state);

// exit.c
int		ft_exit(char **argv, t_shell *shell);

// unset.c
int		ft_unset(t_shell *sh, char **cmd);

// cd.c
int		ft_cd(t_shell *sh, char **cmd);
int		cmd_count(char **cmd);

// echo.c
int		is_n_e(char *str);
int		ft_echo(char **cmd, t_exec *cmds);

// export.c
int		ft_export(t_shell *sh, char **cmd, int state);
void	ft_print_export(t_shell *sh);
int		export_one(t_shell *sh, char *arg, char *val);

// env.c
int		ft_env(t_shell *sh, char **cmd);

// pwd.c
int		ft_pwd(t_shell *sh);

#endif
