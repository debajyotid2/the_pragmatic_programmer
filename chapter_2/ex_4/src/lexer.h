#ifndef _LEXER_H_
#define _LEXER_H_

#include <stdio.h>
#include <stdlib.h>

#define ERR_AND_EXIT(...) ({\
        fprintf(__VA_ARGS__);\
        exit(EXIT_FAILURE);\
        })

typedef struct lexemes_t Lexemes;
Lexemes* lexemes_alloc(void);
void lexemes_reserve(Lexemes* lex);
void lexemes_destroy(Lexemes* lex);
void lexemes_store_lexeme(Lexemes* lex, char* lexeme, size_t length);
void lexemes_print(Lexemes* lex);
void lexer(FILE* fp, Lexemes* lexemes);

#endif
