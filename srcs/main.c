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

int	main(int ac, char **av)
{
	t_draw	mlx_data;
	int		error_code;

	mlx_data.is_julia = -1;
	mlx_data.is_mandelbrot = -1;
	mlx_data.ac = ac;
	mlx_data.av = av;
	if (ac == 2 || ac == 4)
		is_fractal(&mlx_data);
	if (mlx_data.is_mandelbrot == 0 || mlx_data.is_julia == 0)
	{
		error_code = ft_events(&mlx_data);
		if (error_code != 0)
			handle_error(error_code, &mlx_data);
	}
	else
	{
		write(1, "Availabe parameters : \njulia {real_number}", 43);
		write(1, "{imaginary_number}.\nmandelbrot\n", 32);
	}
	return (0);
}

void	handle_error(int error_code, t_draw *data)
{
	if (error_code == 1)
		write(2, "MLX_INIT ERROR\n", 15);
	else if (error_code == 2)
	{
		write(2, "MLX_WIN ERROR\n", 15);
		free(data->mlx_ptr);
	}
	exit(1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s2[i] != '\0')
		return (-1);
	else if (s1[i] != '\0')
		return (1);
	return (0);
}

void	is_fractal(t_draw *data)
{
	if (data->ac == 4 && ft_strcmp("julia", data->av[1]) == 0)
		data->is_julia = 0;
	else if (data->ac == 2 && ft_strcmp("mandelbrot", data->av[1]) == 0)
		data->is_mandelbrot = 0;
}
