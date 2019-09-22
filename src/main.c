/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:26:06 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/22 18:10:30 by tbeguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"

int		main(int argc, char **argv)
{
	t_mlx all;

	all.name = argv[0];
	if (argc != 2)
		argv_err(&all);
	init_all(&all);

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
