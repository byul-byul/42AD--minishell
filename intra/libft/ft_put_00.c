/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:49:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 23:20:49 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
}

void	ft_putstr(t_cchr *s)
{
	ft_putstr_fd(s, 1);
}

void	ft_putendl(t_cchr *s)
{
	ft_putendl_fd(s, 1);
}

void	ft_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
}
