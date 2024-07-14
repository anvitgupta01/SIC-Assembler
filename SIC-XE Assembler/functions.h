void changeString(string &s, int size)
{
    if (s.length() > size)
    {
        s = s.substr(s.length() - size, size);
    }
    else
    {
        string temp = "";
        for (int i = 1; i <= (size - s.length()); i++)
        {
            temp += "0";
        }
        temp += s;
        s = temp;
    }
}

int convertHexToDec(string hexString)
{
    stringstream stream;
    int dec;
    stream << hexString;
    stream >> hex >> dec;
    return dec;
}

int convertStringToInt(string str)
{
    int value;
    stringstream(str) >> value;
    return value;
}

string convertDecToHex(int decimal)
{
    stringstream stream2;
    stream2 << hex << decimal;
    string result(stream2.str());
    char resultUpper[10];
    strcpy(resultUpper, result.c_str());
    for (int i = 0; i < strlen(resultUpper); i++)
    {
        resultUpper[i] = toupper(resultUpper[i]);
    }
    return resultUpper;
}

string convertHexToBin(string text)
{
    int no = 0;
    string binaryResult = "";
    for (int i = 0; i < text.length(); i++)
    {
        string temp = "";
        if (text[i] >= '0' && text[i] <= '9')
        {
            no = int(text[i]) - 48;
            while (no > 0)
            {
                temp += char(no % 2 + 48);
                no /= 2;
            }
            while (temp.length() != 4)
            {
                temp += '0';
            }
            no = 0;
        }
        else
        {
            no = text[i] - 'A' + 10;
            while (no > 0)
            {
                temp += char(no % 2 + 48);
                no /= 2;
            }
        }
        for (int j = 3; j >= 0; j--)
        {
            binaryResult += temp[j];
        }
    }
    return binaryResult;
}

string convertBinToHex(string binText)
{
    stringstream res;
    string binary_str(binText);
    bitset<12> set(binary_str);
    res << hex << uppercase << set.to_ulong();
    return res.str();
}

bool all_num(string x)
{
    bool iall_num = true;
    int i = 0;
    while (all_num && (i < x.length()))
    {
        iall_num &= isdigit(x[i++]);
    }
    return iall_num;
}

void eval_operand(string s, int &abs, bool &error, ofstream &ferror, int &temp_value, string csect_name, int line)
{
    string str = "", operand;
    temp_value = 0;
    if (s[0] == 'X')
    {
        int ind = 1;
        while (s[ind] != '\'')
            ind++;
        ind++;
        while (s[ind] != ' ')
            str += s[ind++];
        temp_value = convertHexToDec(str);
    }
    else
    {
        stringstream ss(s);
        ss >> operand;
        if (all_num(operand))
        {
            temp_value += stoi(operand);
        }
        else if (CSECT[csect_name].SYM_TAB[operand].exists)
        {
            temp_value += CSECT[csect_name].SYM_TAB[operand].address;
            abs++;
        }
        else
        {
            error = true;
            abs += 1000;
            ferror << "ERROR: LINE" << line << " " << operand << " is not defined in symbol table\n";
        }
        while (ss >> operand)
        {
            char oprtr = operand[0];
            operand = operand.substr(1, operand.length() - 1);
            switch (oprtr)
            {
            case '+':
                if (all_num(operand))
                {
                    temp_value += stoi(operand);
                }
                else if (CSECT[csect_name].SYM_TAB[operand].exists)
                {
                    temp_value += CSECT[csect_name].SYM_TAB[operand].address;
                    abs++;
                }
                else
                {
                    error = true;
                    ferror << "ERROR: LINE" << line << " " << operand << " is not defined in symbol table\n";
                }
                break;
            case '-':
                if (all_num(operand))
                {
                    temp_value -= stoi(operand);
                }
                else if (CSECT[csect_name].SYM_TAB[operand].exists)
                {
                    temp_value -= CSECT[csect_name].SYM_TAB[operand].address;
                    abs--;
                }
                else
                {
                    error = true;
                    ferror << "ERROR: LINE" << line << " " << operand << " is not defined in symbol table\n";
                }
                break;
            case '*':
            case '/':
                error = true;
                ferror << "ERROR: LINE" << line << " " << oprtr << " is not usable in expression\n";
                break;
            default:
                error = true;
                ferror << "ERROR: LINE" << line << " " << oprtr << " is not defined\n";
                break;
            }
        }
    }
}

string eval_expression(string str, bool &indexed, bool &error, ofstream &ferror, string csect_name, int line, int LOC, vector<string> &M, string tm, int &rel, int &tempval)
{
    string res = "";
    rel = 0;
    tempval = 0;
    string operand;
    bool ext = false;
    indexed = false;
    string operand1;
    stringstream ss(str);
    string tempM = "M";
    string t88 = "";
    if (tm == "06")
        t88 = convertDecToHex(LOC);
    else if (tm == "05" || tm == "03")
        t88 = convertDecToHex(LOC + 1);
    else
        t88 = convertDecToHex(LOC);
    changeString(t88, 6);
    tempM += t88;
    tempM += tm;
    ss >> operand;
    operand1 = operand;
    if (operand[0] == '#' || operand[0] == '@')
        operand = operand.substr(1, operand.length() - 1);
    if (all_num(operand))
    {
        tempval += stoi(operand);
    }
    else if (CSECT[csect_name].SYM_TAB[operand].exists)
    {
        tempval += CSECT[csect_name].SYM_TAB[operand].address;
        if (CSECT[csect_name].SYM_TAB[operand].isRelative)
            rel++;
    }
    else if (CSECT[csect_name].EXTREF_TAB[operand].exists)
    {
        ext = true;
        string sir = operand;
        for (int i = 1; i <= 6 - operand.length(); i++)
            sir += " ";
        string str = tempM + "+" + sir;
        M.push_back(str);
    }
    else if (operand[0] == '*' && tm == "06")
    {
        res = t88;
    }
    else
    {
        error = true;
        rel += 1000;
        ferror << "ERROR: LINE" << line << " " << operand << " is not defined \n";
    }

    while (ss >> operand)
    {
        char oprtr = operand[0];
        operand = operand.substr(1, operand.length() - 1);
        switch (oprtr)
        {
        case '+':
            if (all_num(operand))
            {
                tempval += stoi(operand);
            }
            else if (CSECT[csect_name].SYM_TAB[operand].exists)
            {
                tempval += CSECT[csect_name].SYM_TAB[operand].address;
                if (CSECT[csect_name].SYM_TAB[operand].isRelative)
                    rel++;
            }
            else if (CSECT[csect_name].EXTREF_TAB[operand].exists)
            {
                ext = true;
                string sir = operand;
                for (int i = 1; i <= 6 - operand.length(); i++)
                    sir += " ";
                string str = tempM + "+" + sir;
                M.push_back(str);
            }
            else
            {
                error = true;
                rel += 1000;
                ferror << "ERROR: LINE" << line << " " << operand << " is not defined \n";
            }
            break;
        case '-':
            if (all_num(operand))
            {
                tempval -= stoi(operand);
            }
            else if (CSECT[csect_name].SYM_TAB[operand].exists)
            {
                tempval -= CSECT[csect_name].SYM_TAB[operand].address;
                if (CSECT[csect_name].SYM_TAB[operand].isRelative)
                    rel--;
            }
            else if (CSECT[csect_name].EXTREF_TAB[operand].exists)
            {
                ext = true;
                string sir = operand;
                for (int i = 1; i <= 6 - operand.length(); i++)
                    sir += " ";
                string str = tempM + "-" + sir;
                M.push_back(str);
            }
            else
            {
                error = true;
                rel += 1000;
                ferror << "ERROR: LINE" << line << " " << operand << " is not defined \n";
            }
            break;
        case ',':
            if (operand[0] == 'X')
                indexed = true;
            break;
        case '*':
        case '/':
            error = true;
            ferror << "ERROR LINE:" << line << " " << oprtr << "is not usable in the expression\n";
            break;
        default:
            error = true;
            ferror << "ERROR: LINE" << line << " " << oprtr << " is not defined\n";
            break;
        }
    }

    if (!ext && rel == 1)
    {
        string sir = CSECT[csect_name].name;
        for (int i = 1; i <= 6 - operand.length(); i++)
            sir += " ";
        string str = tempM + "+" + sir;
        if (tm == "05")
            M.push_back(str);
    }
    else if (!ext && rel == -1)
    {
        string sir = CSECT[csect_name].name;
        for (int i = 1; i <= 6 - operand.length(); i++)
            sir += " ";
        string str = tempM + "-" + sir;
        if (tm == "05")
            M.push_back(str);
    }
    else if (!ext && abs(rel) > 1)
    {
        error = true;
        ferror << "ERROR LINE:" << line << " Invalid expression \n";
    }
    res = convertDecToHex(tempval);
    return res;
}

string convertQuote(string s, int line, bool &error, ofstream &ferror)
{
    string str = "";
    if (s[0] == 'C')
    {
        int index = 2;
        string val = "", val637 = "";
        int ch637;
        while (index < s.length() && s[index] != '\'' && s[index] != ' ')
        {
            val637 += s[index];
            ch637 = (int)s[index];
            string te640 = convertDecToHex(ch637);
            changeString(te640, 2);
            val += te640;
            index++;
        }
        str = val;
    }
    else if (s[0] == 'X')
    {
        int index = 2;
        while (index < s.length() && s[index] != '\'' && s[index] != ' ')
            str += s[index++];
    }
    else
    {
        error = true;
        ferror << "ERROR LINE:" << line << " undefined literal type\n";
    }
    return str;
}