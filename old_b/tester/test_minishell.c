#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

// ======= Вспомогательные структуры для тестов =======
typedef struct s_expected_token {
    char *value;
    int type;
} t_expected_token;

typedef struct s_test_case {
    char *input;
    t_expected_token *expected;
    int expected_count;
} t_test_case;

// ======= Сравнение токенов =======
int compare_tokens(t_token *actual, t_expected_token *expected, int count) {
    for (int i = 0; i < count; i++) {
        if (!actual) {
            printf("❌ Token %d: missing token\n", i);
            return 0;
        }
        if (strcmp(actual->value, expected[i].value) != 0 || actual->type != expected[i].type) {
            printf("❌ Token %d: expected [%s, %d], got [%s, %d]\n",
                   i, expected[i].value, expected[i].type, actual->value, actual->type);
            return 0;
        }
        actual = actual->next;
    }
    if (actual) {
        printf("❌ Extra tokens found after expected count.\n");
        return 0;
    }
    return 1;
}

// ======= Запуск одного теста =======
void run_test(t_test_case *test, int index) {
    t_token *tokens = lexer(test->input);

    printf("🔹 Test %d: \"%s\"\n", index + 1, test->input);
    if (compare_tokens(tokens, test->expected, test->expected_count))
        printf("✅ Passed\n\n");
    else
        printf("❌ Failed\n\n");

    free_tokens(tokens);
}

// ======= Запуск всех тестов =======
void run_all_tests(t_test_case *tests, int count) {
    for (int i = 0; i < count; i++)
        run_test(&tests[i], i);
}

// ======= Main =======
int main(void) {
    // ======= Примеры тестов =======
    t_expected_token test1_tokens[] = {
        {"echo", T_WORD}, {"hello", T_WORD}, {"|", T_PIPE},
        {"grep", T_WORD}, {"x", T_WORD}
    };

    t_expected_token test2_tokens[] = {
        {"(", T_LPAREN}, {"ls", T_WORD}, {"&&", T_AND},
        {"echo", T_WORD}, {"done", T_WORD}, {")", T_RPAREN}
    };

    t_test_case tests[] = {
        {"echo hello | grep x", test1_tokens, 5},
        {"(ls && echo done)", test2_tokens, 6}
    };

    run_all_tests(tests, sizeof(tests) / sizeof(tests[0]));
    return 0;
}
