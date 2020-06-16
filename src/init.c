/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:51:29 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/23 22:40:16 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"
#include<stdio.h>


static void		init_maps(t_mlx *all, char* map_file)
{
	all->map.file = map_file;
	if (read_map(all, all->map.file) == -1)
		exit(0);
}

static void		init_player(t_mlx *all)
{
	all->player.x = 5.0f;
	all->player.y = 5.0f;
	all->player.z = 0.0f;
	all->player.dir_x = -1.0f;
	all->player.dir_y = 0.0f;
	all->player.p_x = 0.0f;
	all->player.p_y = 0.66f;
}

void	init_all(t_mlx *all, char *map_file)
{
	int	bpp;
	int	s_l;
	int	endian;

	ft_bzero(all, sizeof(t_mlx));
	all->img.width = 500;
	all->img.height = 500;
	all->x = -1;
	all->y = -1;
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->img.width, all->img.height,
			"Wolf3d tbeguin@42");
	all->img.img = mlx_new_image(all->mlx, all->img.width, all->img.height);
	all->img.img_str = (unsigned int *)mlx_get_data_addr(all->img.img,
		   	&bpp, &s_l, &endian);
	ft_bzero(all->img.img_str, all->img.width * all->img.height * 4);
	init_maps(all, map_file);
	init_player(all);
	threads(*all);
}
