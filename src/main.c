/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:26:06 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/23 23:00:43 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"
#include <math.h>
#include<stdio.h>

int		main(int argc, char **argv)
{
	t_mlx all;

	all.name = argv[0];
	if (argc != 2)
		argv_err(&all);
	init_all(&all);

	int m = 0;
	int n;
	while (all.map.height > m)
	{
		n = 0;
		while (all.map.width > n)
		{
			printf("%d", all.map.map[m][n]);
			n++;
		}
		printf("\n");
		m++;
	}
	mlx_hook(all.win, 2, 1L << 0, key_event, &all);
	mlx_hook(all.win, 6, 1L << 6, ft_mouse_move, &all);
	mlx_hook(all.win, 17, 1L << 0, ft_exit, &all);
	mlx_loop_hook(all.mlx, threads_loop, &all);
	mlx_loop(all.mlx);
	return (0);
}

int		ft_exit(t_mlx *all)
{
	mlx_destroy_window(all->mlx, all->win);
	exit(0);
	return (0);
}

int		argv_err(t_mlx *all)
{
	ft_putstr("Usage  : ");
	ft_putstr(all->name);
	ft_putstr(" <maps>\n");
	exit(0);
	return (0);
}
