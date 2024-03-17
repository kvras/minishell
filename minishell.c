#include "minishell.h"

int special_char(char c)
{
	char *special = " $<>&|;\'\"";
	int i = 0;
	while(special[i])
	{
		if(special[i] == c)
			return 1;
		i++;
	}
	return 0;
}
void ft_expand(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int i;
	int j;
	char *tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	++i;
	while(line[i])
	{
		if(special_char(line[i]))
			break;
		++i;
	}
	tmp = malloc(i + 1);
	if(!tmp)
		return ;
	while(j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "var", addresses));
	free(tmp);
	*offset = *offset + i - 1;
}

void ft_word(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int i;
	int j;
	char *tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	while(line[i])
	{
		if(special_char(line[i]))
			break;
		++i;
	}
	tmp = malloc(i + 1);
	if(!tmp)
		return ;
	while(j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "word", addresses));
	free(tmp);
	*offset = *offset + i - 1;
}
void ft_quotes(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int i;
	int j;
	char *tmp;
	tmp = NULL;
	i = 0;
	j = 0;
	++i;
	while(line[i])
	{
		if(line[0] == line[i])
			break;
		++i;
	}
	tmp = malloc(i + 1);
	if(!tmp)
		return ;
	while(j < i-1)
	{
		tmp[j] = line[j+1];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "quote", addresses));
	free(tmp);
	*offset = *offset + i;
}
int check_quote(char *line, char c,	int *offset)
{
	int i;
	int j;
	int last;
	i = 0;
	j = 0;

	while(line[i])
	{
		if(line[i] == c)
		{
			last = i;
			j++;
		}
		i++;
	}
	if(j % 2 == 0)
	{
		if (offset)
			*offset += last;
		return 1;
	}
	return 0;
}

void parse_line(char *line, t_node **commands, t_node **addresses)
{
	int i;
	i = 0;
	while(line[i])
	{
		if(line[i] == ' ')
			ft_lstadd_back1(commands, ft_lstnew1(" ", "space", addresses));
		else if(line[i] == '$')
			ft_expand(&line[i], commands, &i, addresses);
		else if(line[i] == '<' && line[i + 1] == '<' && ++i)
			ft_lstadd_back1(commands, ft_lstnew1("<<", "her_doc", addresses));
		else if(line[i] == '>' && line[i + 1] == '>' && ++i)
			ft_lstadd_back1(commands, ft_lstnew1(">>", "append", addresses));
		else if(line[i] == '<')
			ft_lstadd_back1(commands, ft_lstnew1("<", "rd_in", addresses));
		else if(line[i] == '>')
			ft_lstadd_back1(commands, ft_lstnew1(">", "rd_out", addresses));
		else if(line[i] == '|')
			ft_lstadd_back1(commands, ft_lstnew1("|", "pipe", addresses));
		else if(line[i] == '\'' && check_quote(&line[i], '\'', NULL) == 1)
			ft_quotes(&line[i], commands, &i, addresses);
		else if(line[i] == '\"' && check_quote(&line[i], '\"', NULL) == 1)
			ft_quotes(&line[i], commands, &i, addresses);
		else
			ft_word(&line[i], commands, &i, addresses);
		if(line[i])
			i++;
	}
}
void f()
{
	system("leaks minishell");
}
int quotes_syntax(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '\'' && check_quote(&line[i], '\'', &i) == 0)
		{
			printf("quote error\n");
			return 0;
		}
		if(line[i] == '\"' && check_quote(&line[i], '\"', &i) == 0)
		{
			printf("quote error\n");
			return 0;
		}
		if(line[i])
			i++;
	}
	return 1;
}
int main(int argc, char **argv, char **env)
{
	char    *line = NULL;
	t_node	*tmp;
	t_node  *commands = NULL;
    t_node  *addresses = NULL;
	atexit(f);
	while(1)
	{
		line = readline("minishell$ ");
		if(!line || strncmp(line, "exit", 4) == 0)
			return (free(line), 0);
		if(quotes_syntax(line) == 0)
			return (free(line), 0);
		if (strncmp(line, "pwd", 3) == 0)
		{
			exec_pwd();
			// return (free(line), 0);
			free(line);
			continue;
		}
		if (strncmp(line, "cd", 2) == 0)
		{
			exec_cd(line + 3);
			//return (free(line), 0);
			free(line);
			continue;
		}
		if (strncmp(line, "env", 3) == 0)
		{
			exec_env(env);
			free(line);
			continue;
		}
		if (strncmp(line, "export", 6) == 0)
		{
			// put_env("saad=hamdouni");
			printf("%d\n",put_env("SAAD=hamdouni"));
			free(line);
			continue;
		}
		if (strncmp(line, "unset", 5) == 0)
		{
			printf("%d\n",unset_env("LESS"));
			free(line);
			continue;
		}
		parse_line(line, &commands, &addresses);
		while(commands)
		{
			tmp = commands;
			commands = commands->next;
			printf("%s   | %s  \n", (char *)tmp->value, tmp->type);
		}
		free_addresses(addresses);
		addresses = NULL;
		commands = NULL;
		free(line);
    }
	return 0;
}
