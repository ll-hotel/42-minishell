/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:49:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/15 20:09:45 by ll-hotel         ###   ########.fr       */
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

	char	*new_line;
	int		new_len;

	if (pipe(fds) == -1)
		return (perror("here-document"), 0);
	*hd_expanded = fds[0];
	line = get_next_line(hd_input);

	while (line)
	{
		new_line = ft_calloc(1, sizeof(char));
		if (!new_line)
			return (perror("minishell"), 0);
		new_len = 1;
		name_pos = ft_strichr(line, '$');

		char	*tmp = ft_realloc(new_line, new_len, new_len + name_pos);
		if (!tmp)
			return (perror("minishell"), 0);
		new_len += name_pos;
		ft_memmove(tmp + new_len, line, name_pos);
		new_line = tmp;

		while (line[name_pos++])
		{
			name_len = measure_name_len(line + name_pos);

			char c = line[name_pos + name_len];
			line[name_pos + name_len] = 0;

			ft_dprintf(2, "{\n"\
					"  {\n"\
					"    new_line: `%s',\n    new_len: %d\n"\
					"  },\n  {\n"\
					"    name: `%s',\n    name_pos: %d,\n    name_len: %d\n"\
					"  },\n  c: `%c' (%x)\n}\n", \
					new_line, new_len,
					line + name_pos, name_pos, name_len, \
					c, (int)c);

			t_env_var *evar = env_var_get(msh, line + name_pos);
			line[name_pos + name_len] = c;

			//

			const int	value_len = ft_strlen(evar->value);
			char	*tmp = ft_realloc(new_line, new_len, new_len + value_len);
			new_len += value_len;
			if (!tmp)
				return (perror("minishell"), 0);
			ft_strlcat(tmp, evar->value, new_len);
			new_line = tmp;

			//

			name_pos += ft_strichr(line + name_pos + name_len, '$') + name_len;
		}

		ft_dprintf(fds[1], "%s\n", new_line);
		free(new_line);
		free(line);
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
