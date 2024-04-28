/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:48:06 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/04/28 11:48:07 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	scale(double input, double output_start, double output_end,
		double input_end)
{
	double	scaled_value;
	double	slope;

	slope = 1.0 * (output_end - output_start) / (input_end);
	scaled_value = output_start + (slope * input);
	return (scaled_value);
}

int	calculate_color_value(int x, int y, t_draw *data)
{
	int			i;
	t_complex	square_z;
	t_complex	z;
	double		a;
	double		b;
	double		tmp;

	i = 0;
	z.real = data->x_min + ((data->x_max - data->x_min) / (double)(WIDTH)*x);
	z.img = data->y_max + ((data->y_min - data->y_max) / (double)HEIGHT * y);
	a = z.real * z.real;
	b = z.img * z.img;
	tmp = a + b;
	while ((a + b) < 4 && i++ < data->iter)
	{
		square_z = z;
		z.real = (a - b) + data->c.real;
		z.img = (2 * square_z.real * square_z.img) + data->c.img;
		a = z.real * z.real;
		b = z.img * z.img;
	}
	if (i == data->iter)
		return (0);
	return (i);
}

int	julia_set(t_draw *data, int color)
{
	int		x;
	int		y;
	int		i;
	char	*pixel;
	int		a;

	data->is_julia++;
	i = -1;
	while (++i <= HEIGHT * WIDTH)
	{
		x = (i % WIDTH);
		y = (i / WIDTH);
		a = calculate_color_value(x, y, data);
		color = ((double)a / 100) * 0x00ffff * 2;
		pixel = data->img.addrs + data->img.size_line * y + x * (data->img.bpp
				/ 8);
		*(int *)pixel = color;
	}
	return (0);
}
