struct optab_struct
{
    int format;
    bool exists;
    string opcode;
    optab_struct()
    {
        format = -1;
        exists = false;
        opcode = "FF";
    }
};

struct symtab_struct
{
    int address;
    bool exists;
    bool isRelative;
    symtab_struct()
    {
        address = -3;
        exists = false;
        isRelative = false;
    }
};

struct REG_TAB_struct
{
    int value;
    bool exists;
    char number;
    REG_TAB_struct()
    {
        value = 0;
        exists = false;
        number = -1;
    }
};

struct littab2_struct
{
    int address;
    string value;
    bool write;
    bool exists;
    littab2_struct()
    {
        address = 0;
        value = "";
        write = false;
        exists = false;
    }
};

struct extdef_struct
{
    string name;
    string address;
    bool exists;
    extdef_struct()
    {
        name = "undefined";
        address = "0";
        exists = false;
    }
};

struct extref_struct
{
    string name;
    bool exists;
    extref_struct()
    {
        name = "undefined";
        exists = false;
    }
};

struct csect_struct
{
    int LOCCTR;
    int section_number;
    int length;
    int start;
    string name;
    string base;
    stack<int> ORG_STACK;
    map<string, extdef_struct> EXTDEF_TAB;
    map<string, extref_struct> EXTREF_TAB;
    map<string, symtab_struct> SYM_TAB;
    map<string, littab2_struct> LIT_TAB;
    csect_struct()
    {
        regtab_init();
        LOCCTR = 0;
        section_number = 0;
        length = 0;
        start = 0;
        name = "DEFAULT";
        base = "";
    }
};

map<string, optab_struct> OP_TAB;
map<string, REG_TAB_struct> REG_TAB;
map<string, csect_struct> CSECT;
map<string, bool> ASM_DIR;