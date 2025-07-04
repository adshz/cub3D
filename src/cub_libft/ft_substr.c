/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:57:06 by szhong            #+#    #+#             */
/*   Updated: 2025/05/09 15:44:36 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Creates a substring of a string starting from the specified index.
 *
 * @param s The original string.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 * @return The created substring or an empty string if invalid parameters.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (s == NULL || start >= my_strlen(s))
	{
		substr = (char *)malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > my_strlen(s) - start)
		len = my_strlen(s) - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (0);
	i = start;
	j = 0;
	while (i < my_strlen(s) && j < len)
	{
		substr[j++] = s[i++];
	}
	substr[j] = '\0';
	return (substr);
}
