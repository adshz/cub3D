/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:03:08 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:04:20 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void  init_texture_pixels(t_cub *cub)
{
  int i;

  if (cub->texture_pixels)
    free_matrix((void **)cub->texture_pixels);
  cub->texture_pixels = ft_calloc(cub->win_height + 1, sizeof(int **));
  if (!cub->texture_pixels)
    clean_exit(cub, err_msg(NULL, ERR_MALLOC, 1));
  i = 0;
  while (i < cub->win_height)
  {
    cub->texture_pixels[i] = ft_calloc(cub->win_width + 1, sizeof * cub->texture_pixels);
    if (!cub->texture_pixels[i])
      clean_exit(cub, err_msg(NULL, ERR_MALLOC, 1));
    i++;
  }
}

static void	assign_texture_index(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			cub->texture_data.index = WEST;
		else
			cub->texture_data.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			cub->texture_data.index = SOUTH;
		else
			cub->texture_data.index = NORTH;
	}
}

void	update_texture_pixels(t_cub *cub, t_texture_data *texture, t_ray *ray, int x)
{
	int	y;
	int	color;

	assign_texture_index(cub, ray);
	texture->x = (int)(ray->wall_x * texture->size);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0)) 
		texture->x = texture->size - texture->x - 1;
	texture->step = 1.0 * texture->size / ray->line_height;
	texture->pos = (ray->draw_start - cub->win_height / 2 + ray->line_height / 2) * texture->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture->y = (int)texture->pos  & (texture->size - 1);
		texture->pos += texture->step;
		color = cub->textures[texture->index][texture->size * texture->y + texture->x];
		if (texture->index == NORTH || texture->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			cub->texture_pixels[y][x] = color;
		y++;
	}
}
