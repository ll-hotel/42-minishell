/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:17:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/20 19:44:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static char	*get_input(t_ch *ch);
static char	*pwd_prompt(t_ch *ch);
static int	is_only_space(char *str);

char	*display_prompt(t_ch *ch)
{
	char	*input;

	input = get_input(ch);
	if (input && !is_only_space(input))
	{
		add_history(input);
		return (input);
	}
	return (input);
}

static char	*get_input(t_ch *ch)
{
	char	*line;
	char	*input;
	char	*prompt;

	input = NULL;
	if (isatty(0))
	{
		prompt = pwd_prompt(ch);
		if (prompt)
		{
			input = readline(prompt);
			free(prompt);
		}
	}
	else
	{
		line = get_next_line(0);
		input = ft_strtrim(line, "\n");
		if (line)
			free(line);
	}
	return (input);
}

static char	*pwd_prompt(t_ch *ch)
{
	const char	*prefix = "\001\e[96m\e[1m\002📂 ";
	const char	*suffix = " ➜ \001\e[0m\e[39m\002";
	char		*pwd;
	char		*temp;

	pwd = get_pwd(ch);
	if (pwd)
		temp = ft_strjoin(prefix, ft_strrchr(pwd, '/') + (pwd[1] != 0));
	else
		temp = ft_strjoin(prefix, "CPT");
	ft_free(pwd);
	if (!temp)
	{
		perror("miniChell: prompt");
		return (NULL);
	}
	pwd = ft_strjoin(temp, suffix);
	free(temp);
	return (pwd);
}

static int	is_only_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
