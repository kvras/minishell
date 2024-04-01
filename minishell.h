#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
typedef struct s_node
{
	void *value;
	char *type;
	struct s_node *next;
} t_node;
typedef struct s_command
{
    char    **cmd;
    int     input;
    int     output;
    struct s_command   *next;
}           t_command;

//-----------------------------------------------------

t_command *set_newlist(t_node **node);
void handle_space(t_node **node, char ***array, char **s);
void handle_pipe(t_node **node, t_command **cmd, char ***array, int *fd_in, int *fd_out);
void handle_append_or_red_out(t_node **node, int *fd_out, int flag);
void handle_here_doc_or_rd_in(t_node **node, int *fd_in, int flag);
void execute_commands(t_command *cmd, char ***env, t_node **addresses);
void display_cmd(t_command *cmd);
t_command *ft_lstnew_cmd(char **cmd, int input, int output);
void ft_lstadd_back_cmd(t_command **lst, t_command *new);
t_command	*ft_lstlast_cmd(t_command *lst);
char	*ft_join_free(char *s, const char *buf);
char	**ft_pathname(char *p, char **cmdargs, char **env);
int ft_herdoc(char *s);
int make_process(t_command *command, char **env);
char **ft_array(char **array, char *s);
void run_signals();
void ctr_d();
void ctr_c(int sig);
void bach_slash(int sig);
int pipe_parse_error(t_node *node);
char **get_env(char **env);
void exec_export(char *var, char ***env);
void exec_unset(char *s, char ***env);
//-----------------------------------------------------
void exec_echo(char **cmd, char **env);
char	*get_environment(char **envp, char *var);
int exec_pwd();
int exec_cd(char *path);
int is_builtin(t_command *commands, char ***env, t_node **addresses);
int expand(char *var, char **env);
int exec_pwd();
int exec_cd(char *path);
int exec_env(char **env);
void    put_env(t_node **env, char *var, t_node **addresses);
void    unset_env(t_node **env, char *var);
int get_equal(char *s);
int		ft_malloc(size_t size, void **ptr, t_node **addresses);
t_node	*ft_alloc(void **value, char *type);
void	add_back(t_node **lst, t_node *new);
void	free_addresses(t_node *addresses);
t_node  *ft_lstnew1(void *value, char *type, t_node **addresses);
t_node  *ft_lstlast1(t_node *lst);
void	ft_lstadd_back1(t_node **lst, t_node *new);
void    ft_expand(char *line, t_node **commands, int *offset, t_node **addresses);
void    parse_line(char *line, t_node **commands, t_node **addresses, int i);
void    array_to_list(t_node **lst, char **array, t_node **addresses);
int     check_char(char *s,char c);
#endif