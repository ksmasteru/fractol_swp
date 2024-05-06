/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:09:02 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/05/06 09:09:12 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mouse_event(int button, int x, int y, t_draw *data)
{
	x++;
	y++;
	if (button == 5 || button == 4)
	{
		if (button == 5)
			zoom_in_bonus(x, y, button, data);
		else
			zoom_out(data);
		if (data->is_julia >= 0 || data->is_mandelbrot >= 0
			|| data->is_burningship >= 0)
		{
			if (ft_create_img(data) == 1)
				return (1);
			if (data->is_julia >= 0)
				julia_set(data, 0xffffff);
			else if (data->is_mandelbrot >= 0)
				mandelbrot(data);
			else
				burningship(data);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img.mlx_img, 0, 0);
		}
	}
	return (0);
}

int	close_win(t_draw *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	handle_view_iteration(int keycode, t_draw *data)
{
	if (keycode == XK_1)
		data->iter += 50;
	if (keycode == XK_2)
		if (data->iter > 50)
			data->iter -= 50;
	if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Right
		|| keycode == XK_Left)
		shift_view(keycode, data);
}

int	pressed_key_event(int keycode, t_draw *data)
{
	if (keycode == XK_Escape || keycode == XK_Right || keycode == XK_Left
		|| keycode == XK_Up || keycode == XK_Down || keycode == XK_1
		|| keycode == XK_2)
	{
		if (keycode == XK_Escape)
			close_win(data);
		if (keycode == XK_Right || keycode == XK_Left || keycode == XK_Up
			|| keycode == XK_Down || keycode == XK_1 || keycode == XK_2)
			handle_view_iteration(keycode, data);
		if (data->is_julia >= 0 || data->is_mandelbrot >= 0
			|| data->is_burningship >= 0)
		{
			ft_create_img(data);
			if (data->is_julia >= 0)
				julia_set(data, 0xffffff);
			else if (data->is_mandelbrot >= 0)
				mandelbrot(data);
			else
				burningship(data);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img.mlx_img, 0, 0);
		}
	}
	return (0);
}
