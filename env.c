/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/20 15:09:58 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_env(char **env)
{
    int i = 0;
    char **array;

    while(env[i])
        i++;
    // ft_malloc((sizeof(char *) * (i + 1)), (void **)&array, NULL);
   array = malloc((sizeof(char *) * (i + 1)));
    if(!array)
        return NULL;
    i = 0;
    while(env && env[i])
    {
        array[i] = malloc((sizeof(char) * (ft_strlen(env[i]) + 1)));
        if(!array[i])
            return NULL;
        ft_strlcpy(array[i], env[i], ft_strlen(env[i]) + 1);
        i++;
    }
    array[i] = NULL;
    return (array);
}

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
    if (!var || var[0] != '$' || !var[1])
        return (0);
    while (env && env[i])
    {
        if (!ft_strncmp(env[i], var + 1, get_equal(env[i])))
        {
            ft_putstr_fd(env[i] + get_equal(env[i]) + 1, 1);
            ft_putstr_fd("\n", 1);
            return (1);
        }
        i++;
    }
    ft_putstr_fd("\n", 1);
    return 1;
}
