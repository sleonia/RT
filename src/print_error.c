/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:09:38 by deladia           #+#    #+#             */
/*   Updated: 2019/11/08 14:09:52 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		sdl_error(char *str)
{
	ft_putendl(str);
	ft_putendl(SDL_GetError());
	exit(1);
}

void		ft_error(char *str)
{
	ft_putendl(str);
	exit(1);
}
