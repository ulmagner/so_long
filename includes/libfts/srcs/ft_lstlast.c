/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:24:01 by ulmagner          #+#    #+#             */
/*   Updated: 2024/05/22 12:27:12 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	else if (lst->next == NULL)
		return (lst);
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}
