/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:13:52 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 20:42:30 by bhajili          ###   ########.fr       */
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
	int			last_status;
}			t_env;

t_env		*env_init(char **envp);
t_env_var	*env_varinit(char *keyvalue);
char		**env_reassemble_envp(t_env *env);
int			env_varlist_add(t_env *env, t_env_var *envvar);
int			env_varlist_push(t_env_var **head, t_env_var *envvar);
int			env_varlist_remove(t_env *env, const char *key);
int			env_varlist_pop(t_env_var **head, const char *key);
char		*env_getvalue(t_env *env, const char *key);
void		env_free(t_env *env);
void		free_envvar(t_env_var *envvar);
void		env_print(t_env *env, int print_empty_var);
int			env_setvalue(t_env *env, const char *key, char *value);

#endif