#ifndef ZORASM_LEXER_C
#define ZORASM_LEXER_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./lexer.h"

Zorasm_lexer_t Zorasm_init_lexer(Zora_file_t *file) {
  Zorasm_lexer_t lexer = {0};

  lexer.file = file;
  lexer.pos = 0;
  lexer.col = lexer.pos + 1;
  lexer.line = 1;
  lexer.cur = file->src[lexer.pos];
  lexer.tokens = malloc(sizeof(Zorasm_token_t) * (file->len + 1));
  lexer.ntok = 0;

  return lexer;
}

char Zorasm_lexer_advance(Zorasm_lexer_t *lexer) {
  if (lexer->cur == '\0') return lexer->cur;

  if (lexer->cur == '\n') {
    lexer->line++;
    lexer->col = 0;
  }

  lexer->pos++;
  lexer->col++;
  lexer->cur = lexer->file->src[lexer->pos];
  return lexer->cur;
}

void Zorasm_lexer_degrade(Zorasm_lexer_t *lexer) {
  if (lexer->pos == 0)
    return;

  if (lexer->cur == '\n') {
    lexer->line--;
    lexer->col = 0;
  }

  lexer->pos--;
  lexer->col--;
  lexer->cur = lexer->file->src[lexer->pos];
}

char Zorasm_lexer_peek(Zorasm_lexer_t *lexer, int offset) {
  if (lexer->pos + offset < (unsigned int)lexer->file->len)
    return lexer->file->src[lexer->pos + offset];
  return '\0';
}

void Zorasm_lexer_n_advance(Zorasm_lexer_t *lexer, unsigned int n) {
  unsigned int i;
  for (i = 0; i < n; i++) Zorasm_lexer_advance(lexer);
}

void Zorasm_lexer_skip_ws(Zorasm_lexer_t *lexer) {
  while (Zora_is_ws(lexer->cur))
    Zorasm_lexer_advance(lexer);
}

void Zorasm_lexer_skip_line(Zorasm_lexer_t *lexer) {
  while (lexer->cur != '\n' && lexer->cur != '\0')
    Zorasm_lexer_advance(lexer);
}

void Zorasm_log_error_line(char *source, int errline) {
  int line = 1, pos = 0, findline = 1, scrapline = 1, i;
  int filelen = strlen(source);
  for (i = 0; (i < filelen && findline); i++) {
    if (source[pos] == '\n') line++;
    if (errline == line) {
      pos++;
      printf("  %d | ", errline);
      while (scrapline) {
        if (source[pos] == '\0') break;
        printf("%c", source[pos++]);
        if (source[pos] == '\n' && filelen > pos) scrapline = 0;
      }
      printf("\n\n");
      findline = 0;
    }
    pos++;
  }
}

void Zorasm_lexical_error(Zorasm_lexer_t *lexer) {
  printf("\n%s:%d:%d Unrecognized token `%c`\n\n", lexer->file->argfile, lexer->line, lexer->col, lexer->cur);
  Zorasm_log_error_line(lexer->file->src, lexer->line);
}

#endif
