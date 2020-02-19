/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccriston <ccriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:12:42 by ccriston          #+#    #+#             */
/*   Updated: 2020/02/19 21:14:29 by ccriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			redred(int color)
{
	return (((int)color >> 16) & 0xFF);
}

int			greengreen(int color)
{
	return (((int)color >> 8) & 0xFF);
}

int			blueblue(int color)
{
	return ((int)color & 0xFF);
}

float		minn(float a, float b)
{
	return ((a < b) ? b : a);
}
