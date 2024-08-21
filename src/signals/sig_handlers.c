/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/08/21 16:23:35 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sighandle_child(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(STDOUT_FILENO, "\n", 1);
	}
	g_siginfo = sig;
}

void	ms_sighandle(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
