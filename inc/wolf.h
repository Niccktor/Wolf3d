/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 05:29:43 by tbeguin           #+#    #+#             */
/*   Updated: 2019/09/21 07:36:09 by tbeguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#include <mlx.h>
#include "../libft/libft.h"


typedef struct			s_player
{
	double				x;
	double				y;
	double				z;
	int					angle;	
}						t_player;

typedef struct			s_map
{
	int					**map;
	int					height;
	int					width;
}						t_map;

typedef struct			s_image
{
	void				img;
	unsigned int		*img_str;
	int					height;
	int					width;
	int					bpp;
	int					endian;
}						t_image;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	struct s_player		player;
	struct s_image		img;
	struct s_map		map;
}						t_mlx;

void					init_all(t_mlx *all);

#endif 
