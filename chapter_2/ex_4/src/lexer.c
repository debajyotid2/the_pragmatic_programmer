#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

#define TOKEN_BUFFER_SIZE 50
#define LEXEME_BUFFER_SIZE 50

typedef enum TokenType
{
    D, W, N, E, S, U
} TokenType;

typedef struct lexemes_t
{
    size_t num_lexemes;
    char** lexemes;
} Lexemes;

Lexemes* lexemes_alloc(void)
{
    Lexemes* lexeme_store = (Lexemes *)malloc(sizeof(Lexemes));;
    lexeme_store->num_lexemes = 0;
    lexeme_store->lexemes = (char **)calloc(LEXEME_BUFFER_SIZE, sizeof(char *));
    return lexeme_store;
}

void lexemes_reserve(Lexemes* lex)
{
    if (lex==NULL) 
        ERR_AND_EXIT(stderr, "%s: Null value in pointer.\n", __func__);
    if (lex->num_lexemes==LEXEME_BUFFER_SIZE)
        lex->lexemes = (char **)realloc(lex->lexemes, LEXEME_BUFFER_SIZE*sizeof(char *));
}

void lexemes_destroy(Lexemes* lex)
{
    if (lex==NULL) 
        ERR_AND_EXIT(stderr, "%s: Null value in pointer.\n", __func__);
    for (size_t i=0; i<lex->num_lexemes; i++)
    {
        free(lex->lexemes[i]);
        lex->lexemes[i] = NULL;
    }
    free(lex->lexemes);
    free(lex);
}

void lexemes_store_lexeme(Lexemes* lex, char* lexeme, size_t length)
{
    if (lex==NULL || lexeme==NULL) 
        ERR_AND_EXIT(stderr, "%s: Null value in pointer.\n", __func__);
    lex->lexemes[lex->num_lexemes] = (char *)calloc(length+1, sizeof(char));
    memcpy(lex->lexemes[lex->num_lexemes], lexeme, (length+1)*sizeof(char));
    lex->num_lexemes++;
}

void lexemes_print(Lexemes* lex)
{
    if (lex==NULL) 
        ERR_AND_EXIT(stderr, "%s: Null value in pointer.\n", __func__);
    for (size_t i=0; i<lex->num_lexemes; ++i)
        printf("%lu. %s\n", i+1, lex->lexemes[i]);
}

void lexer(FILE* fp, Lexemes* lexemes)
{
    int buf_pos = 0;
    char c;
    char* buffer = (char *)calloc(TOKEN_BUFFER_SIZE, sizeof(char));

    if (fp==NULL || lexemes==NULL)
        ERR_AND_EXIT(stderr, "%s: Received a null ptr.\n", __func__);

    // Parse lexemes
    while ((c=getc(fp)) != EOF)
    {
        // Ensure enough space exists for the entire token
        if (buf_pos==TOKEN_BUFFER_SIZE)
            buffer = (char *)realloc(buffer, TOKEN_BUFFER_SIZE*sizeof(char));

        // End of token
        if (isspace(c))
        {
            // Ensure enough space exists for all lexemes
            lexemes_reserve(lexemes);

            buffer[buf_pos] = '\0';
            lexemes_store_lexeme(lexemes, buffer, buf_pos);

            // Allocate new buffer
            buf_pos = 0;
            continue;
        }
        buffer[buf_pos] = c;
        buf_pos++;
    }

    if (buffer!=NULL)
        free(buffer);
}
