#include "../includes/fractol.h"

void	handle_atoi_error(void)
{
	write(1, "wrong input arguments\n", 23);
	exit(0);
}

double	get_atoi_sign(char **str)
{
	int		i;
	char	*stri;
	int		sign;

	sign = 1;
	i = 0;
	stri = *str;
	while (stri[i] == 32 || (stri[i] >= 9 && stri[i] <= 13))
		i++;
	if (stri[i] == '+' || stri[i] == '-')
	{
		if (stri[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	*str += i;
	return (sign);
}
double	get_be_point_val(char **str, double *af_point_val)
{
	double	be_point_val;
	char	*stri;
	int		i;

	be_point_val = 0;
	i = 0;
	stri = *str;
	while ((stri[i] >= '0' && stri[i] <= '9') || stri[i] == '.')
	{
		if (stri[i] == '.')
		{
			i++;
			*af_point_val = 0;
			*str += i;
			return (be_point_val);
		}
		be_point_val *= 10;
		be_point_val += stri[i] - 48;
		i++;
	}
	if (stri[i] != '\0')
		handle_atoi_error();
	return (be_point_val);
}

double	get_af_point_val(char *str)
{
	unsigned int	af_point_val;
	int				the_counter;
	int				i;
	double			res;

	res = 0;
	the_counter = 1;
	i = 0;
	af_point_val = 0;
	if (str[i] == '\0')
		handle_atoi_error();
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		the_counter *= 10;
		af_point_val *= 10;
		af_point_val += str[i++] - 48;
	}
	if (str[i] != '\0')
		handle_atoi_error();
	res = (double)af_point_val / the_counter;
	return (res);
}

double	d_atoi(char *str)
{
	double be_point_val;
	double af_point_val;
	double sign;
	double res;

	res = 0;
	af_point_val = -1;
	sign = get_atoi_sign(&str);
	be_point_val = get_be_point_val(&str, &af_point_val);
	if (af_point_val != -1)
		res += get_af_point_val(str);
	res += be_point_val;
	return (sign * res);
}