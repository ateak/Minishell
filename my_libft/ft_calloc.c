/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:57:20 by cpollito          #+#    #+#             */
/*   Updated: 2022/05/17 16:57:46 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buff;

	if (size > (size_t)-1 / count)
		return (NULL);
	buff = (void *)malloc(count * size);
	if (!buff)
		return (NULL);
	ft_bzero(buff, (count * size));
	return (buff);
}
