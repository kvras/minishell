/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/01 03:31:45 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_env(char **env)
{
    int i = 0;
    char **array;

    while(env[i])
        i++;
    array = (char **)malloc((sizeof(char *) * (i + 1)));
    if(!array)
        return NULL;
    i = 0;
    while(env && env[i])
    {
        array[i] = ft_strdup(env[i]);
        i++;
    }
    array[i] = NULL;
    return (array);
}

// hadi bach n addiw wa7ed lvar l env
void exec_export(char *var, char ***env)
{
    int i;
    i = 0;
    if(!var)
        return ;
   while(env && *env && (*env)[i])
   {
        if(!ft_strncmp((*env)[i], var, get_equal(var)))
        {
            free((*env)[i]);
             (*env)[i] = ft_strdup(var);
             return ;
        }
        i++;
   }
    if(ft_isalpha(var[0]) || var[0] == '_')
        *env = ft_array(*env, ft_strdup(var));
    else
         printf("export: not a valid identifier\n");
}

// hadi bach n unsetiw wa7ed lvar
void exec_unset(char *s, char ***env)
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
    char **unset_array = (char **)malloc((sizeof(char *) * (len+1)));
    if(!unset_array)
        return ;
    i = 0;
    int j = 0;
    while(env && *env && (*env)[i])
    {
        if(ft_strncmp((*env)[i], s, ft_strlen(s)))
            unset_array[j++] = ft_strdup((*env)[i]);
        i++;
    }
    unset_array[j] = NULL;
    *env = unset_array;
}

//hadi bach n executiw env
int exec_env(char **env)
{
    int i;

    i = 0;
    while(env && env[i])
    {
        ft_putstr_fd(env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return 0;
}

// hadi bach n unsetiw wa7ed lvar
int get_equal(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == '=')
            return i;
        i++;
    }
    return 0;
}
int check_char(char *s,char c)
{
    if(!s)
        return 0;
    while(*s)
    {
        if(*s == c)
            return 1;
        s++;
    
    }
    return (0);
}
int expand(char *var, char **env)
{
    int i;

    i = 0;
    if (!check_char(var, '$'))
        return (0);
    char *trim = ft_strnstr(var, "$",ft_strlen(var));
    while (env && env[i])
    {
        if (!ft_strncmp(,, get_equal(env[i])))
        {
        }
        else if (!ft_strncmp(env[i], trim + 1, get_equal(env[i])))
        {
            ft_putstr_fd(env[i] + get_equal(env[i]) + 1, 1);
            ft_putstr_fd("\n", 1);
            return (1);
        }
        i++;
    }
    return 0;
}
