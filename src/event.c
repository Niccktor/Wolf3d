/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicktor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 22:45:14 by nicktor           #+#    #+#             */
/*   Updated: 2019/09/30 18:57:34 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"
#include <stdio.h>
#include <math.h>
#define THETHA 0.01

int		ft_mouse_move(int x, int y, t_mlx* all)
{
	double old_dir_x;
	double old_plan_x;
	double theta;

	if (all->x == -1 && all->y == -1)
	{
		all->x = x;
		all->y = y;
		return (0);
	}

	if (x >= all->x)
		theta = -0.015;
	else
		theta = 0.015;

	old_dir_x = all->player.dir_x;
	old_plan_x = all->player.p_x;
	all->player.dir_x = all->player.dir_x * cos(theta) - all->player.dir_y * sin(theta);
	all->player.dir_y = old_dir_x * sin(theta) + all->player.dir_y * cos(theta);
	all->player.p_x = all->player.p_x * cos(theta) - all->player.p_y * sin(theta);
	all->player.p_y = old_plan_x * sin(theta) + all->player.p_y * cos(theta);
	
	all->x = x;
	all->y = y;
	/*printf("x = %d, y = %d\n", x, y);*/
	threads_loop(all);
	//threads(*all);
	return (0);
}

int		key_event(int key, t_mlx *all)
{
	double old_dir_x;
	double old_plan_x;

	if (key == ESC)
		ft_exit(all);
	if  (key == KEY_W && all->map.map[(int)(all->player.x + 0.3 * all->player.dir_x)][(int)(all->player.y + 0.3 * all->player.dir_y)] != 1)
	{
		all->player.x += 0.1 * all->player.dir_x;
		all->player.y += 0.1 * all->player.dir_y;
	}
	if (key == KEY_S && all->map.map[(int)(all->player.x - 0.3 * all->player.dir_x)][(int)(all->player.y - 0.3 * all->player.dir_y)] != 1)
	{
		all->player.x -= 0.1 * all->player.dir_x;
		all->player.y -= 0.1 * all->player.dir_y;
	}
	if (key == KEY_A && all->map.map[(int)(all->player.x - 0.3 * all->player.p_x)][(int)(all->player.y - 0.3 * all->player.p_y)] != 1)
	{
		all->player.x -= 0.1 * all->player.p_x;
		all->player.y -= 0.1 * all->player.p_y;
	}
	if (key == KEY_D && all->map.map[(int)(all->player.x + 0.3 * all->player.p_x)][(int)(all->player.y + 0.3 * all->player.p_y)] != 1)
	{
		all->player.x += 0.1 * all->player.p_x;
		all->player.y += 0.1 * all->player.p_y;
	}
	if (key == KEY_Q)
	{
		old_dir_x = all->player.dir_x;
		old_plan_x = all->player.p_x;
		all->player.dir_x = all->player.dir_x * cos(THETHA) - all->player.dir_y * sin(THETHA);
		all->player.dir_y = old_dir_x * sin(THETHA) + all->player.dir_y * cos(THETHA);
		all->player.p_x = all->player.p_x * cos(THETHA) - all->player.p_y * sin(THETHA);
		all->player.p_y = old_plan_x * sin(THETHA) + all->player.p_y * cos(THETHA);
	}
	if (key == KEY_E)
	{
		old_dir_x = all->player.dir_x;
		old_plan_x = all->player.p_x;
		all->player.dir_x = all->player.dir_x * cos(-THETHA) - all->player.dir_y * sin(-THETHA);
		all->player.dir_y = old_dir_x * sin(-THETHA) + all->player.dir_y * cos(-THETHA);
		all->player.p_x = all->player.p_x * cos(-THETHA) - all->player.p_y * sin(-THETHA);
		all->player.p_y = old_plan_x * sin(-THETHA) + all->player.p_y * cos(-THETHA);
	}
	//printf("key = %d\nx = %f, y = %f\n", key, all->player.x, all->player.y);
	threads_loop(all);
	//threads(*all);
	return (0);
}
