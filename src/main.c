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
	{
		ft_putstr_fd(RED "Error: Invalid number of arguments\n" RESET, 2);
		print_usage();
		return (EXIT_FAILURE);
	}
	init_game(argv, &cub, &input);
	parse_file(argv, &cub, &input);
	assign_data(&cub, &input);
	if (validate_data(&cub) != SUCCESS)
		return (FAILURE);
	init_mlx(&cub);
	transform_textures(&cub);
	render_game(&cub);
	setup_hooks(&cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (0);
}
