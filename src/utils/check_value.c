/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 21:30:49 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/19 15:11:27 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		check_phi(double input_phi)
{
	if (input_phi >= 0.0 && input_phi <= 360.0)
		return (input_phi);
	return (90.0);
}

double		check_tetta(double input_tetta)
{
	if (input_tetta >= 0.0 && input_tetta <= 360.0)
		return (input_tetta);
	return (90.0);
}

int			check_skybox(int input_skybox, int texture_cnt)
{
	if (input_skybox >= -1 && input_skybox < texture_cnt)
		return (input_skybox);
	return (-1);
}

double		check_ambient(double input_ambient)
{
	if (input_ambient >= 0.1 && input_ambient <= 1.0)
		return (input_ambient);
	return (1.0);
}

int			check_fsaa(int input_fsaa)
{
	if (input_fsaa >= 2 && input_fsaa <= 6)
		return (input_fsaa);
	return (0);
}
