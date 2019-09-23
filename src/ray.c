/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 13:36:49 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/23 20:44:02 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"
#include <math.h>
#include <stdio.h>

static void		dda(t_mlx *all)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (all->ray.side_dist_x < all->ray.side_dist_y)
		{
			all->ray.side_dist_x += all->ray.dx;
			all->ray.x += all->ray.step_x;
			all->ray.side = 0;
		}
		else
		{
			all->ray.side_dist_y += all->ray.dy;
			all->ray.y += all->ray.step_y;
			all->ray.side = 1;
		}
		if (all->map.map[all->ray.x][all->ray.y] == 1)
			hit = 1;
	}
}

static void		set_side_dist(t_mlx *all)
{
	if (all->ray.dir_x < 0)
	{
		all->ray.step_x = -1;
		all->ray.side_dist_x = (all->player.x - all->ray.x) * all->ray.dx;
	}
	else
	{
		all->ray.step_x = 1;
		all->ray.side_dist_x = (all->ray.x + 1.0f - all->player.x) * all->ray.dx;
	}
	if (all->ray.dir_y < 0)
	{
		all->ray.step_y = -1;
		all->ray.side_dist_x = (all->player.y - all->ray.y) * all->ray.dy;
	}
	else
	{
		all->ray.step_y = 1;
		all->ray.side_dist_y = (all->ray.y + 1.0f - all->player.y) * all->ray.dy;
	}
}

static void		cast_wall(t_mlx *all, int i)
{
	int wall_dist;
	int	line_height;
	int	start;
	int	end;
	int h;

	h = 1000;
	if (all->ray.side == 0)
		wall_dist = (all->ray.x - all->player.x
				+ (1 - all->ray.step_x) / 2) / all->ray.dir_x;
	else
		wall_dist = (all->ray.y - all->player.y
				+ (1 - all->ray.step_y) / 2) / all->ray.dir_y;
	line_height = (h / wall_dist);
	start = (line_height * -1) / 2 + h / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + h / 2;
	if (end >= h)
		end = h - 1;
	ver_line(all, i, start, end, 0xFF0000);
}

void			render(t_mlx *all)
{
	int i;

	i = 0;
	printf("%f, %f\n%f, %f\n%f, %f\n", all->player.x, all->player.y, all->player.dir_x, all->player.dir_y, all->player.p_x, all->player.p_y);
	while (i < all->img.width)
	{
		all->ray.x = (int)all->player.x;
		all->ray.y = (int)all->player.y;
		all->ray.cam_x = 2 * i / (double)all->img.width - 1;
		all->ray.dir_x = all->player.dir_x
			+ all->player.p_x * all->ray.cam_x;
		all->ray.dir_y = all->player.dir_y
			+ all->player.p_y * all->ray.cam_x;
		all->ray.dx = fabs(1 / all->ray.dir_x);
		all->ray.dx = fabs(1 / all->ray.dir_y);
		set_side_dist(all);
		dda(all);
		cast_wall(all, i);
		mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
		i++;
	}
}
