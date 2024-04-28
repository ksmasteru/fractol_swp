#include "../includes/fractol.h"

int	color_value_burningShip(t_draw *data)
{
	int			i;
	t_complex	temp_z;
	t_complex	z;
	double		a;
	double		b;

	i = -1;
	z = (t_complex){0, 0};
	a = z.real * z.real;
	b = z.img * z.img;
	while ((a + b <= 4) && (++i < data->iter))
	{
		temp_z = z;
		z.real = a - b + data->c.real;
		z.img = fabs(2 * temp_z.real * temp_z.img) + data->c.img;
		a = z.real * z.real;
		b = z.img * z.img;
	}
	if (i == data->iter)
		return (0);
	return (i);
}

int	burningShip(t_draw *data)
{
	int x;
	int y;
	int i;
	char *pixel;
	int a;
	int color;

	data->is_burningShip++;
	i = -1;
	while (++i <= HEIGHT * WIDTH)
	{
		x = (i % WIDTH);
		y = (i / WIDTH);
		data->c.img = data->y_max + ((data->y_min - data->y_max)
				/ (double)HEIGHT * y);
		data->c.real = data->x_min + ((data->x_max - data->x_min)
				/ (double)WIDTH * x);
		a = color_value_burningShip(data);
		color = ((double)a / 100) * 0x00ff00 * 2;
		pixel = data->img.addrs + data->img.size_line * y + x * (data->img.bpp
				/ 8);
		*(int *)pixel = color;
	}
	return (0);
}