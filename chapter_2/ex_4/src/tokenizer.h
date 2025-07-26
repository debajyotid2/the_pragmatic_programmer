#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <stdio.h>
#include <stdlib.h>

#define TOKEN_BUFFER_SIZE 50
#define MAX_TOKENS 1024
#define ERR_AND_EXIT(...)                                                      \
  ({                                                                           \
    fprintf(__VA_ARGS__);                                                      \
    exit(EXIT_FAILURE);                                                        \
  })

typedef struct token_t Token;
void tokens_alloc(Token **tokens);
void print_tokens(Token *tokens, int num_tokens);
void tokenize(FILE *fp, Token *tokens);

#endif
