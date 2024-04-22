#include "minishell.h"

int	ft_strcmp(const char *s1,const char *s2)
{
	int i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// char **get_env(char **env)
// {
//     int i = 0;
//     char **array;

//     while(env[i])
//         i++;
//     array = (char **)malloc((sizeof(char *) * (i + 1)));
//     if(!array)
//         return NULL;
//     i = 0;
//     while(env && env[i])
//     {
//         array[i] = ft_strdup(env[i]);
//         i++;
//     }
//     array[i] = NULL;
//     return (array);
// }

void swap(char **a, char **b)
{   
    char *c;
    c = *a;
    *a = *b;
    *b = c;
}

void sort_env(char **env)
{
    int i;
    int j;

    i = 0;
    while(env && env[i])
    {
        j = i + 1;
        while(env[j])
        {
            if(ft_strcmp(env[i], env[j]) > 0) // ft_strcmp
                swap(&env[i], &env[j]);
            j++;   
        }
        i++;
    }
}

// int exec_env(char **env)
// {
//     int i;

//     i = 0;
//     while(env && env[i])
//     {
//         ft_putstr_fd(env[i], 1);
//         ft_putstr_fd("\n", 1);
//         i++;
//     }
//     return 0;
// }
int exec_env(char **env)
{
    int i;
    int j;
    
    i = 0;
    while(env && env[i])
    {
        j = 0;
        while(env[i][j])
        {
            if(env[i][j] == '+' && env[i][j + 1] == '=')
                j++;
            write(1, &env[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
    return 0;
}
void	export_print(char **export_env)
{
    // if(!export_env || !*export_env)
        // return ; 
    int i;
    
	sort_env(export_env);
	while (export_env && *export_env)
	{
        i = 0;
		ft_putstr_fd("declare -x ", 1);
            
        while((*export_env)[i])
        {
            if ((*export_env)[i]== '+' && (*export_env)[i + 1] == '=')
                i++;
            write(1, &(*export_env)[i], 1);
            if ((*export_env)[i] == '=' && (*export_env)[i - 1] != '=')
                write(1, "\"", 1);
            i++;
        }
        if(check_char(*export_env, '+') && !get_equal(*export_env))
            write(1, "=\"", 2);
        if(get_equal(*export_env))
            write(1, "\"", 1);
		write(1,"\n", 1);
		export_env++;
	}
}

int check_error(char *var)
{
    int i = 0;
    int j;
    int size;
    
    if(var[i] == '_')
        i++;
    j = i;
    if(!ft_isalpha(var[i]))
        return (0);
    size = get_equal(var);
    while(var[i] && (size == 0))
    {
        if(var[i]!='_')
            if (!ft_isalnum(var[i]))
                return (0);
        i++;
    }
    i += j;
    while(i < size)
    {
        if(var[i] != '_')
        {
            if(var[i] == '+' && var[i + 1])
            {
                i++;
                if(var[i] == '=')
                    break;
            else 
                return (0);
             }
        if (!ft_isalnum(var[i]))
            return (0);
        }
        i++;
    }
    // printf("%s\n", var);
    return (1);
}

int get_best_size(char *var)
{
    int j = 0;
    int size = get_equal(var);
    
    if (size == 0) //export only 
        j = ft_strlen(var);
    else // env && export
    {
        if(var[size - 1] == '+' && var[size] == '=')
            j = size - 1;
        // else if(var[size] == '=')
        //     j = size + 1;
        else
            j = size;
    }
    return (j);
}

int get_len_char(char *s, char c)
{
    int i = 0;
    while(s && s[i])
    {
        if(*s != c)
            return (0);
        i++;
    }
    return (i);
}

void env_export_all_cases(char *var, char ***env, int size, t_node **addresses)
{
    int i;   
    int len;
    
    i = 0;
    len = get_equal(var);
    while(env && *env && (*env)[i])
    {
        if (!ft_strncmp((*env)[i], var, size))
        {
            if(var[len - 1] == '+' && var[len] == '=')
            {
                char *s = ft_strjoin((*env)[i] ,var + get_equal(var) + 1, addresses);
                (*env)[i] = ft_strdup(s, addresses);
            }
            else
            {
                (*env)[i] = ft_strdup(var, addresses);
            }
            return ;
        }
        i++;
    }
    *env = ft_array(*env, var, addresses);
}

void exec_export(char *var, char ***env, char ***ex_env, t_node **addresses)
{
    int i = 0;
    int j;
    int size;
    
    if(!var)
    {
        export_print(*ex_env);
        return ;
    }
    if(!check_error(var))
    {
        printf("export: not a valid identifier\n");
        return ;
    }
    size = get_best_size(var);
    if (!get_equal(var))
    {
       env_export_all_cases(var, ex_env, size , addresses);
       return ;
    }
    env_export_all_cases(var, ex_env, size, addresses);
    env_export_all_cases(var, env, size, addresses);
}

void exec_unset(char *s, char ***env, t_node **addresses)
{

    int i = 0;
    int len = 0;
    if(!s)
        return ;
    while(env && *env && (*env)[i])
    {
        if(ft_strncmp((*env)[i], s, ft_strlen(s)))
            len++;
        i++;
    }
    char **unset_array = ft_malloc(sizeof(char *) * (len + 1), addresses);
    if(!unset_array)
        return ;
    i = 0;
    int j = 0;
    while(env && *env && (*env)[i])
    {
        if(ft_strncmp((*env)[i], s, ft_strlen(s)))
            unset_array[j++] = ft_strdup((*env)[i], addresses);
        i++;
    }
    unset_array[j] = NULL;
    *env = unset_array;
}
