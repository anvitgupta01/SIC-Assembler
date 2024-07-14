#include <bits/stdc++.h>
using namespace std;

void regtab_init();

#include "structures.h"
#include "functions.h"
#include "initializers.h"

void preprocess(ifstream &in)
{
    set<char> oprtr;
    oprtr.insert('+');
    oprtr.insert('-');
    oprtr.insert('*');
    oprtr.insert('@');
    oprtr.insert('/');
    oprtr.insert('#');
    oprtr.insert(',');
    oprtr.insert('\'');
    oprtr.insert('=');
    ofstream fout("preprocess.txt");
    string s, str, temp;
    while (getline(in, s))
    {
        stringstream sfg(s);
        sfg >> temp;
        if (temp[0] != '.')
        {
            int len = s.length();
            for (int i = 0; i < len - 1; i++)
            {
                if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/')
                {
                    s.insert(i + 1, 1, ' ');
                    i++;
                }
            }
            bool fk = false;
            for (int i = 0; i < s.length() - 1; i++)
            {
                if (s[i] == ',' && s[i + 1] != ' ')
                {
                    s.insert(i + 1, 1, ' ');
                }
            }
            str = s;
            for (int i = 0; i < s.length(); i++)
            {
                fk = (s[i] == '\'') ? !fk : fk;
                if (!fk)
                {
                    str[i] = (char)toupper(s[i]);
                }
            }
            stringstream ss(str);
            while (ss >> s)
            {
                if (oprtr.find(s[0]) == oprtr.end())
                {
                    if (oprtr.find(s[s.length() - 1]) == oprtr.end())
                    {
                        fout << s << " ";
                    }
                    else
                    {
                        fout << s.substr(0, s.length() - 1) << " " << s[s.length() - 1];
                    }
                }
                else
                {
                    if (s.length() == 1)
                        fout << s;
                    else
                        fout << s << " ";
                }
            }
            fout << "\n";
        }
    }
}

void pass1(ifstream &in, ofstream &ferror, bool &error)
{
    string label, opcode, operand, tempstr, csect_name = "DEFAULT";
    int curr = 0;
    int operand_val = 0, line = 0;
    while (getline(in, tempstr))
    {
        curr = CSECT[csect_name].LOCCTR;
        label = opcode = operand = "";
        bool bn4 = false;
        line++;
        stringstream ss1(tempstr);
        ss1 >> label;
        if (label[0] == '+' && OP_TAB[label.substr(1, label.length() - 1)].exists)
        {
            bn4 = true;
            label = label.substr(1, label.length() - 1);
        }
        if (OP_TAB[label].exists || ASM_DIR[label])
        {
            opcode = label;
            label = "";
            getline(ss1, operand);
        }
        else
        {
            ss1 >> opcode;
            getline(ss1, operand);
        }
        if (opcode[0] == '+')
        {
            bn4 = true;
            opcode = opcode.substr(1, opcode.length() - 1);
        }
        if (operand[0] == ' ')
        {
            int index646 = 0;
            while (operand[index646] == ' ')
                index646++;
            operand = operand.substr(index646, operand.length() - index646);
        }
        if (opcode == "START")
        {
            ss1.clear();
            ss1 << operand;
            ss1 >> operand;
            CSECT[csect_name].start = convertHexToDec(operand);
            CSECT[csect_name].name = label;
            CSECT[csect_name].LOCCTR = convertHexToDec(operand);
        }
        else if (opcode == "CSECT")
        {

            for (auto ele : CSECT[csect_name].LIT_TAB)
            {
                if (ele.second.write)
                {
                    CSECT[csect_name].LIT_TAB[ele.first].address = CSECT[csect_name].LOCCTR;
                    CSECT[csect_name].LOCCTR += (ele.second.value.length() / 2);
                    CSECT[csect_name].LIT_TAB[ele.first].write = false;
                }
            }
            CSECT[csect_name].length = CSECT[csect_name].LOCCTR - CSECT[csect_name].start;

            csect_name = label;
            CSECT[csect_name].name = label;
        }
        else
        {
            if (label.length() != 0)
            {
                if (CSECT[csect_name].SYM_TAB[label].exists)
                {
                    error = true;
                    ferror << "ERROR LINE:" << line << " duplicate symbol " << label << "\n";
                }
                else
                {
                    CSECT[csect_name].SYM_TAB[label].address = curr;
                    CSECT[csect_name].SYM_TAB[label].exists = true;
                    CSECT[csect_name].SYM_TAB[label].isRelative = true;
                }
            }
            if (opcode == "END")
            {
                for (auto ele : CSECT[csect_name].LIT_TAB)
                {
                    if (ele.second.write)
                    {
                        CSECT[csect_name].LIT_TAB[ele.first].address = CSECT[csect_name].LOCCTR;
                        CSECT[csect_name].LOCCTR += (ele.second.value.length() / 2);
                        CSECT[csect_name].LIT_TAB[ele.first].write = false;
                    }
                }
                CSECT[csect_name].length = CSECT[csect_name].LOCCTR - CSECT[csect_name].start;
                return;
            }
            else if (OP_TAB[opcode].exists)
            {
                CSECT[csect_name].LOCCTR += OP_TAB[opcode].format;
                if (bn4)
                    CSECT[csect_name].LOCCTR++;
                if (operand.length() != 0)
                {
                    string str640;
                    stringstream ss213(operand);
                    ss213 >> str640;
                    if (str640[0] == '=')
                    {
                        if (str640[1] == 'C')
                        {
                            int index = 3;
                            string val = "";
                            int ch637;
                            while (index < str640.length() && (str640[index] != '\'' && str640[index] != ' '))
                            {
                                ch637 = (int)str640[index];
                                string te640 = convertDecToHex(ch637);
                                changeString(te640, 2);
                                val += te640;
                                index++;
                            }
                            if (!CSECT[csect_name].LIT_TAB[val].exists)
                            {
                                CSECT[csect_name].LIT_TAB[val].value = val;
                                CSECT[csect_name].LIT_TAB[val].write = true;
                                CSECT[csect_name].LIT_TAB[val].exists = true;
                            }
                        }
                        else if (str640[1] == 'X')
                        {
                            int index = 3;
                            string val = "";
                            while (index < str640.length() && (str640[index] != '\'' && str640[index] != ' '))
                            {
                                val += str640[index];
                                index++;
                            }
                            if (!CSECT[csect_name].LIT_TAB[val].exists)
                            {
                                CSECT[csect_name].LIT_TAB[val].value = val;
                                CSECT[csect_name].LIT_TAB[val].exists = true;
                                CSECT[csect_name].LIT_TAB[val].write = true;
                            }
                        }
                        else
                        {
                            error = true;
                            ferror << "ERROR LINE:" << line << " undefined literal type\n";
                        }
                    }
                }
            }
            else if (opcode == "LTORG")
            {
                for (auto ele : CSECT[csect_name].LIT_TAB)
                {
                    if (ele.second.write)
                    {
                        CSECT[csect_name].LIT_TAB[ele.first].address = CSECT[csect_name].LOCCTR;
                        CSECT[csect_name].LOCCTR += (ele.second.value.length() / 2);
                        CSECT[csect_name].LIT_TAB[ele.first].write = false;
                    }
                }
            }
            else if (opcode == "EQU")
            {
                if (label.length() != 0)
                {
                    CSECT[csect_name].SYM_TAB[label].exists = true;
                    CSECT[csect_name].SYM_TAB[label].isRelative = false;
                    if (operand[0] == '*')
                    {
                        CSECT[csect_name].SYM_TAB[label].address = curr;
                    }
                    else
                    {
                        int tval = 0, ab = 0;
                        eval_operand(operand, ab, error, ferror, tval, csect_name, line);
                        CSECT[csect_name].SYM_TAB[label].address = tval;
                    }
                }
                else
                {
                    error = true;
                    ferror << "ERROR LINE:" << line << " Label Expeted for EQU directive \n";
                }
            }
            else if (opcode == "ORG")
            {
                if (operand.length() != 0)
                {
                    int abs = 0, temp12 = 0;
                    eval_operand(operand, abs, error, ferror, temp12, csect_name, line);
                    CSECT[csect_name].ORG_STACK.push(curr);
                    CSECT[csect_name].LOCCTR = temp12;
                }
                else
                {
                    if (!CSECT[csect_name].ORG_STACK.empty())
                    {
                        int temp12 = CSECT[csect_name].ORG_STACK.top();
                        CSECT[csect_name].ORG_STACK.pop();
                        CSECT[csect_name].LOCCTR = temp12;
                    }
                    else
                    {
                        error = true;
                        ferror << "ERROR: The ORG stack is empty\n";
                    }
                }
            }
            else if (opcode == "WORD")
            {
                CSECT[csect_name].LOCCTR += 3;
            }
            else if (opcode == "BYTE")
            {
                string s731 = convertQuote(operand, line, error, ferror);
                CSECT[csect_name].LOCCTR += (s731.length() / 2);
            }
            else if (opcode == "RESW")
            {
                int temp733 = 0;
                int abs738 = 0;
                eval_operand(operand, abs738, error, ferror, temp733, csect_name, line);
                CSECT[csect_name].LOCCTR += 3 * temp733;
                if (abs738 != 0)
                {
                    error = true;
                    ferror << "ERROR: LINE" << line << " expression is not absolute value\n";
                }
            }
            else if (opcode == "RESB")
            {
                int temp736 = 0;
                int abs742 = 0;
                eval_operand(operand, abs742, error, ferror, temp736, csect_name, line);
                CSECT[csect_name].LOCCTR += temp736;
                if (abs742 != 0)
                {
                    error = true;
                    ferror << "ERROR: LINE" << line << " expression is not absolute value\n";
                }
            }
            else if (opcode == "EXTDEF" || opcode == "BASE" || opcode == "NOBASE")
            {
            }
            else if (opcode == "EXTREF")
            {
                stringstream ss803(operand);
                string tem804;
                while (ss803 >> tem804)
                {
                    if (tem804[0] == ',')
                        tem804 = tem804.substr(1, tem804.length() - 1);
                    CSECT[csect_name].EXTREF_TAB[tem804].exists = true;
                    CSECT[csect_name].EXTDEF_TAB[tem804].name = tem804;
                }
            }
            else
            {
                error = true;
                ferror << "ERROR LINE:" << line << " INVALID OPERATION CODE\n";
            }
        }
        if (label.length() > 6)
        {
            error = true;
            ferror << "ERROR LINE:" << line << " used " << label << " with length more than 6\n";
        }
    }
}

void pass2(ifstream &in, ofstream &ferror, bool &error, ofstream &ou)
{
    ofstream LFile("Listing_File.txt");
    LFile << "LINE" << "  LOCCTR  INSTRUCTION           OBJECT CODE\n";
    string H;
    vector<string> T;
    string tempT = "";
    vector<string> D;
    string tempD = "";
    vector<string> R;
    string tempR = "";
    vector<string> M;
    string tempM = "";
    string E;
    string label, opcode, operand, tempstr, csect_name = "DEFAULT", obj_code;
    int curr = 0;
    int operand_val = 0, line = 0;
    int locctr = 0;
    int LEN = 0, ni = 0, xbpe = 0;
    while (getline(in, tempstr))
    {
        obj_code = "";
        ni = 0;
        xbpe = 0;
        curr = locctr;
        label = opcode = operand = "";
        bool bn4 = false;
        line++;
        obj_code += to_string(line) + "  ";
        obj_code += convertDecToHex(locctr) + "  ";
        obj_code += tempstr;
        stringstream ss1(tempstr);
        ss1 >> label;
        if (label[0] == '+' && OP_TAB[label.substr(1, label.length() - 1)].exists)
        {
            bn4 = true;
            label = label.substr(1, label.length() - 1);
        }
        if (OP_TAB[label].exists || ASM_DIR[label])
        {
            opcode = label;
            label = "";
            getline(ss1, operand);
        }
        else
        {
            ss1 >> opcode;
            getline(ss1, operand);
        }
        if (opcode[0] == '+')
        {
            bn4 = true;
            opcode = opcode.substr(1, opcode.length() - 1);
        }
        if (operand[0] == ' ')
        {
            int index646 = 0;
            while (operand[index646] == ' ')
                index646++;
            operand = operand.substr(index646, operand.length() - index646);
        }
        if (opcode == "START")
        {
            ss1.clear();
            ss1 << operand;
            ss1 >> operand;
            locctr = convertHexToDec(operand);
            H += "H";
            if (label.length() > 6)
            {
                error = true;
                ferror << "ERROR LINE:" << line << " expecting 6 character program name\n";
            }
            string tem43 = CSECT[csect_name].name;
            for (int i = 1; i <= 6 - CSECT[csect_name].name.length(); i++)
            {
                tem43 += " ";
            }
            H = H + tem43;
            string t88 = convertDecToHex(locctr);
            changeString(t88, 6);
            H += t88;
            LEN = 0;
        }
        else if (opcode == "CSECT")
        {
            for (auto ele : CSECT[csect_name].LIT_TAB)
            {
                if (ele.second.write)
                {
                    if (tempT.length() == 0)
                    {
                        tempT = "T";
                        string te88 = convertDecToHex(curr);
                        changeString(te88, 6);
                        tempT += te88;
                    }
                    CSECT[csect_name].LIT_TAB[ele.first].address = locctr;
                    LFile << line << "  " << convertDecToHex(locctr) << " * =X\'" << ele.second.value << "\'" << "    " << ele.second.value << endl;
                    curr = locctr;
                    locctr += (ele.second.value.length() / 2);
                    LEN += ele.second.value.length() / 2;
                    CSECT[csect_name].LIT_TAB[ele.first].write = false;

                    if (tempT.length() + ele.second.value.length() <= 67)
                    {
                        tempT += ele.second.value;
                    }
                    else
                    {
                        int va901 = tempT.length() - 7;
                        string h902 = convertDecToHex(va901 / 2);
                        changeString(h902, 2);
                        tempT.insert(7, 1, h902[0]);
                        tempT.insert(8, 1, h902[1]);
                        T.push_back(tempT);
                        tempT.clear();
                        tempT = "T";
                        string te88 = convertDecToHex(curr);
                        changeString(te88, 6);
                        tempT += te88;
                        tempT += ele.second.value;
                    }
                }
            }

            string len87 = convertDecToHex(LEN);
            changeString(len87, 6);
            H = H + len87;
            E += "E";
            if (csect_name == "DEFAULT")
            {
                string tem86 = "", temp836 = convertDecToHex(CSECT[csect_name].start);
                for (int i = 1; i <= (6 - temp836.length()); i++)
                {
                    tem86 += "0";
                }
                E = E + tem86 + temp836;
            }

            ou << H << "\n";
            for (auto i : D)
                ou << i << "\n";
            if (tempD.length() != 0)
                ou << tempD << "\n";
            for (auto i : R)
                ou << i << "\n";
            if (tempR.length() != 0)
                ou << tempR << "\n";
            for (auto i : T)
                ou << i << "\n";
            if (tempT.length() != 0)
            {
                int va901 = tempT.length() - 7;
                va901 /= 2;
                string h902 = convertDecToHex(va901);
                changeString(h902, 2);
                tempT.insert(7, 1, h902[0]);
                tempT.insert(8, 1, h902[1]);
                ou << tempT << "\n";
            }
            for (auto i : M)
                ou << i << "\n";
            ou << E << "\n";
            H.clear();
            T.clear();
            D.clear();
            R.clear();
            M.clear();
            E.clear();
            tempD.clear();
            tempT.clear();
            tempM.clear();
            tempR.clear();
            locctr = 0;
            csect_name = label;
            if (operand.length() != 0)
                ferror << "ERROR LINE:" << line << " expected no operand for CSECT \n";
            LEN = 0;
            H += "H";
            if (label.length() > 6)
            {
                error = true;
                ferror << "ERROR LINE:" << line << " expecting 6 character program name\n";
            }
            string tem43 = CSECT[csect_name].name;
            for (int i = 1; i <= 6 - CSECT[csect_name].name.length(); i++)
            {
                tem43 += " ";
            }
            H = H + tem43;
            H += "000000";
        }
        else
        {
            if (opcode == "END")
            {
                for (auto ele : CSECT[csect_name].LIT_TAB)
                {
                    if (ele.second.write)
                    {
                        if (tempT.length() == 0)
                        {
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                        }
                        CSECT[csect_name].LIT_TAB[ele.first].address = locctr;
                        LFile << line << "  " << convertDecToHex(locctr) << " * =X\'" << ele.second.value << "\'" << "    " << ele.second.value << endl;
                        curr = locctr;
                        locctr += (ele.second.value.length() / 2);
                        LEN += ele.second.value.length() / 2;
                        CSECT[csect_name].LIT_TAB[ele.first].write = false;

                        if (tempT.length() + ele.second.value.length() <= 67)
                        {
                            tempT += ele.second.value;
                        }
                        else
                        {
                            int va901 = tempT.length() - 7;
                            va901 /= 2;
                            string h902 = convertDecToHex(va901);
                            changeString(h902, 2);
                            tempT.insert(7, 1, h902[0]);
                            tempT.insert(8, 1, h902[1]);
                            T.push_back(tempT);
                            tempT.clear();
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                            tempT += ele.second.value;
                        }
                    }
                }
                string len87 = convertDecToHex(LEN);
                changeString(len87, 6);
                H = H + len87;
                E += "E";
                if (csect_name == "DEFAULT")
                {
                    string tem86 = "", temp836 = convertDecToHex(CSECT[csect_name].start);
                    for (int i = 1; i <= (6 - temp836.length()); i++)
                    {
                        tem86 += "0";
                    }
                    E = E + tem86 + temp836;
                }
                ou << H << "\n";
                for (auto i : D)
                    ou << i << "\n";
                if (tempD.length() != 0)
                    ou << tempD << "\n";
                for (auto i : R)
                    ou << i << "\n";
                if (tempR.length() != 0)
                    ou << tempR << "\n";
                for (auto i : T)
                    ou << i << "\n";
                if (tempT.length() != 0)
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    ou << tempT << "\n";
                }
                for (auto i : M)
                    ou << i << "\n";
                ou << E << "\n";
                LFile << obj_code << "\n";
                H.clear();
                T.clear();
                D.clear();
                R.clear();
                M.clear();
                E.clear();
                tempD.clear();
                tempT.clear();
                tempM.clear();
                tempR.clear();
                return;
            }
            else if (OP_TAB[opcode].exists)
            {
                curr = locctr;
                string tObj = "";
                locctr += OP_TAB[opcode].format;
                LEN += OP_TAB[opcode].format;
                if (bn4)
                {
                    locctr++;
                    LEN++;
                }
                if (OP_TAB[opcode].format == 1)
                {
                    tObj = OP_TAB[opcode].opcode;
                }
                else if (OP_TAB[opcode].format == 2)
                {
                    tObj = OP_TAB[opcode].opcode;
                    stringstream ss106(operand);
                    string s106;
                    while (ss106 >> s106)
                    {
                        if (s106[0] == ',')
                            s106 = s106.substr(1, s106.length() - 1);
                        if (REG_TAB[s106].exists)
                        {
                            tObj += (char)REG_TAB[s106].number;
                        }
                        else
                        {
                            error = true;
                            ferror << "ERROR LINE:" << line << " The register \'" << s106 << "\' is not valid\n";
                        }
                    }
                    int x = tObj.length();
                    for (int i = 1; i <= 4 - x; i++)
                    {
                        tObj += "0";
                    }
                }
                else if (opcode == "RSUB")
                {
                    tObj = "4F0000";
                    if (bn4)
                        tObj += "00";
                }
                else if (OP_TAB[opcode].format == 3)
                {
                    stringstream ss108(operand);
                    string opr;
                    ss108 >> opr;
                    int opc = convertHexToDec(OP_TAB[opcode].opcode), expr = 0;
                    if (bn4)
                    {             // format 4
                        xbpe = 1; // e=1;
                        if (opr[0] == '@')
                        {
                            ni = 2; // n=1
                            opr = opr.substr(1, opr.length() - 1);
                            string tm = "05";
                            bool indexed = 0;
                            int rel = 0, tempval = 0;
                            string val10 = eval_expression(operand, indexed, error, ferror, csect_name, line, curr, M, tm, rel, tempval);
                            changeString(val10, 5);
                            opc += ni;
                            string st1 = convertDecToHex(opc);
                            changeString(st1, 2);
                            tObj += st1;
                            st1 = convertDecToHex(xbpe);
                            changeString(st1, 1);
                            tObj += st1;
                            tObj += val10;
                            ss108 >> opr;
                            if (opr[1] == 'X')
                            {
                                error = true;
                                ferror << "ERROR LINE:" << line << " cannot use indexed with indirect addressing mode\n";
                            }
                        }
                        else if (operand[0] == '#')
                        {
                            ni = 1;
                            xbpe = 1;
                            opr = opr.substr(1, opr.length() - 1);
                            string tm = "05";
                            bool indexed = 0;
                            int rel = 0, tempval;
                            string val10 = eval_expression(operand, indexed, error, ferror, csect_name, line, curr, M, tm, rel, tempval);
                            changeString(val10, 5);
                            opc += ni;
                            string st1 = convertDecToHex(opc);
                            changeString(st1, 2);
                            tObj += st1;
                            st1 = convertDecToHex(xbpe);
                            changeString(st1, 1);
                            tObj += st1;
                            st1 = convertDecToHex(tempval);
                            changeString(st1, 5);
                            tObj += st1;
                            ss108 >> opr;
                            if (opr[1] == 'X')
                            {
                                error = true;
                                ferror << "ERROR LINE:" << line << " cannot use inedxed with immediate addressing mode\n";
                            }
                        }
                        else
                        {
                            tempM = "M";
                            string t88 = convertDecToHex(curr + 1);
                            changeString(t88, 6);
                            tempM += t88;
                            tempM += "05";
                            ni = 3;
                            xbpe = 1;
                            int val10 = 0;
                            if (CSECT[csect_name].SYM_TAB[opr].exists)
                            {
                                val10 = CSECT[csect_name].SYM_TAB[opr].address;
                                tempM += '+' + CSECT[csect_name].name;
                                M.push_back(tempM);
                                tempM.clear();
                            }
                            else if (CSECT[csect_name].EXTREF_TAB[opr].exists)
                            {
                                val10 = 0;
                                tempM += '+' + opr;
                                M.push_back(tempM);
                                tempM.clear();
                            }
                            else
                            {
                                error = true;
                                ferror << "ERROR LINE:" << line << " Invalid operand \n";
                            }
                            ss108 >> opr;
                            if (opr[1] == 'X')
                            {
                                xbpe += 8;
                            }
                            opc += ni;
                            string st1 = convertDecToHex(opc);
                            changeString(st1, 2);
                            tObj += st1;
                            st1 = convertDecToHex(xbpe);
                            changeString(st1, 1);
                            tObj += st1;
                            st1 = convertDecToHex(val10);
                            changeString(st1, 5);
                            tObj += st1;
                        }
                    }
                    else
                    {
                        string tm = "03";
                        int val = 0, opc;
                        opc = convertHexToDec(OP_TAB[opcode].opcode);
                        stringstream ss117(operand);
                        string opr;
                        ss117 >> opr;
                        if (opr[0] == '@')
                        {
                            ni = 2;
                            int tval = 0;
                            opr = opr.substr(1, opr.length() - 1);
                            if (CSECT[csect_name].SYM_TAB[opr].exists)
                            {
                                val = CSECT[csect_name].SYM_TAB[opr].address;
                                val = val - locctr;
                                if (val >= 2048 || val < -2048)
                                {
                                    if (CSECT[csect_name].base.length() != 0)
                                    {
                                        tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                        val = val + locctr - tval;
                                        if (val < 0 || val > 4095)
                                        {
                                            error = true;
                                            ferror << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                        }
                                        else
                                        {
                                            xbpe += 4;
                                        }
                                    }
                                    else
                                    {
                                        error = true;
                                        ferror << "ERROR LINE:" << line << " disp out of bounds for PC relative" << "\n";
                                    }
                                }
                                else
                                {
                                    xbpe += 2;
                                }
                            }
                            else if (CSECT[csect_name].EXTREF_TAB[opr].exists)
                            {
                                tempM = "M";
                                string t88 = convertDecToHex(curr + 1);
                                changeString(t88, 6);
                                tempM += t88;
                                tempM += tm;
                                tempM += '+';
                                tempM += opr;
                                if (opr.length() > 6)
                                {
                                    error = true;
                                    ferror << "ERROR LINE:" << line << " length of operand more than 6\n";
                                }
                                M.push_back(tempM);
                                tempM.clear();
                            }
                            else
                            {
                                error = true;
                                ferror << "ERROR LINE:" << line << " operand " << opr << " not defined\n";
                            }
                            ss117 >> opr;
                        }
                        else if (opr[0] == '#')
                        {
                            ni = 1;
                            opr = opr.substr(1, opr.length() - 1);
                            bool indexed = false;
                            int rel = 0, tempval = 0;
                            string val12 = eval_expression(operand, indexed, error, ferror, csect_name, line, curr, M, tm, rel, tempval);
                            if (rel == 0)
                            {
                                if (tempval > 2047 || tempval < -2048)
                                {
                                    error = true;
                                    ferror << "ERROR LINE:" << line << " The value exceeds 3 half bytes\n";
                                }
                                val = tempval;
                            }
                            else
                            {
                                int tval = 0;
                                val = tempval - locctr;
                                if (val > 2047 || val < -2048)
                                {
                                    if (CSECT[csect_name].base.length() != 0)
                                    {
                                        tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                        val = val + locctr - tval;
                                        if (val < 0 || val > 4095)
                                        {
                                            error = true;
                                            ferror << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                        }
                                        else
                                        {
                                            xbpe += 4;
                                        }
                                    }
                                    else
                                    {
                                        error = true;
                                        ferror << "ERROR LINE:" << line << " disp out of bounds for PC relative" << "\n";
                                    }
                                }
                                else
                                {
                                    xbpe += 2;
                                }
                            }
                            if (indexed)
                            {
                                error = true;
                                ferror << "ERROR LINE:" << line << " indexed with immediate not allowed\n";
                            }
                        }
                        else
                        {
                            ni = 3;
                            if (opr[0] == '=')
                            {
                                if (opr[1] == 'C')
                                {
                                    int index = 3;
                                    string val12 = "";
                                    int ch637;
                                    while (index < opr.length() && (opr[index] != '\'' && opr[index] != ' '))
                                    {
                                        ch637 = (int)opr[index];
                                        string te640 = convertDecToHex(ch637);
                                        changeString(te640, 2);
                                        val12 += te640;
                                        index++;
                                    }
                                    if (!CSECT[csect_name].LIT_TAB[val12].write)
                                    {
                                        CSECT[csect_name].LIT_TAB[val12].write = true;
                                    }
                                    val = CSECT[csect_name].LIT_TAB[val12].address;
                                }
                                else if (opr[1] == 'X')
                                {
                                    int index = 3;
                                    string val12 = "";
                                    while (index < opr.length() && (opr[index] != '\'' && opr[index] != ' '))
                                    {
                                        val12 += opr[index];
                                        index++;
                                    }
                                    if (!CSECT[csect_name].LIT_TAB[val12].write)
                                    {
                                        CSECT[csect_name].LIT_TAB[val12].write = true;
                                    }
                                    val = CSECT[csect_name].LIT_TAB[val12].address;
                                }
                                int tval = 0;
                                val = val - locctr;
                                if (val > 2047 || val < -2048)
                                {
                                    if (CSECT[csect_name].base.length() != 0)
                                    {
                                        tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                        val = val + locctr - tval;
                                        if (val < 0 || val > 4095)
                                        {
                                            error = true;
                                            ferror << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                        }
                                        else
                                        {
                                            xbpe += 4;
                                        }
                                    }
                                    else
                                    {
                                        error = true;
                                        ferror << "ERROR LINE:" << line << " disp out of bounds for PC relative" << "\n";
                                    }
                                }
                                else
                                {
                                    xbpe += 2;
                                }
                            }
                            else
                            {
                                bool indexed = false;
                                int rel = 0, tempval = 0;
                                string val1 = eval_expression(operand, indexed, error, ferror, csect_name, line, curr, M, tm, rel, tempval);
                                if (rel == 0)
                                {
                                    if (tempval > 2047 || tempval < -2048)
                                    {
                                        error = true;
                                        ferror << "ERROR LINE:" << line << " disp value out of bounds\n";
                                    }
                                    else
                                    {
                                        val = tempval;
                                    }
                                }
                                else
                                {
                                    int tval = 0;
                                    val = tempval - locctr;
                                    if (val > 2047 || val < -2048)
                                    {
                                        if (CSECT[csect_name].base.length() != 0)
                                        {
                                            tval = CSECT[csect_name].SYM_TAB[CSECT[csect_name].base].address;
                                            val = val + locctr - tval;
                                            if (val < 0 || val > 4095)
                                            {
                                                error = true;
                                                ferror << "ERROR LINE:" << line << " disp out of bounds for BASE relative\n";
                                            }
                                            else
                                            {
                                                xbpe += 4;
                                            }
                                        }
                                        else
                                        {
                                            error = true;
                                            ferror << "ERROR LINE:" << line << " disp out of bounds for PC relative" << "\n";
                                        }
                                    }
                                    else
                                    {
                                        xbpe += 2;
                                    }
                                }
                                if (indexed)
                                    xbpe += 8;
                            }
                        }
                        opc += ni;
                        string sti = convertDecToHex(opc);
                        changeString(sti, 2);
                        tObj += sti;
                        sti = convertDecToHex(xbpe);
                        changeString(sti, 1);
                        tObj += sti;
                        sti = convertDecToHex(val);
                        changeString(sti, 3);
                        tObj += sti;
                    }
                }

                obj_code += "  " + tObj;
                if (tempT.length() == 0)
                {
                    tempT = "T";
                    string t88 = convertDecToHex(curr);
                    changeString(t88, 6);
                    tempT += t88;
                }
                if (tempT.length() + tObj.length() <= 67)
                {
                    tempT += tObj;
                }
                else
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                    tempT += tObj;
                }
            }
            else if (opcode == "LTORG")
            {
                for (auto ele : CSECT[csect_name].LIT_TAB)
                {
                    if (ele.second.write)
                    {
                        if (tempT.length() == 0)
                        {
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                        }
                        CSECT[csect_name].LIT_TAB[ele.first].address = locctr;
                        LFile << line << "  " << convertDecToHex(locctr) << " * =X\'" << ele.second.value << "\'" << "    " << ele.second.value << endl;
                        curr = locctr;
                        locctr += (ele.second.value.length() / 2);
                        LEN += ele.second.value.length() / 2;
                        CSECT[csect_name].LIT_TAB[ele.first].write = false;

                        if (tempT.length() + ele.second.value.length() <= 67)
                        {
                            tempT += ele.second.value;
                        }
                        else
                        {
                            int va901 = tempT.length() - 7;
                            string h902 = convertDecToHex(va901 / 2);
                            changeString(h902, 2);
                            tempT.insert(7, 1, h902[0]);
                            tempT.insert(8, 1, h902[1]);
                            T.push_back(tempT);
                            tempT.clear();
                            tempT = "T";
                            string te88 = convertDecToHex(curr);
                            changeString(te88, 6);
                            tempT += te88;
                            tempT += ele.second.value;
                        }
                    }
                }
            }
            else if (opcode == "EQU")
            {
            }
            else if (opcode == "ORG")
            {
                if (operand.length() != 0)
                {
                    int abs = 0, temp12 = 0;
                    eval_operand(operand, abs, error, ferror, temp12, csect_name, line);
                    CSECT[csect_name].ORG_STACK.push(curr);
                    locctr = temp12;
                }
                else
                {
                    if (!CSECT[csect_name].ORG_STACK.empty())
                    {
                        int temp12 = CSECT[csect_name].ORG_STACK.top();
                        CSECT[csect_name].ORG_STACK.pop();
                        locctr = temp12;
                    }
                    else
                    {
                        error = true;
                        ferror << "ERROR: The ORG stack is empty\n";
                    }
                }
            }
            else if (opcode == "WORD")
            {
                string tm = "06";
                bool indexed = 0;
                int rel = 0, tempval;
                string val1157 = eval_expression(operand, indexed, error, ferror, csect_name, line, locctr, M, tm, rel, tempval);
                changeString(val1157, 6);
                obj_code += " " + val1157;
                if (tempT.length() == 0)
                {
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                }
                if (tempT.length() + 6 <= 67)
                {
                    tempT += val1157;
                }
                else
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                    tempT += val1157;
                }
                locctr += 3;
                LEN += 3;
            }
            else if (opcode == "BYTE")
            {
                string s731 = convertQuote(operand, line, error, ferror);
                locctr += (s731.length() / 2);
                LEN += (s731.length() / 2);
                if (tempT.length() == 0)
                {
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                }
                if (tempT.length() + s731.length() <= 67)
                {
                    tempT += s731;
                }
                else
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                    tempT = "T";
                    string te88 = convertDecToHex(curr);
                    changeString(te88, 6);
                    tempT += te88;
                    tempT += s731;
                }
                obj_code += " " + s731;
            }
            else if (opcode == "RESW")
            {
                if (tempT.length() != 0)
                {

                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                }
                int temp733 = 0;
                int abs738 = 0;
                eval_operand(operand, abs738, error, ferror, temp733, csect_name, line);
                locctr += 3 * temp733;
                LEN += 3 * temp733;
                if (abs738 != 0)
                {
                    error = true;
                    ferror << "ERROR: LINE" << line << " expression is not absolute value\n";
                }
            }
            else if (opcode == "RESB")
            {
                if (tempT.length() != 0)
                {
                    int va901 = tempT.length() - 7;
                    va901 /= 2;
                    string h902 = convertDecToHex(va901);
                    changeString(h902, 2);
                    tempT.insert(7, 1, h902[0]);
                    tempT.insert(8, 1, h902[1]);
                    T.push_back(tempT);
                    tempT.clear();
                }
                int temp736 = 0;
                int abs742 = 0;
                eval_operand(operand, abs742, error, ferror, temp736, csect_name, line);
                cout << temp736 << endl;
                locctr += temp736;
                LEN += temp736;
                if (abs742 != 0)
                {
                    error = true;
                    ferror << "ERROR: LINE" << line << " expression is not absolute value\n";
                }
            }
            else if (opcode == "EXTDEF")
            {
                string sd27;
                if (tempD.length() == 0)
                    tempD = "D";
                stringstream ss102(operand);
                while (ss102 >> sd27)
                {
                    if (sd27[0] == ',')
                        sd27 = sd27.substr(1, sd27.length() - 1);
                    string strd103 = sd27;
                    if (CSECT[csect_name].SYM_TAB[sd27].exists)
                    {
                        string valu103 = convertDecToHex(CSECT[csect_name].SYM_TAB[sd27].address);
                        changeString(valu103, 6);
                        for (int i = 1; i <= 6 - sd27.length(); i++)
                            strd103 += " ";
                        strd103 += valu103;
                        if (tempD.length() + 12 <= 73)
                        {
                            tempD += strd103;
                        }
                        else
                        {
                            D.push_back(tempD);
                            tempD.clear();
                            tempD = "D";
                            tempD += strd103;
                        }
                    }
                    else
                    {
                        error = true;
                        ferror << "ERROR LINE:" << line << " Undefined symbol" << sd27 << "\n";
                    }
                }
            }
            else if (opcode == "EXTREF")
            {
                string sd27;
                if (tempR.length() == 0)
                    tempR = "R";
                stringstream ss102(operand);
                while (ss102 >> sd27)
                {
                    if (sd27[0] == ',')
                        sd27 = sd27.substr(1, sd27.length() - 1);
                    string strr10 = sd27;
                    for (int i = 1; i <= 6 - sd27.length(); i++)
                        strr10 += " ";
                    if (tempR.length() + 6 <= 73)
                    {
                        tempR += strr10;
                    }
                    else
                    {
                        R.push_back(tempR);
                        tempR.clear();
                        tempR = "R";
                        tempR += strr10;
                    }
                }
            }
            else if (opcode == "BASE")
            {
                stringstream ss102(operand);
                ss102 >> operand;
                if (CSECT[csect_name].SYM_TAB[operand].exists)
                    CSECT[csect_name].base = operand;
                else
                {
                    error = true;
                    ferror << "ERROR LINE:" << line << " undefined symbol " << operand << endl;
                }
            }
            else if (opcode == "NOBASE")
            {
                CSECT[csect_name].base = "";
            }
            else
            {
                error = true;
                ferror << "ERROR LINE:" << line << " INVALID OPERATION CODE\n";
            }
        }
        if (label.length() > 6)
        {
            error = true;
            ferror << "ERROR LINE:" << line << " used " << label << " with length more than 6\n";
        }
        LFile << obj_code << "\n";
    }
}

int main()
{
    regtab_init();
    optab_init();
    asmdir_init();
    ifstream in("input.txt");
    ofstream ferror("errors.txt");
    ofstream ou("output.txt");
    if (!in)
    {
        cout << "ERROR: could not open input file" << endl;
        exit(1);
    }
    if (!ou)
    {
        cout << "ERROR: could not open output file" << endl;
        exit(1);
    }
    preprocess(in);
    in.close();
    cout << ".\n.Preprocessing\n.\n";
    in.open("preprocess.txt");
    bool error = false;
    cout << ".\nPASS1 Starting\n.\n";
    ferror << "PASS1:\n";
    pass1(in, ferror, error);
    in.close();
    in.open("preprocess.txt");
    cout << error << " End of pass1 \n";

    cout << ".\nPASS2 Starting\n.\n";
    ferror << "PASS2:\n";
    pass2(in, ferror, error, ou);
    cout << error << " End of pass2 \n";
    ofstream fout("TABLES.txt");
    for (auto cs : CSECT)
    {
        fout << "---------------------------------------------------------------\n";
        fout << cs.second.name << " START:" << cs.second.start << " LENGTH:" << cs.second.length << " LOCCTR:" << cs.second.LOCCTR << "\n";
        fout << "SYMBOL TABLE\n";
        for (auto st : cs.second.SYM_TAB)
        {
            if (st.second.exists)
                fout << "NAME: " << st.first << " Address: " << st.second.address << " IsRelative: " << st.second.isRelative << "\n";
        }
        fout << "\nLITERAL TABLE\n";
        for (auto lt : cs.second.LIT_TAB)
        {
            fout << "NAME:" << lt.first << "  VALUE: " << lt.second.value << "    ADDRESS: " << lt.second.address << "    WRITE: " << lt.second.write << "\n";
        }
    }
    fout.close();
    in.close();
    ferror.close();
    ou.close();
    return 0;
}