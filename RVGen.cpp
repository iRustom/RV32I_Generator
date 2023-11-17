#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>

using namespace std;

int generator()
{
    int instruction = 0;
    int opcode = rand() % 10;

    // opcode = 5;

    switch (opcode)
    {
    case 0: // R-type
    {
        int rd = rand() % 32;
        int rs1 = rand() % 32;
        int rs2 = rand() % 32;

        int funct3 = rand() % 8;
        int funct7 = rand() % 2; // either 0 or 1 for 31st bit

        /* tests
        rd = 0;
        rs1 = 0;
        rs2 = 2;
        funct3 = 0;
        funct7 = 1;
        */

        instruction = 0b0110011 | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (0b00000 << 25) | (funct7 << 30) | (0b0 << 31);

        switch (funct3)
        {
        case 0:
        {
            if (funct7 == 0)
            {
                cout << "add x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            }
            else
            {
                cout << "sub x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            }
            break;
        }
        case 1:
        {
            cout << "sll x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 2:
        {
            cout << "slt x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 3:
        {
            cout << "sltu x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 4:
        {
            cout << "xor x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 5:
        {
            if (funct7 == 0)
            {
                cout << "srl x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            }
            else
            {
                cout << "sra x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            }
            break;
        }
        case 6:
        {
            cout << "or x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 7:
        {
            cout << "and x" << rd << ", x" << rs1 << ", x" << rs2 << " - " << bitset<32>(instruction) << endl;
            break;
        }

        default:
            return 0;
        }

        break;
    }
    case 1: // I-type
    {
        int rd = rand() % 32;
        int rs1 = rand() % 32;
        int rs2 = rand() % 32;

        int funct3 = rand() % 8;
        int imm = rand() % 8192 - 4096; // -4096 to 4095
        instruction = 0b0010011 | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm << 20);

        switch (funct3)
        {
        case 0:
        {
            cout << "addi x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 1:
        {
            cout << "slli x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 2:
        {
            cout << "slti x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 3:
        {
            if (imm < 0)
            {
                imm += 4096;
            }
            instruction = 0b0010011 | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm << 20);
            cout << "sltiu x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 4:
        {
            cout << "xori x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 5:
        {
            if (imm < 32)
            {
                cout << "srli x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            }
            else
            {
                cout << "srai x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            }
            break;
        }
        case 6:
        {
            cout << "ori x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 7:
        {
            cout << "andi x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }

        default:
            return 0;
        }

        break;
    }
    case 2: // Loads
    {
        int rd = rand() % 32;
        int rs1 = rand() % 32;
        int rs2 = rand() % 32;

        int funct3_1 = rand() % 3;
        int funct3_2 = rand() % 2 + 4;

        int choose = rand() % 2;
        int funct3;

        if (choose == 0)
        {
            funct3 = funct3_1;
        }
        else
        {
            funct3 = funct3_2;
        }

        int imm = rand() % 8192 - 4096;

        instruction = 0b0000011 | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm << 20);

        switch (funct3)
        {
        case 0:
        {
            cout << "lb x" << rd << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }
        case 1:
        {
            cout << "lh x" << rd << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }
        case 2:
        {
            cout << "lw x" << rd << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }
        case 4:
        {
            if (imm < 0)
            {
                imm += 4096;
            }
            instruction = 0b0000011 | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm << 20);
            cout << "lbu x" << rd << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }
        case 5:
        {
            if (imm < 0)
            {
                imm += 4096;
            }
            instruction = 0b0000011 | (rd << 7) | (funct3 << 12) | (rs1 << 15) | (imm << 20);
            cout << "lhu x" << rd << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }
        default:
            return 0;
        }
        break;
    }
    case 3: // Stores
    {
        int rs1 = rand() % 32;
        int rs2 = rand() % 32;

        int funct3 = rand() % 3;
        int imm = rand() % 8192 - 4096;

        instruction = 0b0100011 | ((imm & 0b11111) << 7) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (((imm & 0b111111100000) >> 5) << 25);

        switch (funct3)
        {
        case 0:
        {
            cout << "sb x" << rs2 << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }
        case 1:
        {
            cout << "sh x" << rs2 << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }
        case 2:
        {
            cout << "sw x" << rs2 << ", " << imm << "(x" << rs1 << ") - " << bitset<32>(instruction) << endl;
            break;
        }

        default:
            return 0;
        }

        break;
    }
    case 4: // Branches
    {
        int rs1 = rand() % 32;
        int rs2 = rand() % 32;

        int funct3_1 = rand() % 2;
        int funct3_2 = rand() % 4 + 4;

        int choose = rand() % 2;
        int funct3;

        if (choose == 0)
        {
            funct3 = funct3_1;
        }
        else
        {
            funct3 = funct3_2;
        }

        int imm = rand() % 8192 - 4096;
        imm <<= 1;
        instruction = 0b1100011 | (((imm & 0b010000000000) >> 11) << 7) | (((imm & 0b11110) >> 1) << 8) | (funct3 << 12) | (rs1 << 15) | (rs2 << 20) | (((imm & 0b001111110000) >> 5) << 25) | (((imm & 0b100000000000) >> 12) << 31);

        switch (funct3)
        {
        case 0:
        {
            cout << "beq x" << rs1 << ", x" << rs2 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 1:
        {
            cout << "bne x" << rs1 << ", x" << rs2 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 4:
        {
            cout << "blt x" << rs1 << ", x" << rs2 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 5:
        {
            cout << "bge x" << rs1 << ", x" << rs2 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 6:
        {
            if (imm < 0)
            {
                imm += 8192;
            }
            cout << "bltu x" << rs1 << ", x" << rs2 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }
        case 7:
        {
            if (imm < 0)
            {
                imm += 8192;
            }
            cout << "bgeu x" << rs1 << ", x" << rs2 << ", " << imm << " - " << bitset<32>(instruction) << endl;
            break;
        }

        default:
            return 0;
        }

        break;
    }
    case 5: // JAL
    {
        int rd = rand() % 32;
        int imm = rand() % 2097152 - 1048576;
        imm <<= 1;

        instruction = 0b1101111 | (rd << 7) | (imm & 0xFF000) | (((imm >> 11) & 0b1) << 20) | (((imm >> 1) & 0b1111111111) << 21) | ((imm >> 20) & 0b1) << 31;

        cout << "jal x" << rd << ", " << imm << " - " << bitset<32>(instruction) << endl;

        break;
    }
    case 6: // JALR
    {
        int rd = rand() % 32;
        int rs1 = rand() % 32;
        int imm = rand() % 8192 - 4096;

        instruction = 0b1100111 | (rd << 7) | (0b000 << 12) | (rs1 << 15) | (imm << 20);

        cout << "jalr x" << rd << ", x" << rs1 << ", " << imm << " - " << bitset<32>(instruction) << endl;

        break;
    }
    case 7: // LUI
    {
        int rd = rand() % 32;
        int imm = rand() % 1048576;

        instruction = 0b0110111 | (rd << 7) | (imm << 12);

        cout << "lui x" << rd << ", " << imm << " - " << bitset<32>(instruction) << endl;

        break;
    }
    case 8: // AUIPC
    {
        int rd = rand() % 32;
        int imm = rand() % 1048576;

        instruction = 0b0010111 | (rd << 7) | (imm << 12);

        cout << "auipc x" << rd << ", " << imm << " - " << bitset<32>(instruction) << endl;

        break;
    }
    case 9: // ecall and ebreak
    {
        int funct7 = rand() % 2;

        if (funct7 == 0)
        {
            instruction = 0b1110011;
            cout << "ecall - " << bitset<32>(instruction) << endl;
        }
        else
        {
            instruction = 0b1110011 | (funct7 << 20);
            cout << "ebreak - " << bitset<32>(instruction) << endl;
        }

        break;
    }

    default:
        return 0;
    }

    return instruction;
}

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    int n;

    do
    {
        cout << "Enter the number of instructions to generate: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            generator();
        }
        cout << "\nEnter 1 to generate more instructions or 0 to exit: ";
        cin >> n;
    } while (n == 1);

    return 0;
}