#include <iostream>
#include <string.h>
#include <map>
#include <algorithm>
#include <set>

// For storing the validity of an instruction : bool will represent validity and string will be the corresponding message.
typedef std::pair<bool, std::string> pbs;

#define FALSE false
#define TRUE true

// Below include all the messages used for defining the validity or invalidity of an instruction
#define VALID_SIC "Valid SIC instruction"
#define VALID_SIC_XE "Valid SIC-XE instruction"
#define LENGTH_ERROR "Invalid length of instruction... Give instruction of length 1 byte, 2 bytes, 3 bytes or 4 bytes "
#define INPUT_ERROR "Input is not in hexadecimal... Give input involving hexadecimal characters, which are 0 to 9 or A to F or a to f "
#define INSTRUCTION_NOT_FOUND_ERROR "No such opcode : False opcode... The opcode is not present in SIC and SIC-XE"
#define REGISTER_NOT_SUPPORTED "The register mentioned is not present in either SIC or SIC-XE"
#define OPCODE_NOT_IN_FORMAT "The opcode is not present in the format : No such instruction"
#define OPCODE_NOT_IN_SIC "The opcode is not present in SIC"
#define INDEX_SET_WITH_IMMEDIATE "x = 1 with immediate mode but indexing cannot be used with immediate mode"
#define INDEX_SET_WITH_INDIRECT "x = 1 with indirect mode but indexing cannot be used with indirect mode"
#define b_AND_p_BOTH_ARE_SET "Both b and p bits are set"
#define FORMAT_3_VALUE_E_1 "e is set to 1 but in format 3, it must be 0"
#define FORMAT_4_VALUE_E_0 "e is set to 0 but in format 4, it must be 1"
#define FORMAT_4_b_SET_TO_1 "b = 1 in format 4"
#define FORMAT_4_p_SET_TO_1 "p = 1 in format 4"
#define SIC_NOT_SUPPORT_4_BYTES "SIC doesn't support 4 bytes"
#define RSUB_ALL_BITS_TO_ZERO "rsub used with non-zero bits except opcode bits"
#define SVC_HAVE_0_AT_R2 "r2 is not set to accumulator. \"SVC\" always have r2 as accumulator"
#define CLEAR_HAVE_0_AT_R2 "r2 is not set to accumulator. \"CLEAR\" always have r2 as accumulator"
#define TIXR_HAVE_0_AT_R2 "r2 is not set to accumulator. \"TIXR\" always have r2 as accumulator"

// Character table stores the encoding for differnet characters in hexadecimal format.
std ::map<char, int> CHARACTER_ENCODE = {
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'A', 10},
    {'B', 11},
    {'C', 12},
    {'D', 13},
    {'E', 14},
    {'F', 15}};

// The opcode table or OPTAB will store opcodes in hexadecimal, their formats and boolean value for only present in SIC-XE
// boolean value is 1 if the opcode is only supported in SIC-XE and not in SIC.
std::map<std ::string, std::pair<int, bool>> OPTAB = {
    {"18", {3, 0}},
    {"58", {3, 1}},
    {"90", {2, 1}},
    {"40", {3, 0}},
    {"B4", {2, 1}},
    {"28", {3, 0}},
    {"88", {3, 1}},
    {"A0", {2, 1}},
    {"24", {3, 0}},
    {"64", {3, 1}},
    {"9C", {2, 1}},
    {"C4", {1, 1}},
    {"C0", {1, 1}},
    {"F4", {1, 1}},
    {"3C", {3, 0}},
    {"30", {3, 0}},
    {"34", {3, 0}},
    {"38", {3, 0}},
    {"48", {3, 0}},
    {"00", {3, 0}},
    {"68", {3, 1}},
    {"50", {3, 0}},
    {"70", {3, 1}},
    {"08", {3, 0}},
    {"6C", {3, 1}},
    {"74", {3, 1}},
    {"04", {3, 0}},
    {"D0", {3, 1}},
    {"20", {3, 0}},
    {"60", {3, 1}},
    {"98", {2, 1}},
    {"C8", {1, 1}},
    {"44", {3, 0}},
    {"D8", {3, 0}},
    {"AC", {2, 1}},
    {"4C", {3, 0}},
    {"A4", {2, 1}},
    {"A8", {2, 1}},
    {"F0", {1, 1}},
    {"EC", {3, 1}},
    {"0C", {3, 0}},
    {"78", {3, 1}},
    {"54", {3, 0}},
    {"80", {3, 1}},
    {"D4", {3, 1}},
    {"14", {3, 0}},
    {"7C", {3, 1}},
    {"E8", {3, 0}},
    {"84", {3, 1}},
    {"10", {3, 0}},
    {"1C", {3, 0}},
    {"5C", {3, 1}},
    {"94", {2, 1}},
    {"B0", {2, 1}},
    {"E0", {3, 0}},
    {"F8", {1, 1}},
    {"2C", {3, 0}},
    {"B8", {2, 1}},
    {"DC", {3, 0}}};

// Function declarations apart from main()
void start();
pbs checkValidate(std::string);

int main()
{
    int x;

    std::cout << '\n';
    std::cout << "Enter 1 to start and 0 to terminate." << '\n';

    std::cin >> x;

    std::cout << '\n';

    if (x == 1)
    {
        std::cout << "Note : Entering -1 for any instruction input will terminate the program." << '\n';
        std::cout << '\n';
        start();
    }

    return 0;
}

// The start function will start the input and output process from the terminal
// After this, user is able to enter the instruction to check for validity
void start()
{
    std::string instruction;

    while (true)
    {
        std ::cout << "Enter the instruction in hexadecimal format to be validated for being a SIC or SIC-XE instruction " << '\n';

        std::cin >> instruction;

        // The terminating instruction will be -1
        // If -1, then the user no longer have new instructions to enter and calls exit for start function to end the input-output processes from terminal.
        if (instruction == "-1")
        {
            return;
        }

        auto [valid, message] = checkValidate(instruction);

        if (valid)
        {
            std ::cout << message << '\n'
                       << '\n';
        }
        else
        {
            std ::cout << "Invalid instruction : " << message << '\n'
                       << '\n';
        }
    }
}

// Actual validity checking function
pbs checkValidate(std ::string instruction)
{
    int size_inst = instruction.size();

    // SIC only supports 3 bytes and SIC-XE only supports 1 byte, 2 bytes, 3 bytes and 4 bytes instructions
    if (size_inst != 2 && size_inst != 4 && size_inst != 6 && size_inst != 8)
    {
        return {FALSE, LENGTH_ERROR};
    }

    // Preprocessing : Convert all the characters in the instruction to upper-case
    transform(instruction.begin(), instruction.end(), instruction.begin(), ::toupper);

    // Check that input characters must be the valid hexadecimal characters
    char ch;
    for (int i = 0; i < size_inst; ++i)
    {
        ch = instruction[i];

        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F'))
        {
            continue;
        }
        else
        {
            return {FALSE, INPUT_ERROR};
        }
    }

    std::string res = "\n";
    bool status = TRUE;

    // If the instruction is of 1 byte
    if (size_inst == 2)
    {
        auto x = OPTAB.find(instruction);

        // If the opcode is not supported in both SIC and SIC-XE
        if (x == OPTAB.end())
        {
            if (status)
                status = FALSE;
            res += INSTRUCTION_NOT_FOUND_ERROR;
            res += '\n';
        }

        int format = (x->second).first;
        bool valid_sic_xe = (x->second).second;

        // Format of 1 byte instruction opcode, must be 1, and it must be an SIC-XE instruction
        if (format == 1 && valid_sic_xe)
        {
            if (status)
                return {TRUE, VALID_SIC_XE};
        }
        else
        {
            if (status)
                status = FALSE;
            res += OPCODE_NOT_IN_FORMAT;
            res += '\n';
        }
    }

    // If the instruction is of 2 bytes
    else if (size_inst == 4)
    {
        std ::string opcode = instruction.substr(0, 2);

        // Special case of SCV, CLEAR and TIXR instructions
        if (opcode == "B0" || opcode == "B8" || opcode == "B4")
        {
            // In all the three instructions, always r2 is set to 0 or accumulator.
            if (instruction[3] == '0' && instruction[2] <= '9' && instruction[2] >= '0' && instruction[2] != '7')
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                if (instruction[3] != '0')
                {
                    if (opcode == "B0")
                        res += SVC_HAVE_0_AT_R2;
                    else if (opcode == "B4")
                        res += CLEAR_HAVE_0_AT_R2;
                    else
                        res += TIXR_HAVE_0_AT_R2;
                    res += '\n';
                }
                if (instruction[2] <= '9' && instruction[2] >= '0' && instruction[2] != '7')
                {
                }
                else
                {
                    res += REGISTER_NOT_SUPPORTED;
                    res += '\n';
                }
            }

            return {FALSE, res};
        }

        // Special case of SHIFTL and SHIFTR instructions
        // The r1 can be any of the supported register and r2 can be any value in 0 to F (hex).
        if (opcode == "A4" || opcode == "A8")
        {
            ch = instruction[2];

            if (ch >= '0' && ch <= '9' && ch != '7')
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += REGISTER_NOT_SUPPORTED;
                res += '\n';
            }
            return {FALSE, res};
        }

        auto x = OPTAB.find(opcode);

        // If the opcode is not supported in both SIC and SIC-XE
        if (x == OPTAB.end())
        {
            if (status)
                status = FALSE;
            res += INSTRUCTION_NOT_FOUND_ERROR;
            res += '\n';
        }

        int format = (x->second).first;
        bool valid_sic_xe = (x->second).second;

        // Format must be 2 for 2 bytes instruction and it must be an SIC-XE instruction
        if (format == 2 && valid_sic_xe)
        {
            // Register indexes must be supported in SIC-XE
            if (instruction[2] >= '0' && instruction[2] <= '9' && instruction[2] != '7' && instruction[3] >= '0' && instruction[3] <= '9' && instruction[3] != '7')
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += REGISTER_NOT_SUPPORTED;
                res += '\n';
            }
        }

        else
        {
            if (status)
                status = FALSE;
            res += OPCODE_NOT_IN_FORMAT;
            res += '\n';
        }
    }
    else if (size_inst == 6)
    {
        std ::string opcode = instruction.substr(0, 2);

        // Special case of RSUB instruction in SIC.
        if (opcode == "4C")
        {
            if (instruction == "4C0000")
            {
                if (status)
                    return {TRUE, VALID_SIC};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += RSUB_ALL_BITS_TO_ZERO;
                res += '\n';
            }
            return {FALSE, res};
        }

        // Special case of RSUB (format 3) instruction in SIC-XE
        if (opcode == "4F")
        {
            if (instruction == "4F0000")
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += RSUB_ALL_BITS_TO_ZERO;
                res += '\n';
            }
            return {FALSE, res};
        }

        // Calculate the opcode from the OPTAB
        auto x = OPTAB.upper_bound(opcode);
        --x;

        std ::string act_opcode = x->first;

        // idx will represent the n and i value together in decimal
        int idx = CHARACTER_ENCODE.find(opcode[1])->second - CHARACTER_ENCODE.find(act_opcode[1])->second;

        int format = (x->second).first;
        bool valid_inst = (x->second).second;

        // Format of the opcode must be 3 in 3 bytes instructions
        if (format != 3)
        {
            if (status)
                status = FALSE;
            res += OPCODE_NOT_IN_FORMAT;
            res += '\n';
        }

        // The third character in instruction will denote xbpe bits
        int xbpe = CHARACTER_ENCODE.find(instruction[2])->second;

        // If it is SIC-XE and the e = 1, then error in format 3
        if (idx && xbpe % 2)
        {
            if (status)
                status = FALSE;
            res += FORMAT_3_VALUE_E_1;
            res += '\n';
        }

        // If n = i = 0 : SIC instruction
        if (idx == 0)
        {

            if (valid_inst)
            {
                if (status)
                    status = FALSE;
                res += OPCODE_NOT_IN_SIC;
                res += '\n';
            }
            else
            {
                if (status)
                    return {TRUE, VALID_SIC};
            }
        }

        // If n = 0, i = 1 : immediate addressing
        else if (idx == 1)
        {
            if (xbpe == 2 || xbpe == 0 || xbpe == 4)
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                // If indexing is also used
                if ((1 << 3 & xbpe) != 0)
                {
                    if (status)
                        status = FALSE;
                    res += INDEX_SET_WITH_IMMEDIATE;
                    res += '\n';
                }
                else
                {
                    if (status)
                        status = FALSE;
                    res += b_AND_p_BOTH_ARE_SET;
                    res += '\n';
                }
            }
        }

        // If n = 1, i = 0 : indirect addressing
        else if (idx == 2)
        {
            if (xbpe == 2 || xbpe == 0 || xbpe == 4)
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                // If indexing also used
                if ((1 << 3 & xbpe) != 0)
                {
                    if (status)
                        status = FALSE;
                    res += INDEX_SET_WITH_INDIRECT;
                    res += '\n';
                }
                else
                {
                    if (status)
                        status = FALSE;
                    res += b_AND_p_BOTH_ARE_SET;
                    res += '\n';
                }
            }
        }

        // If n = i = 1 : simple addressing
        else if (idx == 3)
        {
            if (xbpe == 0 || xbpe == 2 || xbpe == 4 || xbpe == 8 || xbpe == 10 || xbpe == 12)
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += b_AND_p_BOTH_ARE_SET;
                res += '\n';
            }
        }

        else
        {
            if (status)
                status = FALSE;
            res += OPCODE_NOT_IN_FORMAT;
            res += '\n';
        }
    }

    // If instruction is of 4 bytes
    else if (size_inst == 8)
    {
        std ::string opcode = instruction.substr(0, 2);

        // Handling RSUB (4 bytes) instruction of SIC
        if (opcode == "4C")
        {
            if (status)
                status = FALSE;
            res += OPCODE_NOT_IN_FORMAT;
            res += '\n';
            return {FALSE, res};
        }

        // Handling RSUB (Format 4) instruction in SIC
        if (opcode == "4F")
        {
            // e bit must be 1
            if (instruction == "4F000000")
            {
                if (status)
                    status = FALSE;
                res += FORMAT_4_VALUE_E_0;
                res += '\n';
            }
            else if (instruction == "4F100000")
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += RSUB_ALL_BITS_TO_ZERO;
                res += '\n';
            }
            return {FALSE, res};
        }

        // Find the opcode from OPTAB
        auto x = OPTAB.upper_bound(opcode);
        --x;

        std ::string act_opcode = x->first;

        // idx will represent n and i bits together in decimal
        int idx = CHARACTER_ENCODE.find(opcode[1])->second - CHARACTER_ENCODE.find(act_opcode[1])->second;

        int format = (x->second).first;
        bool valid_inst = (x->second).second;

        // Format must be 4... as all the format 4 opcodes will have format 3 also, no distinction between them.
        if (format != 3)
        {
            if (status)
                status = FALSE;
            res += OPCODE_NOT_IN_FORMAT;
            res += '\n';
        }

        // Third character in the instruction will represent the xbpe bits.
        int xbpe = CHARACTER_ENCODE.find(instruction[2])->second;

        // e must be 1 in format 4
        if (xbpe % 2 == 0)
        {
            if (status)
                status = FALSE;
            res += FORMAT_4_VALUE_E_0;
            res += '\n';
        }

        // p must be 0 in format 4
        if ((1 << 1 & xbpe) != 0)
        {
            if (status)
                status = FALSE;
            res += FORMAT_4_p_SET_TO_1;
            res += '\n';
        }

        // b must be 0 in format 4
        if ((1 << 2 & xbpe) != 0)
        {
            if (status)
                status = FALSE;
            res += FORMAT_4_b_SET_TO_1;
            res += '\n';
        }

        // If n = i = 0 : SIC instruction
        if (idx == 0)
        {
            if (status)
                status = FALSE;
            res += SIC_NOT_SUPPORT_4_BYTES;
            res += '\n';
        }

        // If n = 0, i = 1 : immediate addressing
        else if (idx == 1)
        {
            // if x is 0
            if ((1 << 3 & xbpe) == 0)
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += INDEX_SET_WITH_IMMEDIATE;
                res += '\n';
            }
        }

        // if n = 1, i = 0 : indirect addressing
        else if (idx == 2)
        {
            // if x is 0
            if ((1 << 3 & xbpe) == 0)
            {
                if (status)
                    return {TRUE, VALID_SIC_XE};
            }
            else
            {
                if (status)
                    status = FALSE;
                res += INDEX_SET_WITH_INDIRECT;
                res += '\n';
            }
        }

        // if n = 1, i = 1 : simple addressing
        else if (idx == 3)
        {
            if (status)
                return {TRUE, VALID_SIC_XE};
        }

        else
        {
            if (status)
                status = FALSE;
            res += OPCODE_NOT_IN_FORMAT;
            res += '\n';
        }
    }

    return {FALSE, res};
}