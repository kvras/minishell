/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:07:13 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/09 00:19:10 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_size(char *var, char *env, int size)
{
	int	c;

	c = get_equal(env);
	if (c && env[c - 1] == '+')
		c--;
	if (size && var[size - 1] == '+' && var[size] == '=' && !get_equal(env))
		return (get_equal(var) - 1 == ft_strlen(env));
	else if (size && var[size - 1] == '+' && var[size] == '=' && get_equal(env))
		return (get_equal(var) - 1 == c);
	else if (get_equal(var) && !get_equal(env))
		return (get_equal(var) == ft_strlen(env));
	else if (get_equal(var) && get_equal(env))
		return (get_equal(var) == c);
	return (0);
}

int	check_if_var_exist(char *var, char *env, int size)
{
	if (!ft_strncmp(env, var, size) && cmp_size(env, var))
		return (1);
	return (0);
}

int	get_best_size(char *var)
{
	int	j;
	int	size;

	j = 0;
	size = get_equal(var);
	if (size == 0)
		j = ft_strlen(var);
	else
	{
		if (var[size - 1] == '+' && var[size] == '=')
			j = size - 1;
		else
			j = size;
	}
	return (j);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!str1 && !str2)
		return (0);
	if (!str1 && str2)
		return (-str2[0]);
	if (!str2 && str1)
		return (str1[0]);
	while (str1[i] && str2[i])
	{
		if (str1[i] - str2[i] != 0)
			return (str1[i] - str2[i]);
		i++;
	}
	if (str1[i])
		return (str1[i]);
	else if (str2[i])
		return (-str2[i]);
	return (0);
}

int	check_char(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}
