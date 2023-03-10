#ifndef ZORASM_PROG_C
#define ZORASM_PROG_C

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../zoravm/src/zoravm.h"
#include "./inst.c"
#include "./token.h"

ZoraVM_Program ZoraVM_Parse_Inst(ZORAVM_INST inst, Zorasm_token_t* tokens, unsigned int* c);

int ZoraVM_Program_from_tokens(Zorasm_token_t* tokens, unsigned int ctok , ZoraVM_Program* program) {
    unsigned int c = 0, progc = 0;
    Zorasm_token_t token = tokens[c++];

    for (; token.kind != ZORASM_TK_EOF;) {
        if (token.kind == ZORASM_TK_INST) {
            ZORAVM_INST inst = Zorasm_char_to_inst(token.value);
            program[progc++] = ZoraVM_Parse_Inst(inst, tokens, &c);
        }
        token = tokens[c++];
    }
    return progc;
}

ZoraVM_Program ZoraVM_Parse_Inst(ZORAVM_INST inst, Zorasm_token_t* tokens, unsigned int* c) {
    ZoraVM_Program prog = {0};

    switch (inst) {
        case ZORAVM_INST_PUSH: {
            Zorasm_token_t token = tokens[(*c)++];
            if (token.kind == ZORASM_TK_INT) prog = (ZoraVM_Program)ZoraVM_PushInt(atoll(token.value));
            else if (token.kind == ZORASM_TK_FLOAT) prog = (ZoraVM_Program)ZoraVM_PushFloat(atof(token.value));
            else prog = (ZoraVM_Program)ZoraVM_PushStr(token.value);
        } break;
        case ZORAVM_INST_STORE: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Store(atoll(token.value));
        } break;
        case ZORAVM_INST_LOAD: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Load(atoll(token.value));
        } break;
        case ZORAVM_INST_CALL: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Call(atoll(token.value));
        } break;
        case ZORAVM_INST_CALLIF: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_CallIf(atoll(token.value));
        } break;
        case ZORAVM_INST_CALLIFN: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_CallIfNot(atoll(token.value));
        } break;
        case ZORAVM_INST_JMP: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Jmp(atoll(token.value));
        } break;
        case ZORAVM_INST_JMPIF: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_JmpIf(atoll(token.value));
        } break;
        case ZORAVM_INST_JMPIFN: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_JmpIfNot(atoll(token.value));
        } break;
        case ZORAVM_INST_RET: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Ret(atoll(token.value));
        } break;
        case ZORAVM_INST_HALT: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Halt(atoll(token.value));
        } break;

        case ZORAVM_INST_DUP: prog = (ZoraVM_Program)ZoraVM_Dup(); break;
        case ZORAVM_INST_SWAP: prog = (ZoraVM_Program)ZoraVM_Swap(); break;
        case ZORAVM_INST_POP: prog = (ZoraVM_Program)ZoraVM_Pop(); break;

        case ZORAVM_INST_PRINT: prog = (ZoraVM_Program)ZoraVM_Print(); break;
        case ZORAVM_INST_SCAN: prog = (ZoraVM_Program)ZoraVM_Scan(); break;
        case ZORAVM_INST_SIZEOF: prog = (ZoraVM_Program)ZoraVM_SizeOf(); break;

        case ZORAVM_INST_ADD: prog = (ZoraVM_Program)ZoraVM_Add(); break;
        case ZORAVM_INST_SUB: prog = (ZoraVM_Program)ZoraVM_Sub(); break;
        case ZORAVM_INST_MUL: prog = (ZoraVM_Program)ZoraVM_Mul(); break;
        case ZORAVM_INST_DIV: prog = (ZoraVM_Program)ZoraVM_Div(); break;
        case ZORAVM_INST_MOD: prog = (ZoraVM_Program)ZoraVM_Mod(); break;
        case ZORAVM_INST_INC: prog = (ZoraVM_Program)ZoraVM_Inc(); break;
        case ZORAVM_INST_DEC: prog = (ZoraVM_Program)ZoraVM_Dec(); break;
        case ZORAVM_INST_POW: prog = (ZoraVM_Program)ZoraVM_Pow(); break;

        case ZORAVM_INST_SIN: prog = (ZoraVM_Program)ZoraVM_Sin(); break;
        case ZORAVM_INST_COS: prog = (ZoraVM_Program)ZoraVM_Cos(); break;
        case ZORAVM_INST_TAN: prog = (ZoraVM_Program)ZoraVM_Tan(); break;
        case ZORAVM_INST_FACTORIAL: prog = (ZoraVM_Program)ZoraVM_Factorial(); break;

        case ZORAVM_INST_AND: prog = (ZoraVM_Program)ZoraVM_And(); break;
        case ZORAVM_INST_OR: prog = (ZoraVM_Program)ZoraVM_Or(); break;
        case ZORAVM_INST_XOR: prog = (ZoraVM_Program)ZoraVM_Xor(); break;
        case ZORAVM_INST_NOT: prog = (ZoraVM_Program)ZoraVM_Not(); break;
        case ZORAVM_INST_NEG: prog = (ZoraVM_Program)ZoraVM_Neg(); break;
        case ZORAVM_INST_SHL: prog = (ZoraVM_Program)ZoraVM_Shl(); break;
        case ZORAVM_INST_SHR: prog = (ZoraVM_Program)ZoraVM_Shr(); break;

        case ZORAVM_INST_EQ: prog = (ZoraVM_Program)ZoraVM_CmpEq(); break;
        case ZORAVM_INST_GT: prog = (ZoraVM_Program)ZoraVM_CmpGt(); break;
        case ZORAVM_INST_GTE: prog = (ZoraVM_Program)ZoraVM_CmpGte(); break;
        case ZORAVM_INST_LT: prog = (ZoraVM_Program)ZoraVM_CmpLt(); break;
        case ZORAVM_INST_LTE: prog = (ZoraVM_Program)ZoraVM_CmpLte(); break;
        case ZORAVM_INST_NEQ: prog = (ZoraVM_Program)ZoraVM_CmpNeq(); break;
        case ZORAVM_INST_NGT: prog = (ZoraVM_Program)ZoraVM_CmpNotGt(); break;
        case ZORAVM_INST_NGTE: prog = (ZoraVM_Program)ZoraVM_CmpNotGte(); break;
        case ZORAVM_INST_NLT: prog = (ZoraVM_Program)ZoraVM_CmpNotLt(); break;
        case ZORAVM_INST_NLTE: prog = (ZoraVM_Program)ZoraVM_CmpNotLte(); break;

        case ZORAVM_INST_ENV: prog = (ZoraVM_Program)ZoraVM_Env(); break;

        case ZORAVM_INST_DUMP_STACK: prog = (ZoraVM_Program)ZoraVM_DumpStack(); break;
        case ZORAVM_INST_DUMP_MEM: prog = (ZoraVM_Program)ZoraVM_DumpMem(); break;
        default: {assert(0 && "Unimplemented");}
    }

    return prog;
}

#endif
