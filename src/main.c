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

/*
	double posX = 5.0f;
	double posY = 5.0f;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	int x = 0;

	while (x < all.img.width)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(all.map.width) - 1; //x-coordinate in camera space
		

		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;
		//
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		 double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		 double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (all.map.map[mapX][mapY] > 0) hit = 1;
		}

		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		int z = all.img.height;
		int lineHeight = (int)(z / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + z / 2;
		if (drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + z / 2;
		if (drawEnd >= z)drawEnd = z - 1;

		printf("test : x %d, drawStart %d, drawEnd %d\n", x, drawStart, drawEnd);
		ver_line(&all, x, drawStart, drawEnd, 0xFF00FF);
		x++;
	}
	mlx_put_image_to_window(all.mlx, all.win, all.img.img, 0, 0);

	*/

	mlx_hook(all.win, 2, 1L << 0, key_event, &all);
	mlx_hook(all.win, 6, 1L << 6, ft_mouse_move, &all);
	mlx_hook(all.win, 17, 1L << 0, ft_exit, &all);
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
