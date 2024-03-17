#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_libft/libft.h"

typedef struct s_node
{
	void *value;
	char *type;
	struct s_node *next;
} t_node;

int exec_pwd();
int exec_cd(char *path);
int exec_env(char **env);
int put_env(char *var);
int unset_env(char *var);
int		ft_malloc(size_t size, void **ptr, t_node **addresses);
t_node	*ft_alloc(void *value, char *type);
void	add_back(t_node **lst, t_node *new);
void	free_addresses(t_node *addresses);
t_node  *ft_lstnew1(void *value, char *type, t_node **addresses);
t_node  *ft_lstlast1(t_node *lst);
void	ft_lstadd_back1(t_node **lst, t_node *new);
void    ft_expand(char *line, t_node **commands, int *offset, t_node **addresses);
void    parse_line(char *line, t_node **commands, t_node **addresses);
#endif