#include "../includes/fractol.h"

int mouse_event(int button, int x, int y, t_draw *data)
{
  if (button == 2 || button == 1)
  {
    if (button == 2)
      zoom_in(x, y, button, data);
    else
      zoom_out(data);
  }
  if (data->is_julia  >= 0)
  {
    if (ft_create_img(data) == 1)
      return (1);
    julia_set(data, 0xffffff);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
  }
  else if (data->is_mandelbrot >= 0)
  {
    if (ft_create_img(data) == 1)
      return (1);
    mandelbrot(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
  }
  return (0);
}

int close_win(int keycode, t_draw *draw)
{
	exit(0);
	return (0);
}

int pressed_key_event(int keycode, t_draw *data)
{
  if (keycode == XK_Escape)
	{
    free(data->mlx_ptr);/*linux*/
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

double zoom_in(t_draw *data)
{
  double zoom_x_offset;
  double zoom_y_offset;

  zoom_x_offset = 100 * fabs((data->x_max - data->x_min) / WIDTH);
  zoom_y_offset = 100 * fabs((data->y_max - data->y_min) / HEIGHT);
  data->x_max = (data->x_max) - zoom_x_offset;
  data->y_min = (data->y_min) + zoom_y_offset;
  data->x_min = (data->x_min) + zoom_x_offset;
  data->y_max = (data->y_max) - zoom_y_offset;
  return (0);
}
double zoom_out(t_draw *data)
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


