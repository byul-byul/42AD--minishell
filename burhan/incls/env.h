/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:13:52 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/25 09:21:08 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}				t_env_var;

typedef struct s_env
{
	t_env_var	*var_list;
	char		**envp;
	size_t		size;
	int			is_actual;
}			t_env;

t_env	*env_init(char **envp);
char	*env_getvalue(t_env *env, const char *key);
void	env_free(t_env *env);
int		env_remove_envvar(t_env *env, const char *key);
char	**env_to_envp_array(t_env *env);
void	env_print(t_env *env);

#endif