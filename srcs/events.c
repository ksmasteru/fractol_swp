#include "../includes/fractol.h"

int	mouse_event(int button, int x, int y, t_draw *data)
{
	if (button == 5 || button == 4)
	{
		if (button == 5)
			zoom_in(data);
		else
			zoom_out(data);
		if (data->is_julia >= 0 || data->is_mandelbrot >= 0
			|| data->is_burningShip >= 0)
		{
			if (ft_create_img(data) == 1)
				return (1);
			if (data->is_julia >= 0)
				julia_set(data, 0xffffff);
			else if (data->is_mandelbrot >= 0)
				mandelbrot(data);
			else
				burningShip(data);
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

int	pressed_key_event(int keycode, t_draw *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	return (0);
}

double	zoom_in(t_draw *data)
{
	double	zoom_x_offset;
	double	zoom_y_offset;

	zoom_x_offset = 100 * fabs((data->x_max - data->x_min) / WIDTH);
	zoom_y_offset = 100 * fabs((data->y_max - data->y_min) / HEIGHT);
	data->x_max = (data->x_max) - zoom_x_offset;
	data->y_min = (data->y_min) + zoom_y_offset;
	data->x_min = (data->x_min) + zoom_x_offset;
	data->y_max = (data->y_max) - zoom_y_offset;
	return (0);
}
double	zoom_out(t_draw *data)
{
	double zoom_x_offset;
	double zoom_y_offset;

	zoom_x_offset = 100 * fabs((data->x_max - data->x_min) / WIDTH);
	zoom_y_offset = 100 * fabs((data->x_max - data->x_min) / HEIGHT);
	data->x_max = (data->x_max) + zoom_x_offset;
	data->y_min = (data->y_min) - zoom_y_offset;
	data->x_min = (data->x_min) - zoom_x_offset;
	data->y_max = (data->y_max) + zoom_y_offset;
}