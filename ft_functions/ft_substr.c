/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:46:01 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/10 23:45:23 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(const char *str, int start, int len, t_node **ad)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		return (ft_strdup("", ad));
	if (ft_strlen(str + start) < len)
		len = ft_strlen(str + start);
	ptr = ft_malloc(len + 1, ad);
	if (ptr == NULL)
		return (0);
	while (i < len && (str + start)[i])
	{
		ptr[i] = (str + start)[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
