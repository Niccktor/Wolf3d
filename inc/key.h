/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicktor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 23:03:26 by nicktor           #+#    #+#             */
/*   Updated: 2019/09/23 23:07:05 by nicktor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	KEY_H
# define KEY_H

# ifdef __linux__
# define ESC	65307
# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363
# define KEY_A	97
# define KEY_W	119
# define KEY_Q	113
# define KEY_E	101	
# define KEY_D	100	
# define KEY_S	115	



# else
# define ESC	53
# define UP		126
# define DOWN	125
# define LEFT	123
# define RIGHT	124
# define KEY_A	97
# define KEY_W	119
# define KEY_Q	113
# define KEY_E	101	
# define KEY_D	100	
# define KEY_S	115	

# endif
#endif
