/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:00:18 by szhong            #+#    #+#             */
/*   Updated: 2025/06/05 16:00:29 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	print_usage(void)
{
	ft_putstr_fd("\033[1;36m", 1);
	ft_putstr_fd("   ██████╗██╗   ██╗██████╗ ██████╗ ██████╗\n", 1);
	ft_putstr_fd("  ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n", 1);
	ft_putstr_fd("  ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n", 1);
	ft_putstr_fd("  ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n", 1);
	ft_putstr_fd("  ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n", 1);
	ft_putstr_fd("   ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝\033[0m\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[1;33mUsage:\033[0m ./cub3D <map_file.cub>\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[1;33mExamples:\033[0m\n", 1);
	ft_putstr_fd("  ./cub3D maps/macos/simple.cub   (macOS)\n", 1);
	ft_putstr_fd("  ./cub3D maps/macos/demo.cub     (macOS)\n", 1);
	ft_putstr_fd("  ./cub3D maps/linux/works.cub    (Linux)\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[1;33mControls:\033[0m\n", 1);
	ft_putstr_fd("  W/S       - Move forward/backward\n", 1);
	ft_putstr_fd("  A/D       - Strafe left/right\n", 1);
	ft_putstr_fd("  Left/Right- Rotate view\n", 1);
	ft_putstr_fd("  ESC       - Exit game\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[1;33mAvailable maps:\033[0m\n", 1);
	ft_putstr_fd("  maps/macos/  - For macOS (Apple Silicon & Intel)\n", 1);
	ft_putstr_fd("  maps/linux/  - For Linux systems\n", 1);
}

int	err_msg(char *msg, char *str, int code)
{
	ft_putstr_fd(RED "cub3D: Error", 2);
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n" RESET, 2);
	return (code);
}
