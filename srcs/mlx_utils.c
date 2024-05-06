/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 08:57:51 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/05/06 08:57:53 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_create_img(t_draw *data)
{
	char	*title;

	if (data->is_mandelbrot == 0 || data->is_julia == 0)
	{
		if (data->is_julia == 0)
			title = "julia Fractal";
		else if (data->is_mandelbrot == 0)
			title = "Mandelbrot Fractal";
		data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, title);
		if (!data->win_ptr)
			return (2);
	}
	else
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img.mlx_img)
		return (2);
	data->img.addrs = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.size_line, &data->img.endian);
	return (0);
}

int	ft_put_fractal(t_draw *data)
{
	data->x_max = 2;
	data->y_max = 2;
	data->x_min = -2;
	data->y_min = -2;
	data->iter = 50;
	if (data->is_julia >= 0)
		julia_set(data, 0x00000);
	else if (data->is_mandelbrot == 0)
	{
		data->x_max = 0.47;
		data->y_max = 1.12;
		data->y_min = -1.12;
		mandelbrot(data);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0,
		0);
	return (0);
}

int	ft_events(t_draw *data)
{
	if (data->is_julia >= 0)
		data->c = (t_complex){d_atoi(data->av[2]), d_atoi(data->av[3])};
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	if (ft_create_img(data) != 0)
		return (2);
	if (ft_put_fractal(data) != 0)
		return (3);
	mlx_mouse_hook(data->win_ptr, mouse_event, data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_key_hook(data->win_ptr, pressed_key_event, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
