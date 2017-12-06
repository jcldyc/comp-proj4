// Anthony Gianino (AJG275)
// Project 1 - Part 4 - instr.c
// 11/30/17
//

#include "instr.h"

Instr instrs[0xff] ={

/*name  \value\# args\arg sizes*/
{"HALT", 0x00, 0}, {"TRACE", 0x01, 0},
{"SYSCALL", 0x02, 0}, {"SYSRET", 0x03, 0},
{"<resvd>", 0x04, 0}, {"<resvd>", 0x05, 0},
{"<resvd>", 0x06, 0}, {"<resvd>", 0x07, 0},
{"<resvd>", 0x08, 0}, {"<resvd>", 0x09, 0},
{"<resvd>", 0x0A, 0}, {"<resvd>", 0x0B, 0},
{"<resvd>", 0x0C, 0}, {"<resvd>", 0x0D, 0},
{"<resvd>", 0x0E, 0}, {"<resvd>", 0x0F, 0},
{"RGETW", 0x10, 1, {2}}, /*arg = w_PC_offset*/
{"RGETL", 0x11, 1, {2}}, /*arg = w_PC_offset*/
{"RGETQ", 0x12, 1, {2}}, /*arg = w_PC_offset*/
{"RGETB", 0x13, 1, {2}}, /*arg = w_PC_offset*/
{"RPUTW", 0x14, 1, {2}}, /*arg = w_PC_offset*/
{"RPUTL", 0x15, 1, {2}}, /*arg = w_PC_offset*/
{"RPUTQ", 0x16, 1, {2}}, /*arg = w_PC_offset*/
{"RPUTB", 0x17, 1, {2}}, /*arg = w_PC_offset*/
{"RGOTO", 0x18, 1, {2}}, /*arg = w_PC_offset*/
{"RGOSUB", 0x19, 1, {2}}, /*arg = w_PC_offset*/
{"RGOZ", 0x1A, 1, {2}}, /*arg = w_PC_offset*/
{"RPUSHA", 0x1B, 1, {2}}, /*arg = w_PC_offset*/
{"PUSHW", 0x1C, 1, {2}}, /*arg = w_value*/
{"PUSHL", 0x1D, 1, {4}}, /*arg = l_value*/
{"PUSHQ", 0x1E, 1, {8}}, /*arg = q_value*/
{"PUSHB", 0x1F, 1, {1}}, /*arg = b_value*/
{"CGETW", 0x20, 0}, {"CGETL", 0x21, 0},
{"CGETQ", 0x22, 0}, {"CGETB", 0x23, 0},
{"CPUTW", 0x24, 0}, {"CPUTL", 0x25, 0},
{"CPUTQ", 0x26, 0}, {"CPUTB", 0x27, 0},
{"GOTO", 0x28, 0}, {"GOSUB", 0x29, 0},
{"GOZ", 0x2A, 0}, {"<undef>", 0x28, 0},
{"<undef>", 0x2C, 0}, {"<undef>", 0x2D, 0},
{"<undef>", 0x2E, 0}, {"<undef>", 0x2F, 0},
{"GETSW", 0x30, 0}, {"GETSL", 0x31, 0},
{"GETSQ", 0x32, 0}, {"GETSB", 0x33, 0},
{"PUTSW", 0x34, 0}, {"PUTSL", 0x35, 0},
{"PUTSQ", 0x36, 0}, {"PUTSB", 0x37, 0},
{"GETFW", 0x38, 0}, {"GETFL", 0x39, 0},
{"GETFQ", 0x3A, 0}, {"GETFB", 0x3B, 0},
{"PUTFW", 0x3C, 0}, {"PUTFL", 0x3D, 0},
{"PUTFQ", 0x3E, 0}, {"PUTFB", 0x3F, 0},
{"LGETSW", 0x40, 0}, {"LGETSL", 0x41, 0},
{"LGETSQ", 0x42, 0}, {"LGETSB", 0x43, 0},
{"LPUTSW", 0x44, 0}, {"LPUTSL", 0x45, 0},
{"LPUTSQ", 0x46, 0}, {"LPUTSB", 0x47, 0},
{"LGETFW", 0x48, 0}, {"LGETFL", 0x49, 0},
{"LGETFQ", 0x4A, 0}, {"LGETFB", 0x4B, 0},
{"LPUTFW", 0x4C, 0}, {"LPUTFL", 0x4D, 0},
{"LPUTFQ", 0x4E, 0}, {"LPUTFB", 0x4F, 0},
{"ADDI", 0x50, 0}, {"ADDL", 0x51, 0},
{"ADDF", 0x52, 0}, {"ADDC", 0x53, 0},
{"SUBI", 0x54, 0}, {"SUBL", 0x55, 0},
{"SUBF", 0x56, 0}, {"SUBC", 0x57, 0},
{"MULI", 0x58, 0}, {"MULL", 0x59, 0},
{"MULF", 0x5A, 0}, {"MULC", 0x5B, 0},
{"DIVI", 0x5C, 0}, {"DIVL", 0x5D, 0},
{"DIVF", 0x5E, 0}, {"DIVC", 0x5F, 0},
{"ANDW", 0x60, 0}, {"ANDL", 0x61, 0},
{"ANDQ", 0x62, 0}, {"ANDB", 0x63, 0},
{"ORW", 0x64, 0}, {"ORL", 0x65, 0},
{"ORQ", 0x66, 0}, {"ORB", 0x67, 0},
{"XORW", 0x68, 0}, {"XORL", 0x69, 0},
{"XORQ", 0x6A, 0}, {"XORB", 0x6B, 0},
{"NOTW", 0x6C, 0}, {"NOTL", 0x6D, 0},
{"NOTQ", 0x6E, 0}, {"NOTB", 0x6F, 0},
{"CSFTW", 0x70, 0}, {"CSFTL", 0x71, 0},
{"CSFTQ", 0x72, 0}, {"CSFTB", 0x73, 0},
{"ASFTW", 0x74, 0}, {"ASFTL", 0x75, 0},
{"ASFTQ", 0x76, 0}, {"ASFTB",  0x77, 0},
{"TSTEQI", 0x78, 0}, {"TSTEQL", 0x79, 0},
{"TSTEQF", 0x7A, 0}, {"TSTEQC", 0x7B, 0},
{"TSTLTI", 0x7C, 0}, {"TSTLTL", 0x7D, 0},
{"TSTLTF", 0x7E, 0}, {"TSTLTC", 0x7F, 0},
{"DUPW", 0x80, 0}, {"DUPL", 0x81, 0},
{"DUPQ", 0x82, 0}, {"DUPO", 0x83, 0},
{"SWAPW", 0x84, 0}, {"SWAPL",  0x85, 0},
{"SWAPQ", 0x86, 0}, {"SWAPO",  0x87, 0},
{"CHSPS", 0x88, 0}, {"CHSPF",  0x89, 0},
{"NEWFR", 0x8A, 1, {2}}, /*arg = w_frame*/
{"RESFR", 0x8B, 1, {2}}, /*arg = w_frame*/
{"<resvd>", 0x8C, 0}, {"<resvd>", 0x8D, 0},
{"<resvd>", 0x8E, 0}, {"<resvd>", 0x8F, 0},
{"ADRD", 0x90, 0}, {"CVTIL", 0x91, 0},
{"CVTIF", 0x92, 0}, {"CVTIC", 0x93, 0},
{"CVTLI", 0x94, 0}, {"ZEXWQ", 0x95, 0},
{"CVTLF", 0x96, 0}, {"CVTLC", 0x97, 0},
{"CVTFI", 0x98, 0}, {"CVTFL", 0x99, 0},
{"ADRC", 0x9A, 0}, {"CVTFC", 0x9B, 0},
{"CVTCI", 0x9C, 0}, {"CVTCL", 0x9D, 0},
{"CVTCF", 0x9E, 0}, {"ADRF", 0x9F, 0}
};

