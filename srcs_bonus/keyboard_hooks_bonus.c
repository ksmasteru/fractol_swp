/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:47:46 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/04/28 11:47:47 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void shift_view(int keycode, t_draw *data)
{
    double x_offset;
    
    x_offset = fabs((data->x_max - data->x_min) / WIDTH) * 100;
    if (keycode == XK_Right || keycode == XK_Left)
    {
        if (keycode == XK_Left)
        {
            data->x_max -= x_offset;
            data->x_min -= x_offset;
        }
        else
        {
            data->x_max += x_offset;
            data->x_min += x_offset;
        }
        return ;
    }
    shift_view_y(keycode, data);
}

void shift_view_y(int keycode , t_draw *data)
{
    double y_offset;

    y_offset = fabs((data->y_max - data->y_min) / HEIGHT) * 100;
    if (keycode == XK_Up || keycode == XK_Down)
    {
        if (keycode == XK_Down)
        {
            data->y_max -= y_offset;
            data->y_min -= y_offset;
        }
        else
        {
            data->y_max += y_offset;
            data->y_min += y_offset;
        }
    }
}
