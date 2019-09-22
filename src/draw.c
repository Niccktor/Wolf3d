/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 14:11:58 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/22 18:25:04 by tbeguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf.h"
#include <stdio.h>


void		fill_pixel(t_mlx *all, int x, int y, unsigned int c)
{
	printf("x = %d y = %d\n", x, y);
	if (x >= 0 && x < all->img.width
			&& y >= 0 && y < all->img.height)
	{
		all->img.img_str[y * all->img.width + x] = c;
		c = 0xFF0000;	
	}
}

void		ver_line(t_mlx *a, int x, int s, int e, unsigned int c)
{
	while (s < e)
	{
		fill_pixel(a, x, s, c);
		s++;
	}
}
