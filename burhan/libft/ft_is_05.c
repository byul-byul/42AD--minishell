/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_05.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:50:55 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 13:51:30 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isparentheses(int c)
{
	return (ft_isopenparentheses(c) || ft_iscloseparentheses(c));
}

int	ft_isquote(int c)
{
	return (ft_issinglequote(c) || ft_isdoublequote(c));
}
