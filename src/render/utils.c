/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:05:01 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:06:14 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	image->img_initial_data_addr[y * (image->size_line / 4) + x] = color;
}
