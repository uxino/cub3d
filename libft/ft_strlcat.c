/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:09:24 by museker           #+#    #+#             */
/*   Updated: 2023/07/11 12:13:11 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_tmp;

	i = 0;
	j = 0;
	dst_tmp = ft_strlen(dst);
	if (dstsize <= dst_tmp)
		return (dstsize + ft_strlen(src));
	while (src[j] && dst_tmp + j < dstsize - 1)
	{
		dst[dst_tmp + j] = src[j];
		j++;
	}
	dst[dst_tmp + j] = '\0';
	return (ft_strlen(src) + dst_tmp);
}
