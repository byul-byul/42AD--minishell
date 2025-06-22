/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:13:52 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/22 11:57:43 by bhajili          ###   ########.fr       */
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

// Инициализация и очистка
t_env	*env_init(char **envp);
void	env_free(t_env *env);

// Получение и изменение переменных
char	*env_get(t_env *env, const char *key);
int		env_set(t_env *env, const char *key, const char *value);
int		env_unset(t_env *env, const char *key);

// Преобразование в формат, совместимый с execve()
char	**env_to_envp_array(t_env *env);

// Отладочная функция
void	env_print(t_env *env);

#endif