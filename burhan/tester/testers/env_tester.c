/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:33:24 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/23 12:48:44 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

int g_test_num = 1;
int g_failed_tests[1024];
int g_failed_count = 0;

void	env_run_test(const char *key, const char *value, const char *new_value)
{
	t_env	*env = env_init((char *[]){"HOME=/home/user", "PATH=/usr/bin", NULL});
	char	*result;
	
	printf(BLUE "\nEnv test_%d " RESET, g_test_num);
	printf("(Set: %s=%s, Update: %s)\n", key, value, new_value);
	env_set(env, key, value);
	result = env_get(env, key);
	if (!result || strcmp(result, value) != 0)
	{
		printf(RED "❌ FAIL\n" RESET);
		printf("Expected: %s, Got: %s\n", value, result ? result : "NULL");
		g_failed_tests[g_failed_count++] = g_test_num++;
		env_free(env);
		return;
	}
	if (new_value)
		env_set(env, key, new_value);
	result = env_get(env, key);
	if ((new_value && strcmp(result, new_value) != 0) || (!new_value && strcmp(result, value) != 0))
	{
		printf(RED "❌ FAIL after update\n" RESET);
		printf("Expected: %s, Got: %s\n", new_value ? new_value : value, result ? result : "NULL");
		g_failed_tests[g_failed_count++] = g_test_num++;
		env_free(env);
		return;
	}
	printf(GREEN "✅ Ok\n" RESET);
	env_free(env);
	g_test_num++;
}

void	env_test_array_sync(void)
{
	t_env	*env = env_init((char *[]){"FOO=123", NULL});
	char	**envp = env_to_envp_array(env);
	char	*expected = "FOO=123";

	printf(BLUE "\nEnv test_%d (env_to_envp_array)\n" RESET, g_test_num);
	if (!envp || !envp[0] || strcmp(envp[0], expected) != 0 || envp[1] != NULL)
	{
		printf(RED "❌ FAIL\n" RESET);
		printf(YELLOW "Expected array:\n" RESET);
		printf("  %s\n", expected);
		printf(YELLOW "Actual array:\n" RESET);
		if (!envp)
			printf("  NULL\n");
		else
		{
			for (int i = 0; envp[i]; i++)
				printf("  %s\n", envp[i]);
		}
		g_failed_tests[g_failed_count++] = g_test_num++;
	}
	else
	{
		printf(GREEN "✅ Ok\n" RESET);
		g_test_num++;
	}
	env_free(env);
}

void	env_report_failed_tests(void)
{
	if (g_failed_count == 0)
	{
		printf(GREEN "\nALL ENV TESTS PASSED!\n\n" RESET);
		return;
	}
	printf(RED "\n❌ Failed ENV test cases:\n" RESET);
	for (int i = 0; i < g_failed_count; i++)
		printf(RED "❌ test_%d\n" RESET, g_failed_tests[i]);
}

int	main(void)
{
	env_run_test("VAR1", "abc", NULL);
	env_run_test("VAR2", "123", "789");
	env_run_test("PATH", "/bin", "/usr/local/bin");
	env_test_array_sync();
	env_report_failed_tests();
	return (0);
}
