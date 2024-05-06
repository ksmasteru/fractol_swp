/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_ratio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:18:48 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/05/06 09:18:50 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	get_x_min_ratio(double x)
{
	double	x_min_ratio;

	if (x > WIDTH / 2)
		x_min_ratio = fabs(2 * x / WIDTH);
	else if (x < WIDTH / 2)
		x_min_ratio = fabs((2 * x / WIDTH));
	else
		x_min_ratio = 1;
	return (x_min_ratio);
}

double	get_x_max_ratio(double x)
{
	double	x_max_ratio;

	if (x > WIDTH / 2)
		x_max_ratio = fabs((WIDTH - x) / (WIDTH / 2));
	else if (x < WIDTH / 2)
		x_max_ratio = fabs(2 * (WIDTH - x) / (WIDTH));
	else
		x_max_ratio = 1;
	return (x_max_ratio);
}

double	get_y_max_ratio(double y)
{
	double	y_max_ratio;

	if (y < HEIGHT / 2)
		y_max_ratio = (HEIGHT - y) / (HEIGHT / 2);
	else if (y > HEIGHT / 2)
		y_max_ratio = (HEIGHT - y) / (HEIGHT / 2);
	else
		y_max_ratio = 1;
	return (y_max_ratio);
}

double	get_y_min_ratio(double y)
{
	double	y_min_ratio;

	if (y < HEIGHT / 2)
		y_min_ratio = fabs((2 * y) / HEIGHT);
	else if (y > HEIGHT / 2)
		y_min_ratio = fabs((2 * y) / HEIGHT);
	else
		y_min_ratio = 1;
	return (y_min_ratio);
}
