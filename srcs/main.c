/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:47:25 by hes-saqu          #+#    #+#             */
/*   Updated: 2024/04/28 11:47:26 by hes-saqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double get_x_min_ratio(t_draw *data, double x, double y)
{
  double x_min_ratio;

  if (x > WIDTH / 2)
    x_min_ratio = fabs(2 * x / WIDTH);
  else if( x < WIDTH / 2)
    x_min_ratio = fabs((2 * x / WIDTH));
  else
    x_min_ratio = 1;
  return (x_min_ratio);
}

double get_x_max_ratio(t_draw *data, double x, double y)
{
  double x_max_ratio;
  if (x > WIDTH / 2)
    x_max_ratio = fabs((WIDTH - x) / (WIDTH / 2));
  else if (x < WIDTH / 2)
    x_max_ratio = fabs(2 * (WIDTH -x) / (WIDTH));
  else
    x_max_ratio = 1;
  return (x_max_ratio);
}

double get_y_max_ratio(t_draw *data, double x, double y)
{
  double y_max_ratio;
  if (y < HEIGHT / 2)
    y_max_ratio = (HEIGHT - y) / (HEIGHT / 2);
  else if (y >  HEIGHT / 2)
    y_max_ratio = (HEIGHT - y) / (HEIGHT / 2);
  else
    y_max_ratio = 1;
  return (y_max_ratio);
}
double get_y_min_ratio(t_draw *data, double x, double y)
{
  double y_min_ratio;
  if (y < HEIGHT / 2)
    y_min_ratio = fabs((2 * y) / HEIGHT);
  else if (y > HEIGHT / 2)
    y_min_ratio = fabs((2 * y) / HEIGHT);
  else
    y_min_ratio = 1;
  return (y_min_ratio);
}


int ft_create_img (t_draw *data)
{
  char *title_mandelbrot = "Mandelbrot Fractal";
  char *title_julia = "Julia Fractal";
  char *title;
  title = title_mandelbrot;
  if (data->is_mandelbrot == 0 || data->is_julia == 0)
  {
    if (data->is_julia == 0)
      title = title_julia;
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, title);
    if (!data->win_ptr)
      return (2);
  }
  else
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
  data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
  if(!data->img.mlx_img)
    return (2);
  data->img.addrs = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.size_line, &data->img.endian);
  return (0);
}

int ft_put_fractal(int ac, char **av, t_draw *data)
{
  data->x_max = 2;
  data->y_max = 2;
  data->x_min = -2;
  data->y_min = -2;
  data->iter = 50;
  if (data->is_julia == 0)
  {
    data->c = (t_complex){d_atoi(data->av[2]), d_atoi(data->av[3])};
    if ((data->c.real >= double max) || (data->c.img >= double max))
      return (3);  
    julia_set(data, 0x00000);
  }
  else if (data->is_mandelbrot == 0)
  {
    data->x_max = 2;
    data->x_min = -2;
    data->y_max = 2;
    data->y_min = -2;
    mandelbrot(data);
  }
  mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
  return (0);
}
int ft_events(t_draw *data)
{
    data->mlx_ptr = mlx_init();
    if (data->mlx_ptr)
      return (1);
    if (ft_create_img(data) != 0)
      return (2);
    if (ft_put_fractal(data->ac, data->av, data) != 0)
      return (3);
    mlx_mouse_hook(data->win_ptr, mouse_event, data);
    mlx_hook(data->win_ptr, 17, 0, close_win, data);
    mlx_key_hook(data->win_ptr, pressed_key_event, data);
    mlx_loop(data->mlx_ptr);
    return (0);
}
int main(int ac, char **av) 
{
    t_draw mlx_data;
    int error_code;

    mlx_data.is_julia = -1;
    mlx_data.is_mandelbrot = -1;
    mlx_data.ac = ac;
    mlx_data.av = av;  
    if (ac == 2  || ac == 4)
    {
      if (ac == 4 &&  strcmp("julia", av[1]) == 0)
        mlx_data.is_julia = 0;
      else if (ac == 2 && strcmp("mandelbrot", av[1]) == 0)
        mlx_data.is_mandelbrot = 0;
    }
    if (mlx_data.is_mandelbrot == 0 || mlx_data.is_julia == 0)
    {
        error_code = ft_events(&mlx_data);
        if(error_code != 0)
          handle_error(error_code); /*handle errors*/
    }
    else
      ft_printf(1, "Availabe parameters : \njulia real_number imaginary_number.\nmandelbrot\nBurningship\n");
    return (0);
}

void handle_error(int error_code, t_draw *data)
{
  if (error_code == 1)
    write(2, "MLX_INIT ERROR\n",15);
  else if (error_code == 2)
    write(2, "MLX_WIN ERROR\n", 15);
  else if (error_code == 3)
    write(2, "invalid argument for julia\n", 29);

}
