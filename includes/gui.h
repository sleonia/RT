/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:40:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/08 07:42:06 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <stdbool.h>
# include "rt.h"

typedef struct      s_gui
{
	bool            render_text;
	char			*input_text;
	char			*new_input_text;
}                   t_gui;

#endif
