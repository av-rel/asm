#ifndef ZORASM_C
#define ZORASM_C

#include <stdio.h>
#include <stdlib.h>

#include "./lexer.c"
#include "./token.c"
#include "./parser.c"

Zorasm_token_t* Zorasm(Zora_file_t *file, int *ncount , int *err) {

  Zorasm_lexer_t lexer;
  if (file->len < 1) goto dispose;
  lexer = Zorasm_init_lexer(file);

  if ((*err = Zorasm_tokenizer(&lexer)) != 0) goto dispose;
  if ((*err =  Zorasm_parser_analyze(&lexer)) != 0) goto dispose;

  *ncount = lexer.ntok;

dispose:
  return lexer.tokens;
}

#endif
