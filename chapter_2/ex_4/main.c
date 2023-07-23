#include <stdio.h>
#include "src/lexer.h"

int main(int argc, char** argv)
{
    if (argc!=2)
        ERR_AND_EXIT(stderr, "Usage: %s <filename>\n", argv[0]);

    FILE* fp = fopen(argv[1], "r");
    Lexemes* lexemes;

    if (fp==NULL)
        ERR_AND_EXIT(stderr, "Could not open file %s\n", argv[1]);
    
    lexemes = lexemes_alloc();
    lexer(fp, lexemes);
    lexemes_print(lexemes);
    lexemes_destroy(lexemes);

    fclose(fp);
    return 0;
}
