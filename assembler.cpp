#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
typedef int ADDRESS;
typedef string INST, OPCODE, REG_NAME, REG_NUM, LABEL, ASSEM_DIR, INST;

unordered_map<INST, OPCODE> OPTAB = {
    {"ADD", "00011000"},
    {"AND", "01000000"},
    {"DIV", "00100100"},
    {"LDA", "00000000"},
    {"LDCH", "01010000"},
    {"LDL", "00001000"},
    {"LDX", "00000100"},
    {"MUL", "00100000"},
    {"OR", "01000100"},
    {"STA", "00001100"},
    {"STCH", "01010100"},
    {"STL", "00010100"},
    {"STX", "00010000"},
    {"SUB", "00011100"},
    {"TIX", "00101100"},
    {"RSUB", "01001100"}};

unordered_map<REG_NAME, REG_NUM> REGTAB = {
    {"A", "00"},
    {"X", "01"},
    {"L", "10"},
    {"PC", "8"},
    {"SW", "9"}};

unordered_set<ASSEM_DIR> DIRECTIVE = {
    "START", "END", "RESW", "RESB", "BYTE", "WORD"};

int LOCCTR = 0;

bool success = true;

unordered_map<LABEL, ADDRESS> SYMTAB;

void pass1Assembler();
void pass2Assembler();
void labelAssembly(string);
vector<string> separator(string);
string assemble(string);
string address_Resolve(string, vector<string>&, int);
string int_to_bin(int);

int main()
{
    pass1Assembler();

    if(success == false) {
        cout << "Error in Parse 1 " << endl;
        return 1;
    }

    pass2Assembler();

    if(success = false) {
        cout << "Error in parse 2 " << endl;
        return 1;
    }
    
    return 0;
}

void pass1Assembler()
{
    fstream file;
    file.open("example.txt", ios::in);

    if (!file)
    {
        success = false;
        cout << "We are unable to open file... Check that if it exists or not " << endl;
        return;
    }

    string asmbly_inst;
    while (getline(file, asmbly_inst))
    {
        if(asmbly_inst.size())
            labelAssembly(asmbly_inst);
    }

    file.close();
}

void labelAssembly(string asmbly_inst)
{
    vector<string> words = separator(asmbly_inst);

    if ((OPTAB.find(words[0]) == OPTAB.end()) && (DIRECTIVE.find(words[0]) == DIRECTIVE.end()))
    {
        SYMTAB[words[0]] = LOCCTR;

        if (OPTAB.find(words[1]) != OPTAB.end())
        {
            LOCCTR += 3;
        }
        else
        {
            if (words[1] == "START")
            {
                LOCCTR = 0;
            }
            else if (words[1] == "WORD")
            {
                LOCCTR += 3;
            }
            else if (words[1] == "BYTE")
            {
                string s = words[2];
                int n = s.size();
                for (int i = 3; i < words.size(); i++)
                {
                    n += 1 + words[i].size();
                }

                if (s[0] == 'C')
                {

                    LOCCTR += n - 3;
                }
                else if (s[0] == 'X')
                {
                    LOCCTR += (n - 3) / 2;
                }
            }
            else if (words[1] == "RESB")
            {
                int x = stoi(words[2]);
                LOCCTR += x;
            }
            else if (words[1] == "RESW")
            {
                int x = 3 * (stoi(words[2]));
                LOCCTR += x;
            }
            else if (words[1] == "END")
            {
                // Do nothing
            }
        }
    }
    else if (OPTAB.find(words[0]) != OPTAB.end())
    {
        LOCCTR += 3;
    }
    else
    {
        if (words[0] == "START")
        {
            LOCCTR = 0;
        }
        else if (words[0] == "WORD")
        {
            LOCCTR += 3;
        }
        else if (words[0] == "BYTE")
        {
            string s = words[1];
            int n = s.size();
            for (int i = 2; i < words.size(); i++)
            {
                n += 1 + words[i].size();
            }

            if (s[0] == 'C')
            {
                LOCCTR += n - 3;
            }
            else if (s[0] == 'X')
            {
                LOCCTR += (n - 3) / 2;
            }
        }
        else if (words[0] == "RESB")
        {
            int x = stoi(words[1]);
            LOCCTR += x;
        }
        else if (words[0] == "RESW")
        {
            int x = 3 * (stoi(words[1]));
            LOCCTR += x;
        }
        else if (words[0] == "END")
        {
            // Do nothing
        }
    }
} 

vector<string> separator(string asmbly_inst)
{
    int i = 0;
    while ((i < asmbly_inst.size()) && (asmbly_inst[i] == ' '))
    {
        i++;
    }

    asmbly_inst = asmbly_inst.substr(i);

    transform(asmbly_inst.begin(), asmbly_inst.end(), asmbly_inst.begin(), ::toupper);

    vector<string> words;
    stringstream ss(asmbly_inst);
    string word;

    while (getline(ss, word, ' '))
    {
        if (word.size())
            words.push_back(word);
    }

    return words;
}

void pass2Assembler()
{
    fstream file;
    fstream file_o;
    file.open("example.txt", ios::in);
    file_o.open("output.txt", ios::out);

    if (!file)
    {
        success = false;
        cout << "We are unable to open file... Check that if it exists or not " << endl;
        return;
    }

    if (!file_o)
    {
        success = false;
        cout << "Cannot open output file.. Please fix the issue " << endl;
        return;
    }

    string asmbly_inst;
    while (getline(file, asmbly_inst))
    {
        if(asmbly_inst.size()) {
            string asmble_inst = assemble(asmbly_inst);
            file_o << asmble_inst << endl;
        }
    }

    file.close();
    file_o.close();
}

string assemble(string asmbly_inst)
{
    string asmble_inst = "";

    vector<string> words = separator(asmbly_inst);

    if (OPTAB.find(words[0]) == OPTAB.end() && DIRECTIVE.find(words[0]) == DIRECTIVE.end())
    {
        if (OPTAB.find(words[1]) != OPTAB.end())
        {
            asmble_inst += OPTAB[words[1]];
            string addr = address_Resolve(asmbly_inst, words, 2);
            asmble_inst += addr;
        }
    }
    else if (OPTAB.find(words[0]) != OPTAB.end())
    {
        asmble_inst += OPTAB[words[0]];
        string addr = address_Resolve(asmbly_inst, words, 1);
        asmble_inst += addr;
    }
    else
    {
        // do nothing
    }

    return asmble_inst;
}

string address_Resolve(string asmbly_inst, vector<string> &words, int idx)
{
    string bin_addr = "";

    // Handling RSUB instruction
    if (idx == words.size())
    {
        return "0000000000000000";
    }

    string s = words[idx];
    int n = s.size();

    if (s[n - 1] == 'X' && s[n - 2] == ',')
    {
        bin_addr += "1";
        s = s.substr(0, n - 2);
    }
    else
    {
        bin_addr += "0";
    }

    int x = SYMTAB[s];

    string addr = int_to_bin(x);

    while (addr.size() < 15)
    {
        addr = "0" + addr;
    }

    bin_addr += addr;

    return bin_addr;
}

string int_to_bin(int x)
{
    string bin_addr = "";
    while (x > 0)
    {
        int y = x % 2;
        x >>= 1;

        bin_addr = to_string(y) + bin_addr;
    }
    return bin_addr;
}
