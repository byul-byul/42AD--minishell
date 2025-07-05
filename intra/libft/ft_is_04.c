/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_04.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:35:14 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 13:51:15 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdollarsign(int c)
{
	return (c == '$');
}

int	ft_issinglequote(int c)
{
	return (c == '\'');
}

int	ft_isdoublequote(int c)
{
	return (c == '"');
}

int	ft_isopenparentheses(int c)
{
	return (c == '(');
}

int	ft_iscloseparentheses(int c)
{
	return (c == ')');
}
