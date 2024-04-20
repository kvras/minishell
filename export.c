#include "minishell.h"

static void swap(char **a, char **b)
{   
    char *c;
    c = *a;
    *a = *b;
    *b = c;
}
static void sort_env(char **env)
{
    int i;
    int j;

    i = 0;
    while(env && env[i])
    {
        j = i + 1;
        while(env[j])
        {
            if(strcmp(env[i], env[j]) > 0) // ft_strcmp
                swap(&env[i], &env[j]);
            j++;   
        }
        i++;
    }
}

static void	export_print(char **export_env)
{
    if(!export_env || !*export_env)
        return ; 
	sort_env(export_env);
	while (*export_env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(*export_env, 1);
		ft_putstr_fd("\n", 1);
		export_env++;
	}
}

static int	is_valid_key(char *command)
{
	int	i;

	i = 0;
	if (!ft_isalpha(command[i]) && command[i] != '_')
		return (0);
	while (command[i])
	{
		if (!ft_isalnum(command[i])
			&& command[i] != '_' && command[i] != '='
			&& command[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

static void export_env(char *var, char ***ex_env, t_node **addresses)
{
    int i;
    i = 0;
    
    if(!is_valid_key(var))
    {
        printf("export: not a valid identifier\n");
        return ;
    }
    if (ex_env && *ex_env && !ft_strncmp((*ex_env)[i], var, get_equal(var)))
    {
        (*ex_env)[i] = ft_strdup(var, addresses);
        return ;
    }
    *ex_env = ft_array(*ex_env, ft_strdup(var, addresses), addresses);
        return ;
}

void exec_export(char *var, char ***env, char ***ex_env, t_node **addresses)
{
    int i;
    i = 0;
    
    if(!var)
    {
        export_print(*ex_env);
        return ;
    }
    if (ex_env && *ex_env && !get_equal(var))
    {
       export_env(var, ex_env, addresses);
       return ;
    }
    while(env && *env && (*env)[i])
    {
        
        if (is_valid_key(var) && !ft_strncmp((*env)[i], var, get_equal(var)))
        {
            (*env)[i] = ft_strdup(var, addresses);
            return ;
        }
        i++;
    }
    if (is_valid_key(var))
    {
        *env = ft_array(*env, ft_strdup(var,addresses), addresses);
        *ex_env = ft_array(*ex_env, ft_strdup(var, addresses), addresses);
    }
    else
        printf("export: not a valid identifier\n");
}

// void exec_unset(char *s, char ***env, t_node **address)
// {
//     int i = 0;
//     int len = 0;
//     if(!s)
//         return ;
//     while(env && *env && (*env)[i])
//     {
//         if(ft_strncmp((*env)[i], s, ft_strlen(s)))
//             len++;
//         i++;
//     }
//     // char **unset_array = (char **)malloc((sizeof(char *) * (len+1)))
//     char **unset_array = (char **)ft_malloc((sizeof(char *) * (len+1)), address);
//     if(!unset_array)
//         return ;
//     i = 0;
//     int j = 0;
//     while(env && *env && (*env)[i])
//     {
//         if(ft_strncmp((*env)[i], s, ft_strlen(s)))
//             unset_array[j++] = ft_strdup((*env)[i], address);
//         i++;
//     }
//     unset_array[j] = NULL;
//     *env = unset_array;
// }
