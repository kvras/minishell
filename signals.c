/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:34:38 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/24 23:14:01 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_signals(void)
{
    rl_catch_signals = 0;
    signal(SIGINT, ctr_c);
    signal(SIGQUIT, bach_slash);
}

void ctr_d(void)
{
    ft_putstr_fd("exit\n", 1);
    exit(0);
}

void ctr_c(int sig)
{
    if(sig == SIGINT)
    {
        write(1,"\n",1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}
void bach_slash(int sig)
{
    if (sig == SIGQUIT)
    {
        signal(SIGQUIT, SIG_IGN);
    }
}