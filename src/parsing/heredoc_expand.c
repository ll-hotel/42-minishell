/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:49:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/16 01:58:49 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup(int fds[2], int hd_input, int *hd_expanded, char **line);
static int	loop(int fd, char *line, char *evar_name, t_fptr *fstr);
static int	measure_name_len(char *name_start);

int	heredoc_expand(t_msh *msh, int hd_input, int *hd_expanded)
{
	int			fds[2];
	char		*line;
	t_fptr		fstr[1];

	setup(fds, hd_input, hd_expanded, &line);
	while (line)
	{
		ft_bzero(fstr, sizeof(*fstr));
		if (!loop(hd_input, line, NULL, fstr))
		{

		}
		free(line);
		line = get_next_line(hd_input);
	}
	close(hd_input);
	close(fds[1]);
	return (1);
}

static int	setup(int fds[2], int hd_input, int *hd_expanded, char **line)
{
	if (pipe(fds) == -1)
		return (perror("here-document"), 0);
	*hd_expanded = fds[0];
	*line = get_next_line(hd_input);
	return (1);
}

static int	loop(int fd, char *line, char *evar_name, t_fptr *fstr)
{
	ft_bzero(fstr, sizeof(*fstr));
	evar_name = ft_strtok(line, "$");
	if (evar_name != NULL)
		;
	while (evar_name)
	{
		evar_name = ft_strtok(NULL, "$");
	}
	free(fstr->p);
	free(line);
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
