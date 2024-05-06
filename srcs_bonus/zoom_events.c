/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:12:26 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/05/06 09:12:28 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	zoom_in(t_draw *data)
{
	double	zoom_x_offset;
	double	zoom_y_offset;

	zoom_x_offset = 20 * fabs((data->x_max - data->x_min) / WIDTH);
	zoom_y_offset = 20 * fabs((data->y_max - data->y_min) / HEIGHT);
	data->x_max = (data->x_max) - zoom_x_offset;
	data->y_min = (data->y_min) + zoom_y_offset;
	data->x_min = (data->x_min) + zoom_x_offset;
	data->y_max = (data->y_max) - zoom_y_offset;
	return (0);
}

double	zoom_out(t_draw *data)
{
	double	zoom_x_offset;
	double	zoom_y_offset;

	zoom_x_offset = 15 * fabs((data->x_max - data->x_min) / WIDTH);
	zoom_y_offset = 15 * fabs((data->x_max - data->x_min) / HEIGHT);
	data->x_max = (data->x_max) + zoom_x_offset;
	data->y_min = (data->y_min) - zoom_y_offset;
	data->x_min = (data->x_min) - zoom_x_offset;
	data->y_max = (data->y_max) + zoom_y_offset;
	return (0);
}

double	zoom_in_bonus(int x, int y, int button, t_draw *data)
{
	double	x_max_offset;
	double	x_min_offset;
	double	y_max_offset;
	double	y_min_offset;

	button++;
	x_max_offset = 20 * get_x_max_ratio(x) * fabs((data->x_max - data->x_min)
			/ WIDTH);
	x_min_offset = 20 * get_x_min_ratio(x) * fabs((data->x_max - data->x_min)
			/ WIDTH);
	y_min_offset = 20 * get_y_max_ratio(y) * fabs((data->y_max - data->y_min)
			/ HEIGHT);
	y_max_offset = 20 * get_y_min_ratio(y) * fabs((data->y_max - data->y_min)
			/ HEIGHT);
	data->x_max -= x_max_offset;
	data->x_min += x_min_offset;
	data->y_max -= y_max_offset;
	data->y_min += y_min_offset;
	return (0);
}
