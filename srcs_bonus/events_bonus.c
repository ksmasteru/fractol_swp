#include "../includes/fractol.h"

int mouse_event(int button, int x, int y, t_draw *data)
{
  if (button == 5 || button == 4)
  {
    if (button == 5)
      zoom_in_bonus(x, y, button, data);
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

int close_win(t_draw *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
		exit(0);
}

int pressed_key_event(int keycode, t_draw *data)
{
  double shift_value;
  if (keycode == XK_Escape)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
		exit(0);
	}
  if (keycode == XK_Right || keycode == XK_Left || keycode == XK_Up || keycode == XK_Down)
    shift_view(keycode, data);
  if (keycode == XK_1)
    data->iter += 50;
  if (keycode == XK_2)
  {
    if (data->iter > 50)
      data->iter -= 50;
  }
  if (data->is_julia  >= 0 || data->is_mandelbrot >= 0) 
  {
    ft_create_img(data);
    if (data->is_julia >= 0)
      julia_set(data, 0xffffff);
    else
      mandelbrot(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
  }
	return (0);
}

double zoom_in(t_draw *data)
{
  double zoom_x_offset = 10 * fabs((data->x_max - data->x_min) / WIDTH);
  double zoom_y_offset = 10 * fabs((data->y_max - data->y_min) / HEIGHT);

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

  zoom_x_offset = 10 * fabs((data->x_max - data->x_min) / WIDTH);
  zoom_y_offset = 10 * fabs((data->x_max - data->x_min) / HEIGHT); 
  data->x_max = (data->x_max) + zoom_x_offset;
  data->y_min = (data->y_min) - zoom_y_offset;
  data->x_min = (data->x_min) - zoom_x_offset;
  data->y_max = (data->y_max) + zoom_y_offset;
  return (0);
}
double zoom_in_bonus(int x, int y, int button, t_draw *data)
{
  double x_max_offset;
  double x_min_offset;
  double y_max_offset;
  double y_min_offset;

  double x_max_ratio = get_x_max_ratio(data, x, y);
  double x_min_ratio = get_x_min_ratio(data, x, y);
  double y_min_ratio = get_y_min_ratio(data, x, y);
  double y_max_ratio = get_y_max_ratio(data, x, y);

  x_max_offset = 10 * x_max_ratio * fabs((data->x_max - data->x_min) / WIDTH);
  x_min_offset = 10 * x_min_ratio * fabs((data->x_max - data->x_min) / WIDTH);
  y_min_offset = 10 * y_max_ratio * fabs((data->y_max - data->y_min) / HEIGHT);
  y_max_offset = 10 * y_min_ratio * fabs((data->y_max - data->y_min) / HEIGHT);

  data->x_max -= x_max_offset;
  data->x_min += x_min_offset;
  data->y_max -= y_max_offset;
  data->y_min += y_min_offset;
  return (0);
}


