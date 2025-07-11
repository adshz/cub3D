/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:39:42 by aalissa           #+#    #+#             */
/*   Updated: 2025/07/04 18:00:53 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <stdio.h>
#include <string.h>

void	init_game(char **argv, t_cub *cub, t_file_input *input)
{
	init_data(cub);
	input_obj_init(argv[1], input);
	return ;
}

int	main(int argc, char **argv)
{
	t_cub			cub;
	t_file_input	input;

	if (argc != 2)
		something_went_wrong("enter one map, no more no less", NULL);
	init_game(argv, &cub, &input);
	parse_file(argv, &cub, &input);
	assign_data(&cub, &input);
	if (validate_data(&cub) != SUCCESS)
		return (FAILURE);
	init_mlx(&cub);
	transform_textures(&cub);
	render_game(&cub);
	event_listening(&cub);
	mlx_loop_hook(cub.mlx_ptr, render_wrapper, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
