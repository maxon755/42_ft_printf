/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:51:42 by mgayduk           #+#    #+#             */
/*   Updated: 2018/01/25 09:06:04 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

//__attribute__ ((unused))

/*
** Goes through the format string, looking for the % symbol
** If % was found - parse qualifier by filling stuct fq;
** Then next ap should be written on stdout;
*/

static void	init_struct(t_fq *fq)
{
	ft_memset(fq->flags, '0', 5);
	fq->flags[5] = '\0';
	fq->width = 0;
	fq->precision = -1;
	fq->size = 0;
	fq->type = '\0';
	fq->indent = 0;
}

void	perform(const char *format, va_list ap, int *count)
{
	const char	*needle;
	const char	*fiber;
	t_fq		fq;

	fiber = format;
	while ((needle = ft_strchr(fiber, '%')))
	{
		if (needle - fiber)
		{
			*count += (needle - fiber);
			write(1, fiber, needle - fiber);
		}
		init_struct(&fq);
		parse_qualifier(needle, &fq, ap);
		form_output(ap, &fq);
		*count += write(1, fq.str_out, ft_strlen(fq.str_out));
		ft_strdel(&(fq.str_out));
		needle += fq.indent;
		fiber = needle;
	}
	write(1, fiber, ft_strlen(fiber));
	*count += ft_strlen(fiber);
}

int		ft_printf(const char *format, ...)
{
	va_list ap;
	int		count;

	count = 0;
	va_start(ap, format);
	perform(format, ap, &count);
	va_end(ap);
	return (count);
}
