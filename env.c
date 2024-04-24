/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/24 23:30:30 by miguiji          ###   ########.fr       */
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
int get_dollar(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == '$')
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

// function that expands the variables and modify the char **var remplace $EXEMPLE by its value
// if the variable is not found in the env it s place in the string will be left empy

void expand(t_node *node, t_env *env, t_node **addresses)
{
    char *response = NULL;
    char *var;
    int i;
    int x;

    x = 0;
    i = 0;
    if(!node || !ft_strcmp(node->type, "s_quote"))
        return ;
    while(node->value && ((char *)node->value)[i])
    {
        while(((char *)node->value)[i] != '\0')
        {
            if (((char *)node->value)[i] == '$' && ft_isalnum(((char *)node->value)[i + 1]))
                break ;
            i++;
        }
        response = ft_strjoin(response, ft_substr(node->value, x, i++, addresses), addresses);
        x = i;
        while(((char *)node->value)[i] != '\0' && ft_isalnum(((char *)node->value)[i]))
            i++;
        var = ft_strjoin(ft_substr(node->value, x, i - x, addresses), "=", addresses);
        response = ft_strjoin(response, get_environment(env->env, var), addresses);
        x = i;
    }
    node->value = response;
    // puts("--------------------------------");
    // printf("value = %s\n", (char *)node->value);
    // puts("--------------------------------");
    return ;
}

