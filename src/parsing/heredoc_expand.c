/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:49:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 01:55:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static void	loop(t_ch *ch, char *line, int fd_out);

int	heredoc_expand(t_ch *ch, int hd_input, int *hd_expanded)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (perror("here-document"), 0);
	*hd_expanded = fds[0];
	line = get_next_line(hd_input);
	while (line)
	{
		loop(ch, line, fds[1]);
		free(line);
		line = get_next_line(hd_input);
	}
	close(hd_input);
	close(fds[1]);
	return (1);
}

static void	loop(t_ch *ch, char *line, int fd_out)
{
	t_evar	*evar;
	char		*evar_name;
	int			name_len;
	char		c;

	evar_name = ft_strtok(line, "$");
	if (evar_name == line)
		evar_name = ft_strtok(NULL, "$");
	while (evar_name)
	{
		if (line + 1 < evar_name)
			ft_dprintf(fd_out, "%s", line);
		name_len = 0;
		while (ft_isalnum(evar_name[name_len]))
			name_len += 1;
		c = evar_name[name_len];
		evar_name[name_len] = 0;
		evar = evar_get(ch, evar_name);
		evar_name[name_len] = c;
		if (evar && evar->value)
			ft_dprintf(fd_out, "%s", evar->value);
		line = evar_name + name_len;
		evar_name = ft_strtok(NULL, "$");
	}
	ft_dprintf(fd_out, "%s", line);
}
