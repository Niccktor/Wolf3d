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

static void		render_init(t_mlx* all, int i)
{
	all->ray.cam_x = 2 * i / (double)all->img.width - 1;

	all->ray.dir_x = all->player.dir_x + all->player.p_x * all->ray.cam_x;
	all->ray.dir_y = all->player.dir_y + all->player.p_y * all->ray.cam_x;

	all->ray.x = (int)all->player.x;
	all->ray.y = (int)all->player.y;

	all->ray.dx = (all->ray.dir_y == 0) ? 0 : ((all->ray.dir_x == 0) ? 1 : fabs(1 / all->ray.dir_x));
	all->ray.dy = (all->ray.dir_x == 0) ? 0 : ((all->ray.dir_y == 0) ? 1 : fabs(1 / all->ray.dir_y));

}

/* https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm) */

static void render_side(t_mlx* all)
{
	if (all->ray.dir_x < 0)
	{
		all->ray.step_x = -1;
		all->ray.side_dist_x = (all->player.x - all->ray.x) * all->ray.dx;
	}
	else
	{
		all->ray.step_x = 1;
		all->ray.side_dist_x = (all->ray.x + 1.0 - all->player.x) * all->ray.dx;
	}

	if (all->ray.dir_y < 0)
	{
		all->ray.step_y = -1;
		all->ray.side_dist_y = (all->player.y - all->ray.y) * all->ray.dy;
	}
	else
	{
		all->ray.step_y = 1;
		all->ray.side_dist_y = (all->ray.y + 1.0 - all->player.y) * all->ray.dy;
	}
}

static void		render_dda(t_mlx* all)
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
		if (all->map.map[all->ray.x][all->ray.y] >= 1 && all->map.map[all->ray.x][all->ray.y] != 255)
		{
			hit = 1;
			all->ray.wall = all->map.map[all->ray.x][all->ray.y] - 1;
			if (all->ray.wall > all->text_max)
				all->ray.wall = 0;
		}
	}
}

static void wall_dist(t_mlx* all)
{
	all->ray.perpWallDist = 0.0f;
	if (all->ray.side == 0)
		all->ray.perpWallDist = (all->ray.x - all->player.x + (1 - all->ray.step_x) / 2) / all->ray.dir_x;
	else
		all->ray.perpWallDist = (all->ray.y - all->player.y + (1 - all->ray.step_y) / 2) / all->ray.dir_y;
	all->ray.lineHeight = (int)(all->img.height / all->ray.perpWallDist);
	all->ray.start = -all->ray.lineHeight / 2 + all->img.height / 2;
	if (all->ray.start < 0)
		all->ray.start = 0;
	all->ray.end = all->ray.lineHeight / 2 + all->img.height / 2;
	if (all->ray.end >= all->img.height)
		all->ray.end = all->img.height - 1;
}

static void render_wall(t_mlx* all, int i, int j, int texY)
{
	double step;
	double wallX;
	int textureX;
	double texPos;

	if (all->ray.side == 0)
		wallX = all->player.y + all->ray.perpWallDist * all->ray.dir_y;
	else
		wallX = all->player.x + all->ray.perpWallDist * all->ray.dir_x;
	wallX -= floor(wallX);
	textureX = (int)(wallX * (double)(all->texture[all->ray.wall]->width));
	if (all->ray.side == 0 && all->ray.dir_x > 0)
		textureX = all->texture[all->ray.wall]->width - textureX - 1;
	if (all->ray.side == 1 && all->ray.dir_y < 0)
		textureX = all->texture[all->ray.wall]->width - textureX - 1;
	step = 1.0 * all->texture[all->ray.wall]->height / all->ray.lineHeight;
	texPos = (all->ray.start - all->img.height / 2 + all->ray.lineHeight / 2) * step;
	j = all->ray.start;
	while (j < all->ray.end)
	{
		texY = (int)texPos & (all->texture[all->ray.wall]->height - 1);
		texPos += step;
		fill_pixel(all, i, j , all->texture[all->ray.wall]->img_str[all->texture[all->ray.wall]->height * texY + textureX]);
		j++;
	}
}

/*
	cast_ceiling(all);
	cast_wall(all);
	cast_floor(all);
	*/
	/*ver_line(all, i, 0, start, 0x00FF00);
	if (all->ray.side == 1)
		ver_line(all, i, start, end, 0xFF00FF);
	else
		ver_line(all, i, start, end, 0xFF00FF / 2);
	ver_line(all, i, end,all->img.height, 0xFF0000);
*/
/*static void		cast_floor(t_mlx* all)
{
	int i;
	int j;
	double step_x;
	double step_y;
	double floor_x;
	double floor_y;

	i = 0;
	while (i < all->img.height)
	{
		step_x = ((0.5 * all->img.height) / (i - all->img.height)) * ((all->player.dir_x + all->player.p_x) - (all->player.dir_x - all->player.p_x)) / all->img.width;
		step_y = ((0.5 * all->img.height) / (i - all->img.height)) * ((all->player.dir_y + all->player.p_y) - (all->player.dir_y - all->player.p_y)) / all->img.width;

		floor_x = all->player.x + ((0.5 * all->img.height) / (i - all->img.height)) * (all->player.dir_x - all->player.p_x);
		floor_y = all->player.x + ((0.5 * all->img.height) / (i - all->img.height)) * (all->player.dir_y - all->player.p_y);
	}
}*/

void			*render(void *thd)
{
	t_thread	*thread;
	t_mlx		all;
	int			i;
	int			i_max;

	thread = thd;
	all = thread->all;
	i = thread->i * (all.img.width / NB_THD);
	i_max = (thread->i + 1) * (all.img.width / NB_THD);
	if (thread->i + 1 == NB_THD)
		i_max = all.img.width;
	while (i < i_max)
	{
		render_init(&all, i);
		render_side(&all);
		render_dda(&all);
		wall_dist(&all);
		//cast_floor(&all);
		render_wall(&all, i, 0, 0);
		i++;
	}
	return (0);
}