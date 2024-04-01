/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 03:08:21 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/27 03:08:46 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void pipe_parse_error(t_node *node)
{
    t_node *ptr; 

    ptr = node;
    while (ptr)
    {
        while(!ft_strncmp((ptr->type, "space", 5)))
            ptr = ptr -> next;
        if (!ft_strncmp(ptr->type, "pipe", 4))
        {
            ptr = ptr -> next;
            while(!ft_strncmp((ptr->type, "space", 5)))
                ptr = ptr -> next;
            //print error !
            printf("parse error near `|'");
        }
        else
        {
            while(!ft_strncmp((ptr->type, "space", 5)))
                ptr = ptr -> next;
            if (ptr->next != NULL && !ft_strncmp(ptr->type, "pipe", 4) && ptr->next->next == NULL)
            {
                printf("parse error near `|'");
                return;
            }
        }
        ptr = ptr -> next;
    }
}