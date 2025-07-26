#include <stdio.h>
#include "src/tokenizer.h"

int main(int argc, char** argv) {
    if (argc!=2) {
        ERR_AND_EXIT(stderr, "Usage: %s <filename>\n", argv[0]);
    }

    FILE* fp = fopen(argv[1], "r");
    Token* tokens;
    tokens_alloc(&tokens);

    if (fp==NULL) {
        ERR_AND_EXIT(stderr, "Could not open file %s\n", argv[1]);
    }

    tokenize(fp, tokens);
    print_tokens(tokens, 30);
    free(tokens);

    fclose(fp);
    return 0;
}
