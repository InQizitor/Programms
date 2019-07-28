/*
This .h file is contain disassembler function for Intel 8080 CPU and for soviet analog of this CPU, named as KR580VM80A

*/

#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <map>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

const map <int, string> commandTable = //table with opcodes and their mnemonics
{
	{0X87, "ADD A"},
	{0X80, "ADD B"},
	{0X81, "ADD C"},
	{0X82, "ADD D"},
	{0X83, "ADD E"},
	{0X84, "ADD H"},
	{0X85, "ADD L"},
	{0X86, "ADD M"},
	{0XC6, "ADI "}, 
	{0X8F, "ADC A"},
	{0X88, "ADC B"},
	{0X89, "ADC C"},
	{0X8A, "ADC D"},
	{0X8B, "ADC E"},
	{0X8C, "ADC H"},
	{0X8D, "ADC L"},
	{0X8E, "ADC M"},
	{0XCE, "ACI "}, 
	{0XA7, "ANA A"},
	{0XA0, "ANA B"},
	{0XA1, "ANA C"},
	{0XA2, "ANA D"},
	{0XA3, "ANA E"},
	{0XA4, "ANA H"},
	{0XA5, "ANA L"},
	{0XA6, "ANA M"},
	{0XE6, "ANI "}, 
	{0XCD, "CALL "}, 
	{0XCC, "CZ "}, 
	{0XC4, "CNZ "}, 
	{0XF4, "CP "}, 
	{0XFC, "CM "}, 
	{0XDC, "CC "}, 
	{0XD4, "CNC "}, 
	{0XEC, "CPE "}, 
	{0XE4, "CPO "}, 
	{0X2F, "CMA"},
	{0X3F, "CMC"},
	{0XBF, "CMP A"},
	{0XB8, "CMP B"},
	{0XB9, "CMP C"},
	{0XBA, "CMP D"},
	{0XBB, "CMP E"},
	{0XBC, "CMP H"},
	{0XBD, "CMP L"},
	{0XBE, "CMP M"},
	{0XFE, "CPI "}, 
	{0X27, "DAA"},
	{0X09, "DAD B"},
	{0X19, "DAD D"},
	{0X29, "DAD H"},
	{0X39, "DAD SP"},
	{0X3D, "DCR A"},
	{0X05, "DCR B"},
	{0X0D, "DCR C"},
	{0X15, "DCR D"},
	{0X1D, "DCR E"},
	{0X25, "DCR H"},
	{0X2D, "DCR L"},
	{0X35, "DCR M"},
	{0X0B, "DCX B"},
	{0X1B, "DCX D"},
	{0X2B, "DCX H"},
	{0X3B, "DCX SP"},
	{0XF3, "DI"},
	{0XFB, "EI"},
	{0X76, "HLT"},
	{0XDB, "IN "},
	{0X3C, "INR A"},
	{0X04, "INR B"},
	{0X0C, "INR C"},
	{0X14, "INR D"},
	{0X1C, "INR E"},
	{0X24, "INR H"},
	{0X2C, "INR L"},
	{0X34, "INR M"},
	{0X03, "INX B"},
	{0X13, "INX D"},
	{0X23, "INX H"},
	{0X33, "INX SP"},
	{0XC3, "JMP "},
	{0XCA, "JZ "}, 
	{0XC2, "JNZ "}, 
	{0XF2, "JP "}, 
	{0XFA, "JM "}, 
	{0XDA, "JC "}, 
	{0XD2, "JNC "}, 
	{0XEA, "JPE "},
	{0XE2, "JPO "}, 
	{0X3A, "LDA "}, 
	{0X0A, "LDAX B"},
	{0X1A, "LDAX D"}, 
	{0X2A, "LHLD "}, 
	{0X01, "LXI B, "},
	{0X21, "LXI H, "},
	{0X31, "LXI SP, "}, 
	{0X7F, "MOV A, A"},
	{0X78, "MOV A, B"},
	{0X79, "MOV A, C"},
	{0X7A, "MOV A, D"},
	{0X7B, "MOV A, D"},
	{0X7C, "MOV A, H"},
	{0X7D, "MOV A, L"},
	{0X7E, "MOV A, M"},
	{0X47, "MOV B, A"},
	{0X40, "MOV B, B"},
	{0X41, "MOV B, C"},
	{0X42, "MOV B, D"},
	{0X43, "MOV B, E"},
	{0X44, "MOV B, H"},
	{0X45, "MOV B, L"},
	{0X46, "MOV B, M"},
	{0X4F, "MOV C, A"},
	{0X48, "MOV C, D"},
	{0X49, "MOV C, C"},
	{0X4A, "MOV C, D"},
	{0X4B, "MOV C, E"},
	{0X4C, "MOV C, H"},
	{0X4D, "MOV C, L"},
	{0X4E, "MOV C, M"},
	{0X57, "MOV D, A"},
	{0X50, "MOV D, B"},
	{0X51, "MOV D, C"},
	{0X52, "MOV D, D"},
	{0X53, "MOV D, E"},
	{0X54, "MOV D, H"},
	{0X55, "MOV D, L"},
	{0X56, "MOV D, M"},
	{0X5F, "MOV E, A"},
	{0X58, "MOV E, B"},
	{0X59, "MOV E, C"},
	{0X5A, "MOV E, D"},
	{0X5B, "MOV E, E"},
	{0X5C, "MOV E, H"},
	{0X5D, "MOV E, L"},
	{0X5E, "MOV E, M"},
	{0X67, "MOV H, A"},
	{0X60, "MOV H, B"},
	{0X61, "MOV H, C"},
	{0X62, "MOV H, D"},
	{0X63, "MOV H, E"},
	{0X64, "MOV H, H"},
	{0X65, "MOV H, L"},
	{0X66, "MOV H, M"},
	{0X6F, "MOV L, A"},
	{0X68, "MOV L, B"},
	{0X69, "MOV L, C"},
	{0X6A, "MOV L, D"},
	{0X6B, "MOV L, E"},
	{0X6C, "MOV L, H"},
	{0X6D, "MOV L, L"},
	{0X6E, "MOV L, M"},
	{0X77, "MOV M, A"},
	{0X70, "MOV M, B"},
	{0X71, "MOV M, C"},
	{0X72, "MOV M, D"},
	{0X73, "MOV M, E"},
	{0X74, "MOV M, H"},
	{0X75, "MOV M, L"},
	{0X3E, "MVI A, "}, 
	{0X06, "MVI B, "}, 
	{0X0E, "MVI C, "}, 
	{0X16, "MVI D, "},
	{0X1E, "MVI E, "}, 
	{0X26, "MVI H, "},
	{0X2E, "MVI L, "},
	{0X36, "MVI M, "},
	{0X00, "NOP"},
	{0XB7, "ORA A"},
	{0XB0, "ORA B"},
	{0XB1, "ORA C"},
	{0XB2, "ORA D"},
	{0XB3, "ORA E"},
	{0XB4, "ORA H"},
	{0XB5, "ORA L"},
	{0XB6, "ORA M"},
	{0XF6, "ORI "}, 
	{0XD3, "OUT "}, 
	{0XE9, "PCHL"},
	{0XC1, "POP B"},
	{0XD1, "POP D"},
	{0XE1, "POP H"},
	{0XF1, "POP PSW"},
	{0XC5, "PUSH B"},
	{0XD5, "PUSH D"},
	{0XE5, "PUSH H"},
	{0XF5, "PUSH PSW"},
	{0X17, "RAL"},
	{0X1F, "RAR"},
	{0X07, "RLC"},
	{0X0F, "RRC"},
	{0X20, "RIM"}, //ONLY FOR 8085
	{0XC9, "RET"},
	{0XC8, "RZ"},
	{0XC0, "RNZ"},
	{0XF0, "RP"},
	{0XF8, "RM"},
	{0XD8, "RC"},
	{0XD0, "RNC"},
	{0XE8, "RPE"},
	{0XE0, "RPO"},
	{0XC7, "RST 0"},
	{0XCF, "RST 1"},
	{0XD7, "RST 2"},
	{0XDF, "RST 3"},
	{0XE7, "RST 4"},
	{0XEF, "RST 5"},
	{0XF7, "RST 6"},
	{0XFF, "RST 7"},
	{0X30, "SIM"}, //ONLY FOR 8085
	{0XF9, "SPHL"},
	{0X22, "SHLD "},
	{0X32, "STA "}, 
	{0X02, "STAX B"},
	{0X12, "STAX D"},
	{0X37, "STC"},
	{0X97, "SUB A"},
	{0X90, "SUB B"},
	{0X91, "SUB C"},
	{0X92, "SUB D"},
	{0X93, "SUB E"},
	{0X94, "SUB H"},
	{0X95, "SUB L"},
	{0X96, "SUB M"},
	{0XD6, "SUI "}, 
	{0X9F, "SBB A"},
	{0X98, "SBB B"},
	{0X99, "SBB C"},
	{0X9A, "SBB D"},
	{0X9B, "SBB E"},
	{0X9C, "SBB H"},
	{0X9D, "SBB L"},
	{0X9E, "SBB M"},
	{0XDE, "SBI "}, 
	{0XEB, "XCHG"},
	{0XE3, "XTHL"},
	{0XAF, "XRA A"},
	{0XA8, "XRA B"},
	{0XA9, "XRA C"},
	{0XAA, "XRA D"},
	{0XAB, "XRA E"},
	{0XAC, "XRA H"},
	{0XAD, "XRA L"},
	{0XAE, "XRA M"},
	{0XEE, "XRI "} 
};

void disassemble();

#endif