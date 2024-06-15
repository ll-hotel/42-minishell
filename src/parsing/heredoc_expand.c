/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:49:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/15 19:00:18 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	measure_name_len(char *name_start);

int	heredoc_expand(t_msh *msh, int hd_input, int *hd_expanded)
{
	int		fds[2];
	int		name_pos;
	int		name_len;
	char	*line;

	if (pipe(fds) == -1)
		return (perror("here-document"), 0);
	*hd_expanded = fds[0];
	line = get_next_line(hd_input);

	while (line)
	{
		name_pos = ft_strichr(line, '$');

		while (line[name_pos])
		{
			name_len = measure_name_len(line + name_pos + 1);

			char c = line[name_pos + 1 + name_len];
			line[name_pos + 1 + name_len] = 0;
			t_env_var *evar = env_var_get(msh, line + name_pos + 1);
			line[name_pos + 1 + name_len] = c;

			//

			const int	line_len = ft_strlen(line);
			const int	value_len = ft_strlen(evar->value);
			char	*new_line = ft_calloc(line_len - name_len + value_len, sizeof(char));

			if (!new_line)
				return (perror("minishell"), 0);



			//

			name_pos = ft_strichr(line + name_pos + 1 + name_len, '$');
		}

		ft_dprintf(fds[1], "%s\n", line);
		line = get_next_line(hd_input);
	}

	close(hd_input);
	close(fds[1]);

	(void)msh;
	return (1);
}

static int	measure_name_len(char *name_start)
{
	int	name_len;

	name_len = 0;
	while (ft_isalnum(name_start[name_len]))
		name_len += 1;
	return (name_len);
}
