#include "instructionops.h"

QString generate_op(uint16_t insn)
{
    QString opcode;

    switch (insn & OP_MASK) {
    case ADD:
        opcode = "ADD";
        break;
    case ADDI:
        opcode = "ADDI";
        break;
    case AND:
        opcode = "AND";
        break;
    case INV:
        opcode = "INV";
        break;
    case MULT:
        opcode = "MULT";
        break;
    case DIV:
        opcode = "DIV";
        break;
    case MOD:
        opcode = "MOD";
        break;
    case LDI:
        opcode = "LDI";
        break;
    case BLZ:
        opcode = "BLZ";
        break;
    case BEZ:
        opcode = "BEZ";
        break;
    case BGZ:
        opcode = "BGZ";
        break;
    case JMP:
        opcode = "JMP";
        break;
    case JSR:
        opcode = "JSR";
        break;
    case RET:
        opcode = "RET";
        break;
    case END:
        opcode = "END";
        break;
    default:
        opcode = "???";
    }

    return opcode;
}
