/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:34:25 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:34:33 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static bool	is_dir(char *arg)
{
	int		fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (true);
	}
	return (false);
}

static bool	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u' || arg[len - 1] != 'b' || \
	 arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p' || arg[len - 1] != 'm' || \
	 arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	is_file_valid(char *arg, bool is_cub)
{
	int	fd;

	if (is_dir(arg))
		return (err_msg(arg, "is a directory", FAILURE));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, strerror(errno), FAILURE));
	close(fd);
	if (is_cub && !is_cub_file(arg))
		return (err_msg(arg, "is not a .cub file", FAILURE));
	if (!is_cub && is_xpm_file(arg))
		return (err_msg(arg, "is not a .xpm file", FAILURE));
	return (SUCCESS);
}
