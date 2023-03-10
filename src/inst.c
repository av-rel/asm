#ifndef ZORASM_INST_C
#define ZORASM_INST_C

#include <stdio.h>
#include <string.h>

#include "./token.h"
#include "../zoravm/src/inst.c"

ZORAVM_INST Zorasm_char_to_inst(char *s) {
  int i;
  for (i = 0; i < ZORAVM_INST_HALT; i++)
    if (strcmp(s, ZoraVM_Inst[i]) == 0)
      return i;
  return ZORAVM_INST_HALT;
}

Zorasm_TokenKind Zorasm_inst_operand(ZORAVM_INST zn) {
  switch (zn) {
    case ZORAVM_INST_STORE:
    case ZORAVM_INST_LOAD:
      return ZORASM_TK_REGISTER;

    case ZORAVM_INST_PUSH:
      return ZORASM_TK_KIND;

    case ZORAVM_INST_JMP:
    case ZORAVM_INST_JMPIF:
    case ZORAVM_INST_JMPIFN:
    case ZORAVM_INST_CALL:
    case ZORAVM_INST_CALLIF:
    case ZORAVM_INST_CALLIFN:
      return ZORASM_TK_LABEL;

    case ZORAVM_INST_RET:
    case ZORAVM_INST_HALT:
      return ZORASM_TK_INT;

    default: return ZORASM_TK_NONE;
  }
  return ZORASM_TK_NONE;
}

Zorasm_TokenKind Zorasm_inst_op(char* native) {
    unsigned int i, len = sizeof(ZoraVM_Inst)/sizeof(ZoraVM_Inst[0]) ;
    for (i = 0; i < len ; i++)
        if (strcmp(native, ZoraVM_Inst[i]) == 0) 
            return Zorasm_inst_operand(i);
    return ZORASM_TK_NONE;
}

ZORAVM_DATAKIND Zorasm_tk_to_dk(Zorasm_TokenKind kind){
  ZORAVM_DATAKIND data = {0};
  if (kind == ZORASM_TK_STRING) return ZORAVM_DATA_STRING;
  else if  (kind == ZORASM_TK_INT) return ZORAVM_DATA_STRING;
  else if (kind == ZORASM_TK_FLOAT) return ZORAVM_DATA_STRING;
  else return ((data = -69));
}

int Zorasm_is_inst(char *str) {
  unsigned int i;
  for (i = 0; i < (sizeof(ZoraVM_Inst)/sizeof(ZoraVM_Inst[0])); i++) 
    if (strcmp(str, ZoraVM_Inst[i]) == 0) return 1;
  return 0;
}

int Zorasm_is_register(char *str) {
  unsigned int i;
  for (i = 0; i < strlen(str); i++) {
    if (!Zora_is_digit(str[i])) return 0;
  }
  return 1;
}

int Zorasm_is_datakind(char *str) {
  int data = 0;
  unsigned int i;
  for (i = 0; i < sizeof(ZoraVM_DataKind)/sizeof(ZoraVM_DataKind[0]); i++) if (strcmp(str, ZoraVM_DataKind[i]) == 0) ++data;
  return data;
}

void Zorasm_print_all_insts() {
  unsigned int i, len  = sizeof(ZoraVM_Inst)/sizeof(ZoraVM_Inst[0]);
  for (i = 0; i < len ; i++) {
    printf("%s", ZoraVM_Inst[i]);
    if (i != len - 1) printf(", ");
  }
  printf("\n");
}

void Zorasm_print_all_datakind() {
  unsigned int i, len = sizeof(ZoraVM_DataKind)/sizeof(ZoraVM_DataKind[0]);
  for (i = 0; i < len; i++) {
    printf("%s", ZoraVM_DataKind[i]);
    if (i != len - 1) printf(", ");
  }
  printf("\n");
}

#endif
