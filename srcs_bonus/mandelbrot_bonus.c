/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:45:58 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/04/28 11:46:01 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int calculate_color_value_mandelbrot(t_draw *data)
{
    int i;
    t_complex temp_z;
    t_complex z;
    double a;
    double b;

    i = -1;
    z = (t_complex){0, 0};
    a = z.real * z.real;
    b = z.img * z.img;
    while ((a + b <= 4) && (++i < data->iter))
    {
        temp_z = z;
        z.real = a - b  + data->c.real;
        z.img = 2 * temp_z.real * temp_z.img + data->c.img;
        a = z.real * z.real;
        b = z.img * z.img;
    }
    if (i == data->iter)
        return (0);
    return (i);
}

int mandelbrot(t_draw *data)
{
    int x;
    int y;
    char *pixel;
    int i;
    int a;

    data->is_mandelbrot++;
    i = -1;
    while (++i <= HEIGHT * WIDTH)
    {
        x = (i % WIDTH);
        y = (i / HEIGHT);
        data->c.img = data->y_max + ((data->y_min - data->y_max) / (double)HEIGHT * y);
        data->c.real = data->x_min + ((data->x_max  - data->x_min) / (double) WIDTH * x);
        a = calculate_color_value_mandelbrot(data);
        pixel = data->img.addrs + data->img.size_line * y + x * (data->img.bpp / 8);
        *(int *)pixel = a * 0x10100525;
    }
    return 0;
}
