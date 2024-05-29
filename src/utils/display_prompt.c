/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:17:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 03:38:20 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pwd_prompt(void);
static int	is_only_space(char *str);

char	*display_prompt(void)
{
	char	*input;
	char	*prompt;

	prompt = pwd_prompt();
	input = readline(prompt);
	free(prompt);
	if (input && !is_only_space(input))
	{
		add_history(input);
		return (input);
	}
	return (input);
}

static char	*pwd_prompt(void)
{
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	temp = ft_strjoin("\001\e[96m\e[1m\002📂 ", ft_strrchr(pwd, '/') + \
			(pwd[1] != 0));
	free(pwd);
	pwd = ft_strjoin(temp, "\001\e[0m\e[39m\002 ➜ ");
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
