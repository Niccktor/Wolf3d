/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:26:06 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/21 05:41:18 by tbeguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		main(int argc, char **argv)
{
	t_mlx all;

	all.name = argv[0];
	if (argc != 2)
		argv_err(all);
	init_all(&all, argv[1]);

}

int		argv_err(t_mlx *all)
{
	ft_putstr("Usage  : ");
	ft_putstr(all->name);
	ft_putstr(" <maps>");

}
