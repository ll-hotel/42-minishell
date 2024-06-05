/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:22:21 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/04 22:20:46 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static _Bool	_is_in_set(char c, const char *_set)
{
	char	*set;

	set = (char *)_set;
	while (*set && *set != c)
		set++;
	return (*set == c);
}

static char	*_end_of(const char *_str)
{
	char	*str;

	str = (char *)_str;
	while (*str)
		str++;
	return (str);
}

static void	_strcpy(char *dest, char *start, char *end)
{
	while (start < end && *start)
		*dest++ = *start++;
}

char	*ft_strtrim(const char *str, const char *set)
{
	char	*trimmed;
	char	*start;
	char	*end;
	_Bool	end_in_set;

	if (!str)
		return (NULL);
	start = (char *)str;
	while (*start && _is_in_set(*start, set))
		start++;
	end = _end_of(str);
	while (end > start && _is_in_set(*end, set))
		end--;
	trimmed = 0;
	if (start <= end)
	{
		end_in_set = _is_in_set(*end, set);
		trimmed = malloc(sizeof(char) * (end - start + 1 + (start != end
						|| !end_in_set)));
		if (!trimmed)
			return (0);
		_strcpy(trimmed, start, end + 1);
		trimmed[end - start + (start != end || !end_in_set)] = 0;
	}
	return (trimmed);
}
