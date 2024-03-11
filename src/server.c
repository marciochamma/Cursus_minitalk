/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:33:33 by mchamma           #+#    #+#             */
/*   Updated: 2023/12/12 15:58:22 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal_num, siginfo_t *info, void *context)
{
	static unsigned char	n;
	static int				i;
	int						bit_value;

	(void) context;
	if (signal_num == SIGUSR1)
		bit_value = 1;
	else
		bit_value = 0;
	n = (n << 1) + bit_value;
	i++;
	if (i == 8)
	{
		write(1, &n, 1);
		i = 0;
		n = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	config_signals(void)
{
	struct sigaction	signal;

	signal.sa_sigaction = &signal_handler;
	signal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &signal, 0) < 0)
		ft_printf("bad behaviour: SIGUSR1 setup\n");
	if (sigaction(SIGUSR2, &signal, 0) < 0)
		ft_printf("bad behaviour: SIGUSR2 setup\n");
}

int	main(void)

{
	ft_printf("Server PID: %d\n", getpid());
	config_signals();
	while (1)
		;
	return (0);
}
