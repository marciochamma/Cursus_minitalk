/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:57:13 by mchamma           #+#    #+#             */
/*   Updated: 2023/12/17 17:54:35 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_free_to_send;

void	send_msg(pid_t server_pid, char c, int *i, int *bit)
{
	if (g_free_to_send)
	{
		if (*bit >= 0)
		{
			g_free_to_send = 0;
			if (c & (1 << *bit))
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			(*bit)--;
		}
		else
		{
			*bit = 7;
			(*i)++;
		}
		usleep(100);
	}
}

void	signal_handler(int signal_num)
{
	if (signal_num == SIGUSR1)
		g_free_to_send = 1;
}

void	config_signals(void)
{
	struct sigaction	signal;

	signal.sa_handler = &signal_handler;
	signal.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &signal, 0) < 0)
		ft_printf("bad behaviour: SIGUSR1\n");
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;
	int		bit;

	i = 0;
	bit = 7;
	g_free_to_send = 1;
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		config_signals();
		while (argv[2][i])
		{
			if (g_free_to_send)
				send_msg(server_pid, argv[2][i], &i, &bit);
		}
	}
	else
		ft_printf("Invalid arguments\n");
	return (0);
}
