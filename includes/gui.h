/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:40:57 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/07 00:29:59 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "rt.h"

// enum					e_radio_opt
// {
// 	Easy,
// 	Hard
// };

// typedef struct			s_my_nkc_app
// {
// 	struct nkc			*nkcHandle;
// 	float				value;
// 	enum e_radio_opt	op;
// }						t_my_nkc_app;

enum radioOptions {
    EASY,
    HARD
};

struct my_nkc_app {
    struct nkc* nkcHandle;

    /* some user data */
    float value;
    enum radioOptions op;
};

#endif
