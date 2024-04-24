/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ayoub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:23:56 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/24 23:21:26 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_parse_error(t_node *node)
{
    t_node *ptr; 

    ptr = node;
    while(ptr && !ft_strncmp(ptr->type, "space", 5))
        ptr = ptr -> next;
    if (ptr && !ft_strncmp(ptr->type, "pipe", 4))
    {
        printf("parse error near `|'\n");
        return 1;
    }
    while (ptr)
    {
        if (ptr && !ft_strncmp(ptr->type, "pipe", 4))
        {
            ptr = ptr -> next;
            while(ptr && !ft_strncmp(ptr->type, "space", 5))
                ptr = ptr -> next;
            if(!ptr || !ft_strncmp(ptr->type, "pipe", 4))
            {
                printf("parse error near `|'\n");
                return 1;
            }
        }
        if(ptr)
            ptr = ptr -> next;
    }
    return 0;
}

void display_cmd(t_command *node)
{
    int i;
    while(node)
    {   
        printf("input : %d\n", node->input);
        printf("output : %d\n", node->output);
        printf("cmd : [");
        i = 0;
        while(node && node->cmd && node->cmd[i])
        {
            printf("%s,", node->cmd[i]);
            i++;
        }
        printf("]\n");
        printf("\n");
        node = node->next;
    }
}
t_command *set_newlist(t_node **node, t_env *env, t_node **addresses)
{
    t_command *cmd = NULL;
    char *s = NULL;
    char **array = NULL;
    int flag = 0;
    t_fd fd;
    fd.out = 1;
    fd.in = 0;

    if(pipe_parse_error(*node))
        return NULL;
    while (*node) 
    {
        handle_space(node, &array, &s, addresses);
        handle_pipe(node, &cmd, &array, &fd, addresses);
        handle_append_or_red_out(node, &fd.out, flag);
        handle_here_doc_or_rd_in(node, &fd.in, flag, addresses);
        if(*node && (!ft_strncmp((*node)->type, "pipe", 4) || !ft_strncmp((*node)->type, "space", 5)))
            continue ;
        if(*node)
        {
            expand(*node, env, addresses);
            s = ft_strjoin(s, (*node)->value, addresses);
            *node = (*node)->next;
        }
    }
    array = ft_array(array, s, addresses);
    if(array && *array)
        ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array, fd.in, fd.out, addresses));
    // printf("-------------commands------------\n");
    // display_cmd(cmd);
    // printf("-------------fin commands-------------\n");
    return cmd;
}

void handle_space(t_node **node, char ***array, char **s, t_node **addresses)
{
      if(!*node)
        return ;
    if (!ft_strncmp((*node)->type, "space", 5))
    {
        *array = ft_array(*array, *s, addresses);
        *s = NULL;
        *node = (*node)->next;
    }
    else if (!ft_strncmp((*node)->type, "pipe", 4))
    {
        *array = ft_array(*array, *s, addresses);
        *s = NULL;
    }
}

void handle_pipe(t_node **node, t_command **cmd, char ***array, t_fd *fd, t_node **addresses)
{
    t_command *response;
    if(!*node)
        return ;
    if (!ft_strncmp((*node)->type, "pipe", 4)) 
    {
        if (*array && **array) 
        {
            response = ft_lstnew_cmd(*array, fd->in, fd->out, addresses);
            ft_lstadd_back_cmd(cmd, response);
            *array = NULL;
            fd->out = 1;
            fd->in = 0;
        }
        *node = (*node)->next;
    }
}

void handle_append_or_red_out(t_node **node, int *fd_out, int flag) 
{
      if(!*node)
        return ;
    if (!ft_strncmp((*node)->type, "append", 6) || !ft_strncmp((*node)->type, "rd_out", 6)) 
    {
        flag = 0;
        if (!ft_strncmp((*node)->type, "append", 6))
            flag = 1;
        *node = (*node)->next;
        while (*node && !ft_strncmp((*node)->type, "space", 5))
            *node = (*node)->next;
        if (*node && (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type, "quote", 5))) 
        {
            if (flag)
                *fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
            else
                *fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            *node = (*node)->next;
        } 
        else
            perror("");
    }
}

void handle_here_doc_or_rd_in(t_node **node, int *fd_in, int flag, t_node **addresses)
{
    if(!*node)
        return ;
    if (!ft_strncmp((*node)->type, "here_doc", 8) || !ft_strncmp((*node)->type, "rd_in", 5)) 
    {
        flag = 0;
        if (!ft_strncmp((*node)->type, "rd_in", 5))
            flag = 1;
        *node = (*node)->next;
        if (!*node)
        {
            write(1, "syntax error near unexpected token `newline'\n", 45);
            return ;
        }
        while (!ft_strncmp((*node)->type, "space", 5))
            *node = (*node)->next;
        if (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type, "quote", 5)) 
        {
            if (flag)
                *fd_in = open((*node)->value, O_RDONLY, 0644);
            else
                *fd_in = ft_herdoc((*node)->value, addresses);
            *node = (*node)->next;
        }
        else
            perror("");
    }
}

// builtin_key is a function that checks if the command is a builtin command 
int builtin_key(t_command *cmd)
{
    if(!ft_strcmp(cmd->cmd[0], "cd") || !ft_strcmp(cmd->cmd[0], "echo") || !ft_strcmp(cmd->cmd[0], "pwd") ||
        !ft_strcmp(cmd->cmd[0], "export") || !ft_strcmp(cmd->cmd[0], "unset") || !ft_strcmp(cmd->cmd[0], "env") ||
         !ft_strcmp(cmd->cmd[0], "exit") || cmd->cmd[0][0] == '$')
        return 1;
    return 0;
}

void execute_commands(t_command *cmd, t_env *env, t_node **addresses)
{
    t_command *tmp;
    char *path;
    int i = 0;
    tmp= cmd;
    path = get_environment(env->env, "PATH=");
    while(cmd) 
    {
        if(!builtin_key(cmd))
            cmd->cmd = ft_pathname(path, cmd->cmd, env->env, addresses);
        if(i == 0 && !cmd->next && is_builtin(cmd, env, addresses))
            return ;
        make_process(cmd, env, addresses);
        cmd = cmd->next;
        i++;
    }
    while(wait(NULL)>0);
}
int make_process(t_command *command, t_env *env, t_node **addresses)
{
    int fd[2];
    int pid;
    int response = -1;
    if(!command->cmd)
        return 0;
    if(command->next)
    {
        if(pipe(fd) == -1)
            perror("Error creating pipe");
    }
    pid = fork();
    if(pid == -1)
        perror("Error forking");
    if(pid == 0)
    {
        dup2(command->input, 0);
        if(command->input != 0)
            close(command->input);
        if(command->next && command->output == 1)
        {
            dup2(fd[1], 1);
            close(fd[1]);
        }
        else if(command->output != 1)
        {
            dup2(command->output, 1);
            close(command->output);
        }
        if(!is_builtin(command, env, addresses) && command->cmd[0][0] != '\0')
        {
            response = execve(command->cmd[0], command->cmd,env->env);
            if (response == -1)
            {
                printf("minishell: %s: %s\n", command->cmd[0], strerror(errno));
                exit(127);
            }
        }
        if(response == -1)
            exit(127);
    }
    else
    {
        close(fd[1]);
        command = command->next;
        if(command)
            command->input = fd[0];
        else
            close(fd[0]);
    }
    return 0;
}

int ft_herdoc(char *s, t_node **addresses)
{
    int fd[2];
    char *line;
    char *tmp;
    pipe(fd);
    while(1)
    {
        line = readline("heredoc> ");
        if(!line)
            break;
        if(!ft_strncmp(line, s, ft_strlen(s)) && ft_strlen(line) == ft_strlen(s))
        {
            free(line);
            break;
        }
        tmp = ft_strjoin(line, "\n", addresses);
        write(fd[1], tmp, ft_strlen(tmp));
        free(line);
    }
    close(fd[1]);
    return (fd[0]);
}
char	*get_environment(char **envp, char *var)
{
	int		i;
	char	*response;

	response = NULL;
	i = 0;
	while (envp && envp[i])
	{
		response = ft_strnstr(envp[i], var, ft_strlen(var));
		if (response)
            return response + ft_strlen(var);
		i++;
	}
	return (NULL);
}
char	**ft_pathname(char *p, char **cmdargs, char **env, t_node **addresses)
{
	int		i;
	char	*cmd;
    char    **paths;

    paths = ft_split(p, ':', addresses);
    if(!paths)
        return (cmdargs);
    if(!cmdargs || !*cmdargs)
        return ( NULL);
	i = -1;
    if(cmdargs[0][0] == '/' || cmdargs[0][0] == '.')
        return (cmdargs);
	while (paths && paths[++i] && cmdargs[0][0])
	{
		cmd = ft_join_free(paths[i], "/", addresses);
		cmd = ft_join_free(cmd, cmdargs[0], addresses);
		if (access(cmd, F_OK | X_OK) == 0)
        {
            cmdargs[0] = cmd;
            return (cmdargs);
        }
	}
	return (cmdargs);
}
char	*ft_join_free(char *s, const char *buf, t_node **addresses)
{
	char	*r;

	r = ft_strjoin(s, buf, addresses);
	return (r);
}
t_command	*ft_lstnew_cmd(char **cmd, int input, int output, t_node **addresses)
{
	t_command	*ptr;

    ptr = ft_malloc(sizeof(t_command), addresses);
	if (!ptr)
		return (NULL);
	ptr->cmd = cmd;
	ptr->input = input;
	ptr->output = output;
	ptr -> next = NULL;
	return (ptr);
}

t_command	*ft_lstlast_cmd(t_command *lst)
{
	t_command	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back_cmd(t_command **lst, t_command *new)
{
	t_command	*ptr;

	if (!lst || !new)
		return ;
	ptr = *lst;
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr = ft_lstlast_cmd(*lst);
		ptr -> next = new;
	}
}
char **ft_array(char **array, char *s, t_node **addresses)
{
    char **new;
    int i;
    int j;

    i = 0;
    j = 0;
    if (!array)
    {
        new = ft_malloc(sizeof(char *) * 2, addresses);
        if (!new)
            return NULL;
        new[0] = s;
        new[1] = NULL;
        return new;
    }
    else
    {
        while (array[i])
            i++;
        new = ft_malloc(sizeof(char *) * (i + 2), addresses);
        if (!new)
            return NULL;
    }
    while (array[j])
    {
        new[j] = array[j];
        j++;
    }
    new[j] = s;
    new[j + 1] = NULL;
    return new;
}