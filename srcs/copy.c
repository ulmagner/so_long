/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:31:44 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/24 14:32:02 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	dst = image->addr \
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_image *image, int x, int y)
{
	char	*src;

	src = image->addr \
		+ ((y * image->line_length) + (x * image->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}
