void asmdir_init()
{
    ASM_DIR["BASE"] = true;
    ASM_DIR["EQU"] = true;
    ASM_DIR["END"] = true;
    ASM_DIR["LTORG"] = true;
    ASM_DIR["EXTDEF"] = true;
    ASM_DIR["EXTREF"] = true;
    ASM_DIR["RESB"] = true;
    ASM_DIR["RESW"] = true;
    ASM_DIR["WORD"] = true;
    ASM_DIR["BYTE"] = true;
    ASM_DIR["ORG"] = true;
    ASM_DIR["NOBASE"] = true;
}

void optab_init()
{
    OP_TAB["ADD"].opcode = "18";
    OP_TAB["ADD"].format = 3;
    OP_TAB["ADD"].exists = true;

    OP_TAB["ADDF"].opcode = "58";
    OP_TAB["ADDF"].format = 3;
    OP_TAB["ADDF"].exists = true;

    OP_TAB["ADDR"].opcode = "90";
    OP_TAB["ADDR"].format = 2;
    OP_TAB["ADDR"].exists = true;

    OP_TAB["AND"].opcode = "40";
    OP_TAB["AND"].format = 3;
    OP_TAB["AND"].exists = true;

    OP_TAB["CLEAR"].opcode = "B4";
    OP_TAB["CLEAR"].format = 2;
    OP_TAB["CLEAR"].exists = true;

    OP_TAB["COMP"].opcode = "28";
    OP_TAB["COMP"].format = 3;
    OP_TAB["COMP"].exists = true;

    OP_TAB["COMPF"].opcode = "88";
    OP_TAB["COMPF"].format = 3;
    OP_TAB["COMPF"].exists = true;

    OP_TAB["COMPR"].opcode = "A0";
    OP_TAB["COMPR"].format = 2;
    OP_TAB["COMPR"].exists = true;

    OP_TAB["DIV"].opcode = "24";
    OP_TAB["DIV"].format = 3;
    OP_TAB["DIV"].exists = true;

    OP_TAB["DIVF"].opcode = "64";
    OP_TAB["DIVF"].format = 3;
    OP_TAB["DIVF"].exists = true;

    OP_TAB["DIVR"].opcode = "9C";
    OP_TAB["DIVR"].format = 2;
    OP_TAB["DIVR"].exists = true;

    OP_TAB["FIX"].opcode = "C4";
    OP_TAB["FIX"].format = 1;
    OP_TAB["FIX"].exists = true;

    OP_TAB["FLOAT"].opcode = "C0";
    OP_TAB["FLOAT"].format = 1;
    OP_TAB["FLOAT"].exists = true;

    OP_TAB["HIO"].opcode = "F4";
    OP_TAB["HIO"].format = 1;
    OP_TAB["HIO"].exists = true;

    OP_TAB["J"].opcode = "3C";
    OP_TAB["J"].format = 3;
    OP_TAB["J"].exists = true;

    OP_TAB["JEQ"].opcode = "30";
    OP_TAB["JEQ"].format = 3;
    OP_TAB["JEQ"].exists = true;

    OP_TAB["JGT"].opcode = "34";
    OP_TAB["JGT"].format = 3;
    OP_TAB["JGT"].exists = true;

    OP_TAB["JLT"].opcode = "38";
    OP_TAB["JLT"].format = 3;
    OP_TAB["JLT"].exists = true;

    OP_TAB["JSUB"].opcode = "48";
    OP_TAB["JSUB"].format = 3;
    OP_TAB["JSUB"].exists = true;

    OP_TAB["LDA"].opcode = "00";
    OP_TAB["LDA"].format = 3;
    OP_TAB["LDA"].exists = true;

    OP_TAB["LDB"].opcode = "68";
    OP_TAB["LDB"].format = 3;
    OP_TAB["LDB"].exists = true;

    OP_TAB["LDCH"].opcode = "50";
    OP_TAB["LDCH"].format = 3;
    OP_TAB["LDCH"].exists = true;

    OP_TAB["LDF"].opcode = "70";
    OP_TAB["LDF"].format = 3;
    OP_TAB["LDF"].exists = true;

    OP_TAB["LDL"].opcode = "08";
    OP_TAB["LDL"].format = 3;
    OP_TAB["LDL"].exists = true;

    OP_TAB["LDS"].opcode = "6C";
    OP_TAB["LDS"].format = 3;
    OP_TAB["LDS"].exists = true;

    OP_TAB["LDT"].opcode = "74";
    OP_TAB["LDT"].format = 3;
    OP_TAB["LDT"].exists = true;

    OP_TAB["LDX"].opcode = "04";
    OP_TAB["LDX"].format = 3;
    OP_TAB["LDX"].exists = true;

    OP_TAB["LPS"].opcode = "D0";
    OP_TAB["LPS"].format = 3;
    OP_TAB["LPS"].exists = true;

    OP_TAB["MUL"].opcode = "20";
    OP_TAB["MUL"].format = 3;
    OP_TAB["MUL"].exists = true;

    OP_TAB["MULF"].opcode = "60";
    OP_TAB["MULF"].format = 3;
    OP_TAB["MULF"].exists = true;

    OP_TAB["MULR"].opcode = "98";
    OP_TAB["MULR"].format = 2;
    OP_TAB["MULR"].exists = true;

    OP_TAB["NORM"].opcode = "C8";
    OP_TAB["NORM"].format = 1;
    OP_TAB["NORM"].exists = true;

    OP_TAB["OR"].opcode = "44";
    OP_TAB["OR"].format = 3;
    OP_TAB["OR"].exists = true;

    OP_TAB["RD"].opcode = "D8";
    OP_TAB["RD"].format = 3;
    OP_TAB["RD"].exists = true;

    OP_TAB["RMO"].opcode = "AC";
    OP_TAB["RMO"].format = 2;
    OP_TAB["RMO"].exists = true;

    OP_TAB["RSUB"].opcode = "4F";
    OP_TAB["RSUB"].format = 3;
    OP_TAB["RSUB"].exists = true;

    OP_TAB["SHIFTL"].opcode = "A4";
    OP_TAB["SHIFTL"].format = 2;
    OP_TAB["SHIFTL"].exists = true;

    OP_TAB["SHIFTR"].opcode = "A8";
    OP_TAB["SHIFTR"].format = 2;
    OP_TAB["SHIFTR"].exists = true;

    OP_TAB["SIO"].opcode = "F0";
    OP_TAB["SIO"].format = 1;
    OP_TAB["SIO"].exists = true;

    OP_TAB["SSK"].opcode = "EC";
    OP_TAB["SSK"].format = 3;
    OP_TAB["SSK"].exists = true;

    OP_TAB["STA"].opcode = "0C";
    OP_TAB["STA"].format = 3;
    OP_TAB["STA"].exists = true;

    OP_TAB["STB"].opcode = "78";
    OP_TAB["STB"].format = 3;
    OP_TAB["STB"].exists = true;

    OP_TAB["STCH"].opcode = "54";
    OP_TAB["STCH"].format = 3;
    OP_TAB["STCH"].exists = true;

    OP_TAB["STF"].opcode = "80";
    OP_TAB["STF"].format = 3;
    OP_TAB["STF"].exists = true;

    OP_TAB["STI"].opcode = "D4";
    OP_TAB["STI"].format = 3;
    OP_TAB["STI"].exists = true;

    OP_TAB["STL"].opcode = "14";
    OP_TAB["STL"].format = 3;
    OP_TAB["STL"].exists = true;

    OP_TAB["STS"].opcode = "7C";
    OP_TAB["STS"].format = 3;
    OP_TAB["STS"].exists = true;

    OP_TAB["STSW"].opcode = "E8";
    OP_TAB["STSW"].format = 3;
    OP_TAB["STSW"].exists = true;

    OP_TAB["STT"].opcode = "84";
    OP_TAB["STT"].format = 3;
    OP_TAB["STT"].exists = true;

    OP_TAB["STX"].opcode = "10";
    OP_TAB["STX"].format = 3;
    OP_TAB["STX"].exists = true;

    OP_TAB["SUB"].opcode = "1C";
    OP_TAB["SUB"].format = 3;
    OP_TAB["SUB"].exists = true;

    OP_TAB["SUBF"].opcode = "5C";
    OP_TAB["SUBF"].format = 3;
    OP_TAB["SUBF"].exists = true;

    OP_TAB["SUBR"].opcode = "94";
    OP_TAB["SUBR"].format = 2;
    OP_TAB["SUBR"].exists = true;

    OP_TAB["SVC"].opcode = "B0";
    OP_TAB["SVC"].format = 2;
    OP_TAB["SVC"].exists = true;

    OP_TAB["TD"].opcode = "E0";
    OP_TAB["TD"].format = 3;
    OP_TAB["TD"].exists = true;

    OP_TAB["TIO"].opcode = "F8";
    OP_TAB["TIO"].format = 1;
    OP_TAB["TIO"].exists = true;

    OP_TAB["TIX"].opcode = "2C";
    OP_TAB["TIX"].format = 3;
    OP_TAB["TIX"].exists = true;

    OP_TAB["TIXR"].opcode = "B8";
    OP_TAB["TIXR"].format = 2;
    OP_TAB["TIXR"].exists = true;

    OP_TAB["WD"].opcode = "DC";
    OP_TAB["WD"].format = 3;
    OP_TAB["WD"].exists = true;
}

void regtab_init()
{
    REG_TAB["A"].number = '0';
    REG_TAB["A"].exists = true;

    REG_TAB["X"].number = '1';
    REG_TAB["X"].exists = true;

    REG_TAB["L"].number = '2';
    REG_TAB["L"].exists = true;

    REG_TAB["B"].number = '3';
    REG_TAB["B"].exists = true;

    REG_TAB["S"].number = '4';
    REG_TAB["S"].exists = true;

    REG_TAB["T"].number = '5';
    REG_TAB["T"].exists = true;

    REG_TAB["F"].number = '6';
    REG_TAB["F"].exists = true;

    REG_TAB["PC"].number = '8';
    REG_TAB["PC"].exists = true;

    REG_TAB["SW"].number = '9';
    REG_TAB["SW"].exists = true;
}