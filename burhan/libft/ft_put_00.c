/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:49:45 by bhajili           #+#    #+#             */
/*   Updated: 2024/08/27 10:40:28 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
}

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, 1);
}

void	ft_putendl(char *s)
{
	ft_putendl_fd(s, 1);
}

void	ft_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
}
