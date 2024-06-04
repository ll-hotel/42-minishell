/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:10:17 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/04 12:43:41 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expand(t_msh *msh, char *line, char *name)
{
	char		*wtf;
	char		c;
	int			wtf_len;
	int			name_len;
	t_env_var	*evar;

	name_len = 1;
	while (ft_isalnum(name[name_len]))
		name_len += 1;
	c = name[name_len];
	name[name_len] = 0;
	evar = env_var_get(msh, name + 1);
	name[name_len] = c;
	wtf_len = ft_strlen(line) - name_len + 1;
	if (evar)
		wtf_len += ft_strlen(evar->value);
	wtf = ft_calloc(wtf_len, sizeof(*wtf));
	if (!wtf)
		return (NULL);
	name[0] = 0;
	ft_strlcat(wtf, line, wtf_len);
	if (evar)
		ft_strlcat(wtf, evar->value, wtf_len);
	ft_strlcat(wtf, name + name_len, wtf_len);
	return (wtf);
}
