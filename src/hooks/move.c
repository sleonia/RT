/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 00:00:22 by thorker           #+#    #+#             */
/*   Updated: 2020/02/07 12:30:44 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		change_flag(SDL_Event event, t_move_flag *flag, char i)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_W)
		flag->w = i;
	if (event.key.keysym.scancode == SDL_SCANCODE_S)
		flag->s = i;
	if (event.key.keysym.scancode == SDL_SCANCODE_D)
		flag->d = i;
	if (event.key.keysym.scancode == SDL_SCANCODE_A)
		flag->a = i;
	if (event.key.keysym.scancode == SDL_SCANCODE_V)
		flag->v = i;
	if (event.key.keysym.scancode == SDL_SCANCODE_C)
		flag->c = i;
}

static void     check_flag(SDL_Event event, t_move_flag *flag)
{
	if (event.type == SDL_KEYDOWN)
		change_flag(event, flag, 1);
	if (event.type == SDL_KEYUP)
		change_flag(event, flag, 0);
}

static void		move_help(float *d, t_cam *cam, t_move_flag *flag)
{
	if (flag->d == 1)
	{
		d[2] -= STEP * cos(cam->phi) * sin(cam->tetta);
		d[0] += STEP * sin(cam->phi) * sin(cam->tetta);
	}
	if (flag->v == 1)
	{
		d[2] -= STEP * sin(cam->phi) * cos(cam->tetta);
		d[0] -= STEP * cos(cam->phi) * cos(cam->tetta);
		d[1] += STEP * sin(cam->tetta);
	}
	if (flag->c == 1)
	{
		d[2] += STEP * sin(cam->phi) * cos(cam->tetta);
		d[0] += STEP * cos(cam->phi) * cos(cam->tetta);
		d[1] -= STEP * sin(cam->tetta);
	}
	if (fabs(d[0]) <0.00001f && fabs(d[1]) <0.00001f && fabs(d[2]) <0.00001f)
		return ;
	cam->pos.s[2] += d[2] / sqrt(d[2] * d[2] + d[1] * d[1] + d[0] * d[0]);
	cam->pos.s[0] += d[0] / sqrt(d[2] * d[2] + d[1] * d[1] + d[0] * d[0]);
	cam->pos.s[1] += d[1] / sqrt(d[2] * d[2] + d[1] * d[1] + d[0] * d[0]);
}

void			move(SDL_Event event, t_cam *cam, t_move_flag *flag)
{
	float		d[3];

	check_flag(event, flag);
	d[2] = 0;
	d[0] = 0;
	d[1] = 0;
	if (flag->w == 1)
	{
		d[2] += STEP * sin(cam->phi) * sin(cam->tetta);
		d[0] += STEP * cos(cam->phi) * sin(cam->tetta);
		d[1] += STEP * cos(cam->tetta);
	}
	if (flag->s == 1)
	{
		d[2] -= STEP * sin(cam->phi) * sin(cam->tetta);
		d[0] -= STEP * cos(cam->phi) * sin(cam->tetta);
		d[1] -= STEP * cos(cam->tetta);
	}
	if (flag->a == 1)
	{
		d[2] += STEP * cos(cam->phi) * sin(cam->tetta);
		d[0] -= STEP * sin(cam->phi) * sin(cam->tetta);
	}
	move_help(d, cam, flag);
}
