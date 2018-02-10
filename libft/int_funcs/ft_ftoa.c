/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:33:55 by mgayduk           #+#    #+#             */
/*   Updated: 2018/02/10 14:24:16 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_pow(int base, int power)
{
	int res;

	res = base;
	if (power == 0)
		return (1);
	while (--power)
		res *= base;
	return (res);
}

char	*form_result(intmax_t ipart, long double fpart, int precision)
{
	char	*istr;
	char	*fstr;
	char	*res;

	istr = ft_itoa(ipart);
	if (precision == 0)
		return (istr);
	fstr = ft_itoa(fpart);
	res = ft_strnew(ft_strlen(istr) + ft_strlen(fstr) + 1);
	res = ft_strcat(res, istr);
	res = ft_strcat(res, ".");
	res = ft_strcat(res, fstr);
	ft_strdel(&istr);
	ft_strdel(&fstr);
	return (res);
}

char	*ft_ftoa(long double n, int precision)
{
	intmax_t		ipart;
	long double		fpart;
	int				pow;
	char			*res;

	pow = ft_pow(10, precision);
	if (n >= 0)
		n = ((intmax_t)(n * pow + 0.5)) / (pow * 1.0);
	else
		n = ((intmax_t)(n * pow - 0.5)) / (pow * 1.0);
	ipart = (intmax_t)n;
	fpart = n - (long double)ipart;
	fpart = FT_ABS(fpart);
	fpart = ((intmax_t)(fpart * pow + 0.5)) / (pow * 1.0);
	if (precision != 0)
		fpart = fpart * pow;
	res = form_result(ipart, fpart, precision);
	return (res);
}
