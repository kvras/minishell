#include "minishell.h"

//hadi bach n executiw env
int exec_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        ft_putstr_fd(env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return 1;
}
// hadi bach nchoufo les paths
int get_env(char **env, char *var)
{
    char *tmp;
    
    tmp = getenv(var);
    if(tmp)
    {
        ft_putstr_fd(tmp, 1);
        ft_putstr_fd("\n", 1);
        free(tmp);
        return 1;
    }
    return 0;
}
// hadi bach n addiw wa7ed lvar
int put_env(char *var)
{
    int response;
    response = putenv(var);
    if(response)
        return (1);
    return 0;
}
int unset_env(char *var)
{
    char *str;
    int response;
    str = ft_strjoin(var, "=");
    response = putenv(str);
    free(str);
    if(response)
        return (1);
    return 0;
}
