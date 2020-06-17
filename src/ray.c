/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 13:36:49 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/30 18:31:24 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"
#include <math.h>
#include <stdio.h>

/*
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

	h = 1920 / 2;
	if (all->ray.side == 0)
		wall_dist = (all->ray.x - all->player.x
				+ (1 - all->ray.step_x) / 2) / all->ray.dir_x;
	else
		wall_dist = (all->ray.y - all->player.y
				+ (1 - all->ray.step_y) / 2) / all->ray.dir_y;
	line_height = (int)(h / wall_dist);
	start = -line_height / 2 + h / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + h / 2;
	if (end >= h)
		end = h - 1;

	static int k = 0;
	if (k == 1)
	{
		ver_line(all, i, start, end, 0x0000FF);
		k++;
	}
	else if (k == 2)
	{
		k = 0;
		ver_line(all, i, start, end, 0x00FF00);
	}
	else
	{
		ver_line(all, i, start, end, 0xFF0000);
		k++;
	}

}
*/
int		threads_loop(t_mlx* all)
{

	all->time = (unsigned long)time(NULL);
	all->ticks++;
	if (all->time - all->oldTime != 0)
	{
		printf("fps = %lu ticks = %lu\n", all->fps, all->ticks);
		all->ticks = 0;
		all->fps = 0;
	}
	all->oldTime = all->time;
	if (all->ticks % 10000 != 0)
		return (1);
	else
		all->fps++;
	threads(*all);
	return (1);
}

int		threads(t_mlx all)
{
	int			i;
	t_thread	threads[NB_THD];

	i = 0;
	ft_bzero(all.img.img_str, all.img.width * all.img.height * 4);

	while (i < NB_THD)
	{
		threads[i].i = i;
		threads[i].all = all;
		pthread_create(&threads[i].thread, NULL, render , &threads[i]);
		i++;
	}
	i = 0;
	while (i < NB_THD)
		pthread_join(threads[i++].thread, NULL);
	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);
	return (0);
}



void			*render(void *thd)
{
	t_thread	*thread = thd;
	t_mlx	all = thread->all;
	int i;

	i = thread->i * (all.img.width / NB_THD);
	int i_max = (thread->i + 1) * (all.img.width / NB_THD);
	if (thread->i + 1 == NB_THD)
		i_max = all.img.width;
	while (i < i_max)
	{
		all.ray.cam_x = 2 * i / (double)all.img.width - 1;

		all.ray.dir_x = all.player.dir_x + all.player.p_x * all.ray.cam_x;
		all.ray.dir_y = all.player.dir_y + all.player.p_y * all.ray.cam_x;

		all.ray.x = (int)all.player.x;
		all.ray.y = (int)all.player.y;

		all.ray.dx = (all.ray.dir_y == 0) ? 0 : ((all.ray.dir_x == 0) ? 1 : fabs(1 / all.ray.dir_x));
		all.ray.dy = (all.ray.dir_x == 0) ? 0 : ((all.ray.dir_y == 0) ? 1 : fabs(1 / all.ray.dir_y));

		if (all.ray.dir_x < 0)
		{
			all.ray.step_x = -1;
			all.ray.side_dist_x = (all.player.x - all.ray.x) * all.ray.dx;
		}
		else
		{
			all.ray.step_x = 1;
			all.ray.side_dist_x = (all.ray.x  + 1.0 - all.player.x) * all.ray.dx;
		}

		if (all.ray.dir_y < 0)
		{
			all.ray.step_y = -1;
			all.ray.side_dist_y = (all.player.y - all.ray.y) * all.ray.dy;
		}
		else
		{
			all.ray.step_y = 1;
			all.ray.side_dist_y = (all.ray.y + 1.0 - all.player.y) * all.ray.dy;
		}

		int hit = 0;

		while (hit == 0)
		{
			if (all.ray.side_dist_x < all.ray.side_dist_y)
			{
				all.ray.side_dist_x += all.ray.dx;
				all.ray.x += all.ray.step_x;
				all.ray.side = 0;
			}
			else
			{
				all.ray.side_dist_y += all.ray.dy;
				all.ray.y += all.ray.step_y;
				all.ray.side = 1;
			}
			if (all.map.map[all.ray.x][all.ray.y] == 1)
				hit = 1;
		}

		double perpWallDist;

		if (all.ray.side == 0)
			perpWallDist = (all.ray.x - all.player.x + (1 - all.ray.step_x) / 2) / all.ray.dir_x;
		else
			perpWallDist = (all.ray.y - all.player.y + (1 - all.ray.step_y) / 2) / all.ray.dir_y;

		int lineHeight = (int)(all.img.height / perpWallDist);

		int start = -lineHeight / 2 + all.img.height / 2;
		if (start < 0)
			start = 0;
		int end = lineHeight / 2 + all.img.height / 2;
		if (end >= all.img.height)
			end = all.img.height - 1;

		/*
		all->ray.cam_x = 2 * i / (double)all->img.width - 1;
		all->ray.dir_x = all->player.dir_x
			+ all->player.p_x * all->ray.cam_x;
		all->ray.dir_y = all->player.dir_y
			+ all->player.p_y * all->ray.cam_x;
		all->ray.dx = fabs(1 / all->ray.dir_x);
		all->ray.dx = fabs(1 / all->ray.dir_y);
		set_side_dist(all);
		dda(all);
		cast_wall(all, i);*/
		ver_line(&all, i, 0, start, 0x00FF00);
		if (all.ray.side == 1)
			ver_line(&all, i, start, end, 0xFF00FF);
		else 
			ver_line(&all, i, start, end, 0xFF00FF / 2);

		ver_line(&all, i, end, all.img.height, 0xFF0000);

		i++;
	}
	return (0);
}
