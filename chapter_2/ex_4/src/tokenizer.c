#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

typedef enum TokenType {
  Down,
  West,
  North,
  East,
  South,
  Up,
  Pen,
  Units,
  Nil,
  Comment
} TokenType;

typedef struct token_t {
  TokenType type;
  char token[TOKEN_BUFFER_SIZE];
} Token;

void tokens_alloc(Token **tokens) {
  if (tokens == NULL) {
    ERR_AND_EXIT(stderr, "%s: Received a null ptr.\n", __func__);
  }
  *tokens = (Token *)calloc(MAX_TOKENS, sizeof(Token));
}


void print_tokentype(TokenType type) {
    switch (type) {
      case Comment:
        printf("Comment");
        break;
      case Pen:
        printf("Pen");
        break;
      case Up:
        printf("Up");
        break;
      case Down:
        printf("Down");
        break;
      case East:
        printf("East");
        break;
      case West:
        printf("West");
        break;
      case North:
        printf("North");
        break;
      case South:
        printf("South");
        break;
      case Units:
        printf("Units");
        break;
      default:
        break;
    }
}

void print_tokens(Token *tokens, int num_tokens) { 
  if (tokens == NULL) {
    ERR_AND_EXIT(stderr, "%s: Received a null ptr.\n", __func__);
  }         
  for (int i = 0; i < num_tokens; ++i) {
    if (strlen(tokens[i].token) == 0) {
      continue;
    }
    print_tokentype(tokens[i].type);
    printf(": %s\n", tokens[i].token);
  }
}

void tokenize(FILE *fp, Token *tokens) {
  int buf_pos = 0, token_count = 0, line_no = 1;
  char c;
  char buffer[TOKEN_BUFFER_SIZE];

  if (fp == NULL || tokens == NULL) {
    ERR_AND_EXIT(stderr, "%s: Received a null ptr.\n", __func__);
  }

  TokenType curr_token = Nil, prev_token = Nil;

  // Parse tokens
  while ((c = getc(fp)) != EOF) {
    // Ensure enough space exists for the entire token
    if (buf_pos == TOKEN_BUFFER_SIZE) {
      ERR_AND_EXIT(stderr,
                   "%s: Ran out of space in buffer. Increase default token "
                   "buffer size.\n",
                   __func__);
    }

    // Tokenize!
    if (prev_token != Comment && curr_token != Comment) {
      // Parse non-comment character
      switch (c) {
      case '#':
        curr_token = Comment;
        break;
      case 'P':
        curr_token = Pen;
        break;
      case 'U':
        curr_token = Up;
        break;
      case 'D':
        curr_token = Down;
        break;
      case 'E':
        curr_token = East;
        break;
      case 'W':
        curr_token = West;
        break;
      case 'N':
        curr_token = North;
        break;
      case 'S':
        curr_token = South;
        break;
      default:
        if (isdigit(c)) {
          curr_token = Units;
        }
        break;
      }

      // End of non-comment token
      if (isspace(c) || c == '\n') {
        // Ensure enough space exists for all tokens
        if (token_count == MAX_TOKENS) {
          ERR_AND_EXIT(stderr,
                       "%s: Number of tokens in input exceeds maximum number "
                       "of tokens (%d).\n", 
                       __func__, MAX_TOKENS);
        }

        // If unit token, check if preceding token is
        // E, W, S, P or N
        if (curr_token == Units &&
            !(prev_token == East || prev_token == West || prev_token == North ||
             prev_token == South || prev_token == Pen)) {
          ERR_AND_EXIT(stderr,                                                        
                       "%s: Line %d: Syntax error: Numerical token cannot "
                       "appear after non-directional token or non-'pen' token.\n",
                       __func__, line_no);                                            
        }

        // Store token
        buffer[buf_pos] = '\0';
        tokens[token_count].type = curr_token;
        memset(tokens[token_count].token, '\0', TOKEN_BUFFER_SIZE);
        strncpy(tokens[token_count].token, buffer, buf_pos + 1);
        token_count++;

        // Assign curr_token to prev_token
        prev_token = curr_token;
        curr_token = Nil;

        // Reset buffer position
        buf_pos = 0;
        continue;
      } else {
        buffer[buf_pos] = c;
        buf_pos++;
      }
    } else if (c == '\n') {
      // End of comment token
      // Ensure enough space exists for all tokens
      if (token_count == MAX_TOKENS) {
        ERR_AND_EXIT(stderr,
                     "%s: Number of tokens in input exceeds maximum number of "
                     "tokens (%d).\n",
                     __func__, MAX_TOKENS); 
      }
    
      line_no++;

      // Store token
      buffer[buf_pos] = '\0';
      tokens[token_count].type = curr_token;
      memset(tokens[token_count].token, '\0', TOKEN_BUFFER_SIZE);
      strncpy(tokens[token_count].token, buffer, buf_pos + 1);
      token_count++;

      prev_token = curr_token = Nil;

      // Reset buffer position
      buf_pos = 0;
    } else {
      buffer[buf_pos] = c;
      buf_pos++;
    }
  }
}
