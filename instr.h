// Anthony Gianino (AJG275)
// Project 1 - Part 4 - instr.h
// 11/30/17

/* supervisor instructions */
#define SUPERVISOR 0x00
#define HALT       0x00
#define TRACE      0x01
#define SYSCALL    0x02
#define SYSRET     0x03

/* SYSCALL codes */
#define READ_INT    0
#define PRINT_INT   1
#define READ_CHAR   2
#define PRINT_CHAR  3
#define READ_LONG   4
#define PRINT_LONG  5
#define READ_FLOAT  6
#define PRINT_FLOAT 7

/* references to locations in the code space */
#define PC_RELATIVE 0x10
#define RGETW       0x10 /*arg = w_PC_offset; stack = --w_value*/
#define RGETL       0x11 /*arg = w_PC_offset; stack = --l_value*/
#define RGETQ       0x12 /*arg = w_PC_offset; stack = --q_value*/
#define RGETB       0x13 /*arg = w_PC_offset; stack = --b_value*/
#define RPUTW       0x14 /*arg = w_PC_offset; stack = w_value--*/
#define RPUTL       0x15 /*arg = w_PC_offset; stack = l_value--*/
#define RPUTQ       0x16 /*arg = w_PC_offset; stack = q_value--*/
#define RPUTB       0x17 /*arg = w_PC_offset; stack = b_value--*/
#define RGOTO       0x18 /*arg = w_PC_offset*/
#define RGOSUB      0x19 /*arg = w_PC_offset; stack = --q_ret_addr*/
#define RGOZ        0x1A /*arg = w_PC_offset; stack = w_flag--*/
#define RPUSHA      0x1B /*arg = w_PC_offset; stack = --q_c_addr*/
#define PUSHW       0x1C /*arg = w_value; stack = --w_value*/
#define PUSHL       0x1D /*arg = l_value; stack = --l_value*/
#define PUSHQ       0x1E /*arg = q_value; stack = --q-value*/
#define PUSHB       0x1F /*arg = b_value; stack = --b_value*/
#define CODE_STACK  0x20
#define CGETW       0x20 /*stack = q_c_addr--w_value*/
#define CGETL       0x21 /*stack = q_c_addr--l_value*/
#define CGETQ       0x22 /*stack = q_c_addr--q_value*/
#define CGETB       0x23 /*stack = q_c_addr--b_value*/
#define CPUTW       0x24 /*stack = q_c_addr\w_value--*/
#define CPUTL       0x25 /*stack = q_c_addr\l_value--*/
#define CPUTQ       0x26 /*stack = q_c_addr\q_value--*/
#define CPUTB       0x27 /*stack = q_c_addr\b_value--*/
#define GOTO        0x28 /*stack = q_c_addr--*/
#define RET         0x28 /*stack = q_c_addr--*/
#define GOSUB       0x29 /*stack = q_c_addr--q_ret_addr*/
#define GOZ         0x2A /*stack = q_c_addr\w_flag--*/

/* references to locations in the data space */
#define DATA_INSTR 0x30
#define GETSW      0x30 /*stack = w_d_addr--w_value*/
#define GETSL      0x31 /*stack = w_d_addr--l_value*/
#define GETSQ      0x32 /*stack = w_d_addr--q_value*/
#define GETSB      0x33 /*stack = w_d_addr--b_value*/
#define PUTSW      0x34 /*stack = w_d_addr\w_value--*/
#define PUTSL      0x35 /*stack = w_d_addr\l_value--*/
#define PUTSQ      0x36 /*stack = w_d_addr\q_value--*/
#define PUTSB      0x37 /*stack = w_d_addr\b_value--*/
#define GETFW      0x38 /*stack = q_d_addr--w_value*/
#define GETFL      0x39 /*stack = q_d_addr--l_value*/
#define GETFQ      0x3A /*stack = q_d_addr--q_value*/
#define GETFB      0x3B /*stack = q_d_addr--b_value*/
#define PUTFW      0x3C /*stack = q_d_addr\w_value--*/
#define PUTFL      0x3D /*stack = q_d_addr\l_value--*/
#define PUTFQ      0x3E /*stack = q_d_addr\q_value--*/
#define PUTFB      0x3F /*stack = q_d_addr\b_value--*/

/* references to locations in the frames on the stack */
#define FRAME_INSTR 0x40
#define LGETSW      0x40 /*stack = w_frame\w_offset--w_value*/
#define LGETSL      0x41 /*stack = w_frame\w_offset--l_value*/
#define LGETSQ      0x42 /*stack = w_frame\w_offset--q_value*/
#define LGETSB      0x43 /*stack = w_frame\w_offset--b_value*/
#define LPUTSW      0x44 /*stack = w_frame\w_offset\w_value--*/
#define LPUTSL      0x45 /*stack = w_frame\w_offset\l_value--*/
#define LPUTSQ      0x46 /*stack = w_frame\w_offset\q_value--*/
#define LPUTSB      0x47 /*stack = w_frame\w_offset\b_value--*/
#define LGETFW      0x48 /*stack = w_frame\q_offset--w_value*/
#define LGETFL      0x49 /*stack = w_frame\q_offset--l_value*/
#define LGETFQ      0x4A /*stack = w_frame\q_offset--q_value*/
#define LGETFB      0x4B /*stack = w_frame\q_offset--b_value*/
#define LPUTFW      0x4C /*stack = w_frame\q_offset\w_value--*/
#define LPUTFL      0x4D /*stack = w_frame\q_offset\l_value--*/
#define LPUTFQ      0x4E /*stack = w_frame\q_offset\q_value--*/
#define LPUTFB      0x4F /*stack = w_frame\q_offset\b_value--*/

/* arithmetic and logical instructions */
#define MATH_INSTR    0x50
#define ADDI          0x50 /*stack = int1\int2--int1+int2*/
#define ADDL          0x51 /*stack = l_int1\l_int2--l_int1+l_int2*/
#define ADDF          0x52 /*stack = float1\float2--float1+float2*/
#define ADDC          0x53 /*stack = char1\char2--char1+char2*/
#define SUBI          0x54 /*stack = int1\int2--int1-int2*/
#define SUBL          0x55 /*stack = l_int1\l_int2--l_int1-l_int2*/
#define SUBF          0x56 /*stack = float1\float2--float1-float2*/
#define SUBC          0x57 /*stack = char1\char2--char1-char2*/
#define MULI          0x58 /*stack = int1\int2--int1*int2*/
#define MULL          0x59 /*stack = l_int1\l_int2--l_int1*l_int2*/
#define MULF          0x5A /*stack = float1\float2--float1*float2*/
#define MULC          0x5B /*stack = char1\char2--char1*char2*/
#define DIVI          0x5C /*stack = int1\int2--int1/int2*/
#define DIVL          0x5D /*stack = l_int1\l_int2--l_int1/l_int2*/
#define DIVF          0x5E /*stack = float1\float2--float1/float2*/
#define DIVC          0x5F /*stack = char1\char2--char1/char2*/
#define LOGICAL_INSTR 0x60
#define ANDW          0x60 /*stack = word1\word2--word1_bit_and_word2*/
#define ANDL          0x61 /*stack = long1\long2--long1_bit_and_long2*/
#define ANDQ          0x62 /*stack = quad1\quad2--quad1_bit_and_quad2*/
#define ANDB          0x63 /*stack = byte1\byte2--byte1_bit_and_byte2*/
#define ORW           0x64 /*stack = word1\word2--word1_bit_or_word2*/
#define ORL           0x65 /*stack = long1\long2--long1_bit_or_long2*/
#define ORQ           0x66 /*stack = quad1\quad2--quad1_bit_or_quad2*/
#define ORB           0x67 /*stack = byte1\byte2--byte1_bit_or_byte2*/
#define XORW          0x68 /*stack = word1\word2--word1_bit_xor_word2*/
#define XORL          0x69 /*stack = long1\long2--long1_bit_xor_long2*/
#define XORQ          0x6A /*stack = quad1\quad2--quad1_bit_xor_quad2*/
#define XORB          0x6B /*stack = byte1\byte2--byte1_bit_xor_byte2*/
#define NOTW          0x6C /*stack = word--bit_not_of_word*/
#define NOTL          0x6D /*stack = long--bit_not_of_long*/
#define NOTQ          0x6E /*stack = quad--bit_not_of_quad*/
#define NOTB          0x6F /*stack = byte--bit_not_of_byte*/
#define SHIFT_TEST    0x70
#define CSFTW         0x70 /*stack = w_value\amt--w_value*/
#define CSFTL         0x71 /*stack = l_value\amt--l_value*/
#define CSFTQ         0x72 /*stack = q_value\amt--q_value*/
#define CSFTB         0x73 /*stack = b_value\amt--b_value*/
#define ASFTW         0x74 /*stack = w_value\amt--w_value*/
#define ASFTL         0x75 /*stack = l_value\amt--l_value*/
#define ASFTQ         0x76 /*stack = q_value\amt--q_value*/
#define ASFTB         0x77 /*stack = b_value\amt--b_value*/
#define TSTEQI        0x78 /*stack = int--w_flag*/
#define TSTEQL        0x79 /*stack = l_int--w_flag*/
#define TSTEQF        0x7A /*stack = float--w_flag*/
#define TSTEQC        0x7B /*stack = char--w_flag*/
#define TSTLTI        0x7C /*stack = int--w_flag*/
#define TSTLTL        0x7D /*stack = l_int--w_flag*/
#define TSTLTF        0x7E /*stack = float--w_flag*/
#define TSTLTC        0x7F /*stack = char--w_flag*/

/* stack manipulation instructions */
#define STACK_MANIP 0x80
#define DUPW        0x80 /*stack = w_value--w_value\w_value*/
#define DUPL        0x81 /*stack = l_value--l_value\l_value*/
#define DUPQ        0x82 /*stack = q_value--q_value\q_value*/
#define DUPO        0x83 /*stack = o_value--o_value\o_value*/
#define SWAPW       0x84 /*stack = word1\word2--word2\word1*/
#define SWAPL       0x85 /*stack = long1\long2--long2\long1*/
#define SWAPQ       0x86 /*stack = quad1\quad2--quad2\quad1*/
#define SWAPO       0x87 /*stack = octa1\octa2--octa2\octa1*/
#define CHSPS       0x88 /*stack = w_value-- */
#define CHSPF       0x89 /*stack = q_value-- */
#define NEWFR       0x8A /*arg = w_frame; stack = --q_ofp <set fp>*/
#define RESFR       0x8B /*arg = w_frame; stack = stuff\q_ofp\local--stuff*/

/* format conversion instructions */
#define CONVERT 0x90
#define ADRD    0x90 /*stack = q_d_addr--q_universal_addr*/
#define CVTIL   0x91 /*stack = int--long*/
#define CVTIF   0x92 /*stack = int--float*/
#define CVTIC   0x93 /*stack = int--char*/
#define CVTLI   0x94 /*stack = long--int*/
#define ZEXWQ   0x95 /*stack = w_value--q_value*/
#define CVTLF   0x96 /*stack = long--float*/
#define CVTLC   0x97 /*stack = long--char*/
#define CVTFI   0x98 /*stack = float--int*/
#define CVTFL   0x99 /*stack = float--long*/
#define ADRC    0x9A /*stack = q_c_addr--q_universal_addr*/
#define CVTFC   0x9B /*stack = float--char*/
#define CVTCI   0x9C /*stack = char--int*/
#define CVTCL   0x9D /*stack = char--long*/
#define CVTCF   0x9E /*stack = char--float*/
#define ADRF    0x9F /*stack = w_frame\q_offset--q_universal_addr*/

/* instruction record in the file "instr.c" */
typedef struct {
  char name[10];
  int value;
  int no_arg;
  int arg_size[5];
} Instr;
extern Instr instrs[];

/* Directives */
#define ENTRY 1
#define CODE  2
#define DATA  3

