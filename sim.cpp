#include <bits/stdc++.h>
using namespace std;

string regs[32];
string regs_locs[32];
vector<string> mem_locations, registers_values;
long long int PC_initial, PC;
int for_printing = 1;

string dec_to_bin(string m)
{
    if(m=="")
        return"";
    int n = stoi(m);
    if (n == 0)
        return to_string(0);

    if (n < 0)
    {
        n = 256 + n;
    }

    string bin_val = "";
    while (n > 0)
    {
        bin_val = to_string(n % 2) + bin_val;
        n = n / 2;
    }

    return bin_val;
}
string dec_to_hexa(string m)
{
    if(m=="")
        return"";
    char hexa_val[100];
    int n = stoi(m);

    if (n == 0) return "0";

    int i = 0;
    if (n < 0)
    {
        cout << "-";
        n = abs(n);
    }

    while (n != 0) {

        int temp = 0;
        temp = n % 16;
        if (temp < 10)
        {
            hexa_val[i] = temp + 48;
            i++;
        }

        else
        {
            hexa_val[i] = temp + 55;
            i++;
        }

        n = n / 16;
    }

    string hexa_val2 = "";

    //storing in right order
    for (int j = i - 1; j >= 0; j--)
    {
        hexa_val2 = hexa_val2 + hexa_val[j];
    }

    return hexa_val2;
}

string dec_bin(string n)
{
    int binary[32];

    int i = 0;
    int x = stoi(n);
    while (x > 0)
    {
        binary[i] = x % 2;
        x = x / 2;
        i++;
    }

    string y;
    for (int j = i - 1; j >= 0; j--)
    {
        if (binary[j] == 0)
            y.push_back('0');
        else if (binary[j] == 1)
            y.push_back('1');
    }
    return y;
}
string bin_dec(string n)
{
    int num = stoi(n);
    long long int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return to_string(dec_value);
}
string two_complement(string x)
{
    int checker = 0;
    int temp = x.size()-1;
    for (int i = temp; i >= 0; i--)
    {
        if (checker == 1)
        {
            if (x[i] == 1)
                x.replace(i, 1, "0");
            if (x[i] == 0)
                x.replace(i, 1, "1");
        }
        else
        {
            if (x[i] == 1)
                checker = 1;
        }
    }
    return x;
}
void printAll()
{
    //printing in decimal, binary, and hexadeciaml for bonus point 3
    cout << "Instruction #" << for_printing <<" changes:\n";
    cout << "Program Counter Value: " << PC << "\t" << dec_to_bin(to_string(PC)) << "\t" << dec_to_hexa(to_string(PC));

    for (int i = 0; i < 32; ++i)
    {
        cout << "\nx" << i << ": " << regs[i] << "\t" << dec_to_bin(regs[i]) << "\t" << dec_to_hexa(regs[i]);
    }

    cout << "\n\n Memory relevant contents in decimal:\nLocation\t\tregister";
    for (int i = 0; i < registers_values.size(); ++i)
    {
        cout << "\n" << mem_locations[i] << "\t\t" << registers_values[i];
    }
    cout << endl;
    
    cout << "\n\n Memory relevant contents in binary:\nLocation\t\tregister";
    for (int i = 0; i < registers_values.size(); ++i)
    {
        cout << "\n" << dec_to_bin(mem_locations[i]) << "\t\t" << dec_to_bin(registers_values[i]);
    }
    cout << endl;

    cout << "\n\n Memory relevant contents in hexadecimal:\nLocation\t\tregister";
    for (int i = 0; i < registers_values.size(); ++i)
    {
        cout << "\n" << dec_to_hexa(mem_locations[i]) << "\t\t" << dec_to_hexa(registers_values[i]);
    }
    cout << endl <<endl;
    for_printing++;
}

int main()
{
    regs[0] = "0"; //X0
    string word;

    ifstream data("data.txt", ios::binary);
    while (data >> word)
    {
        if (word == "counter")
        {
            data >> PC_initial;
            PC = PC_initial;
        }
        else if (word[0] == 'x')
        {
            word = word.substr(1);
            data >> regs_locs[stoi(word)];
            data >> regs[stoi(word)];
            
        }
        else
        {
            string temp;
            data >> temp;
            mem_locations.push_back(word);
            registers_values.push_back(temp);
        }
    }
    data.close();

    ifstream test("test.txt", ios::binary);

    int for_pc = 0;
    while (test >> word)
    {
        if (for_pc != 0)
            PC = PC + 4;
        if (word == "ADDI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (temp1[0] == '-')
            {
                temp1 = temp1.substr(1);
                temp2 = 0 - stoi(temp1);
            }
            else
                temp2 = stoi(temp1);
            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) + temp2);
        }
        else if (word == "XORI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp2 = stoi(temp1);

            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) ^ temp2);
        }
        else if (word == "ORI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp2 = stoi(temp1);

            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) | temp2);
        }
        else if (word == "ANDI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp2 = stoi(temp1);

            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) & temp2);
        }
        else if (word == "SLTI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (temp1[0] == '-')
            {
                temp1 = temp1.substr(1);
                temp2 = 0 - stoi(temp1);
            }
            else
                temp2 = stoi(temp1);

            if (stoi(regs[stoi(temp)]) < temp2)
                regs[stoi(word)] = "1";
            else
                regs[stoi(word)] = "0";
        }
        else if (word == "SLTIU")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (temp1[0] == '-')
            {
                temp1 = dec_bin(temp1.substr(1));
                temp1 = two_complement(temp1);
                if (temp1.size() < 32)
                {
                    int i = temp1.size();
                    for (; i < 33; ++i)
                    {
                        temp1.insert(temp1.size()-1, "1");
                    }
                }
                temp1 = bin_dec(temp1);
            }

            temp2 = stoi(temp1);

            if (stoi(regs[stoi(temp)]) < temp2)
                regs[stoi(word)] = "1";
            else
                regs[stoi(word)] = "0";
        }
        else if (word == "LW")
        {
            //LW x5, 0(x6)
        
            string temp, temp1, temp2;

            test >> word >> temp;
            
            word = word.substr(1);
            word.erase(word.size()-1);//5
            
            

            if(temp[0] == '0')
            {
                temp1 = temp.substr(temp.find('x'));
                
                temp1.erase(temp1.size()-1);//x6
                
                int i = 0;
                //for (; i < registers_values.size(); i++)
                //{
                //    if(registers_values[i] == temp1)
                //        break;
                //}
                for (int j = 0; j < temp.size(); ++j) {
                    if (temp[j] == '(')
                        break;
                    else
                        temp2.push_back(temp[j]);
                }
                //string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
                i = 0;
                //for (; i < registers_values.size(); i++)
                //{
                //    if(mem_locations[i] == loc_needed)
                //        break;
                //}
                regs[stoi(word)] = regs[stoi(temp1.substr(1))];
            }
            else
            {
                temp1 = temp.substr(temp.find('x'));
                temp1.erase(temp1.size()-1);//x6
                
                int i = 0;
                for (; i < registers_values.size(); i++)
                {
                    if(registers_values[i] == temp1)
                        break;
                }
                for (int j = 0; j < temp.size(); ++j) 
                {
                    if (temp[j] == '(')
                        break;
                    else
                        temp2.push_back(temp[j]);
                }
                string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
                i = 0;
                for (; i < registers_values.size(); i++)
                {
                    if(mem_locations[i] == loc_needed)
                        break;
                }
                regs[stoi(word)] = registers_values[i];;
            }
        }
        else if (word == "LB")
        {
            string temp, temp1, temp2;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp1 = temp.substr(temp.find('x'));
            temp1.erase(temp1.size()-1);
            
            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(registers_values[i] == temp1)
                    break;
            }
            for (int j = 0; j < temp.size(); ++j) {
                if (temp[j] == '(')
                    break;
                else
                    temp2.push_back(temp[j]);
            }
            string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
            i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(mem_locations[i] == loc_needed)
                    break;
            }
            regs[stoi(word)] = registers_values[i];
        }
        else if (word == "LH")
        {
            string temp, temp1, temp2;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp1 = temp.substr(temp.find('x'));
            temp1.erase(temp1.size()-1);
            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(registers_values[i] == temp1)
                    break;
            }
            for (int j = 0; j < temp.size(); ++j) {
                if (temp[j] == '(')
                    break;
                else
                    temp2.push_back(temp[j]);
            }
            string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
            i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(mem_locations[i] == loc_needed)
                    break;
            }
            regs[stoi(word)] = registers_values[i];
        }
        else if (word == "LBU")
        {
            string temp, temp1, temp2;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp1 = temp.substr(temp.find('x'));
            temp1.erase(temp1.size()-1);
            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(registers_values[i] == temp1)
                    break;
            }
            for (int j = 0; j < temp.size(); ++j) {
                if (temp[j] == '(')
                    break;
                else
                    temp2.push_back(temp[j]);
            }
            string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
            i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(mem_locations[i] == loc_needed)
                    break;
            }
            if (registers_values[i][0] == '-')
                regs[stoi(word)] = registers_values[i].substr(1);
            else
                regs[stoi(word)] = registers_values[i];
        }
        else if (word == "LHU")
        {
            string temp, temp1, temp2;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp1 = temp.substr(temp.find('x'));
            temp1.erase(temp1.size()-1);
            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(registers_values[i] == temp1)
                    break;
            }
            for (int j = 0; j < temp.size(); ++j) {
                if (temp[j] == '(')
                    break;
                else
                    temp2.push_back(temp[j]);
            }
            string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
            i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(mem_locations[i] == loc_needed)
                    break;
            }
            if (registers_values[i][0] == '-')
                regs[stoi(word)] = registers_values[i].substr(1);
            else
                regs[stoi(word)] = registers_values[i];
        }
        else if (word == "SB")
        {
            string temp, temp1, temp2;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);//5

            temp1 = temp.substr(temp.find('x'));
            temp1.erase(temp1.size()-1);//x2

            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(registers_values[i] == temp1)
                    break;
            }
            for (int j = 0; j < temp.size(); ++j) {
                if (temp[j] == '(')
                    break;
                else
                    temp2.push_back(temp[j]);//8
            }
            string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
            i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(mem_locations[i] == loc_needed)
                    break;
            }
            registers_values[i] = regs[stoi(word)];
        }
        else if (word == "SH")
        {
            string temp, temp1, temp2;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);//5

            temp1 = temp.substr(temp.find('x'));
            temp1.erase(temp1.size()-1);//x2

            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(registers_values[i] == temp1)
                    break;
            }
            for (int j = 0; j < temp.size(); ++j) {
                if (temp[j] == '(')
                    break;
                else
                    temp2.push_back(temp[j]);//8
            }
            string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
            i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(mem_locations[i] == loc_needed)
                    break;
            }
            registers_values[i] = regs[stoi(word)];
        }
        else if (word == "SW")
        {
            string temp, temp1, temp2;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);//5

            temp1 = temp.substr(temp.find('x'));
            temp1.erase(temp1.size()-1);//x2

            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(registers_values[i] == temp1)
                    break;
            }
            for (int j = 0; j < temp.size(); ++j) {
                if (temp[j] == '(')
                    break;
                else
                    temp2.push_back(temp[j]);//8
            }
            string loc_needed = to_string(stoi(mem_locations[i]) + (4* stoi(temp2)));
            i = 0;
            for (; i < registers_values.size(); i++)
            {
                if(mem_locations[i] == loc_needed)
                    break;
            }
            registers_values[i] = regs[stoi(word)];
        }
        else if (word == "BEQ")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if ((word == temp) || (regs[stoi(word)] == regs[stoi(temp)]))
            {
                PC = PC + stoi(temp1);
                temp2 = stoi(temp1)/4;
                if (temp2 >= 0)
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                else
                {
                    test.close();
                    test.open("test.txt");
                    temp2 = (PC - PC_initial)/4;
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                }
                PC -= 4;
            }
        }
        else if (word == "BNQ")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (regs[stoi(word)] != regs[stoi(temp)])
            {
                PC = PC + stoi(temp1);
                temp2 = stoi(temp1)/4;
                if (temp2 >= 0)
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                else
                {
                    test.close();
                    test.open("test.txt");
                    temp2 = (PC - PC_initial)/4;
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                }
                PC -= 4;
            }
        }
        else if (word == "BLT")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (stoi(regs[stoi(word)]) < stoi(regs[stoi(temp)]))
            {
                PC = PC + stoi(temp1);
                temp2 = stoi(temp1)/4;
                if (temp2 >= 0)
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                else
                {
                    test.close();
                    test.open("test.txt");
                    temp2 = (PC - PC_initial)/4;
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                }
                PC -= 4;
            }
        }
        else if (word == "BGE")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (stoi(regs[stoi(word)]) >= stoi(regs[stoi(temp)]))
            {
                PC = PC + stoi(temp1);
                temp2 = stoi(temp1)/4;
                if (temp2 >= 0)
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                else
                {
                    test.close();
                    test.open("test.txt");
                    temp2 = (PC - PC_initial)/4;
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                }
                PC -= 4;
            }
        }
        else if (word == "BLTU")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (abs(stoi(regs[stoi(word)])) < abs(stoi(regs[stoi(temp)])))
            {
                PC = PC + stoi(temp1);
                temp2 = stoi(temp1)/4;
                if (temp2 >= 0)
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                else
                {
                    test.close();
                    test.open("test.txt");
                    temp2 = (PC - PC_initial)/4;
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                }
                PC -= 4;
            }
        }
        else if (word == "BGEU")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            if (abs(stoi(regs[stoi(word)])) >= abs(stoi(regs[stoi(temp)])))
            {
                PC = PC + stoi(temp1);
                temp2 = stoi(temp1)/4;
                if (temp2 >= 0)
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                else
                {
                    test.close();
                    test.open("test.txt");
                    temp2 = (PC - PC_initial)/4;
                    for (int i = 0; i < temp2; ++i)
                        getline(test, word);
                }
                PC -= 4;
            }
        }
        else if (word == "LUI")
        {
            string temp;

            test >> word >> temp;

            word = word.substr(1);
            word.erase(word.size()-1);

            regs[stoi(word)] = temp;
        }
        else if (word == "AUIPC")
        {
            string temp;

            test >> word >> temp;
            int temp2;

            word = word.substr(1);
            word.erase(word.size()-1);

            regs[stoi(word)] = to_string((PC + stoi(temp)));
        }
        else if (word == "JAL")
        {
            string temp;

            test >> word >> temp;
            int temp2;

            word = word.substr(1);
            word.erase(word.size()-1);

            regs[stoi(word)] = to_string((PC + 4));

            PC = PC + stoi(temp);
            temp2 = stoi(temp)/4;
            if (temp2 >= 0)
                for (int i = 0; i < temp2; ++i)
                    getline(test, word);
            else
            {
                test.close();
                test.open("test.txt");
                temp2 = (PC - PC_initial)/4;
                for (int i = 0; i < temp2; ++i)
                    getline(test, word);
            }
            PC -= 4;
        }
        else if (word == "JALR")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;
            int temp2;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp.erase(temp.size()-1);

            regs[stoi(word)] = to_string((PC + 4));

            int i = 0;
            for (; i < registers_values.size(); i++)
            {
                if (registers_values[i] == temp)
                    break;
            }

            PC = stoi(temp1) + stoi(mem_locations[i]);

            temp2 = (PC - PC_initial) / 4;

            test.close();
            test.open("test.txt");
            for (int i = 0; i < temp2; ++i)
                getline(test, word);

            PC -= 4;
        }
        else if (word == "SLLI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp2 = stoi(temp1);
            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) << temp2);
        }
        else if (word == "SRLI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp2 = stoi(temp1);
            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) >> temp2);
        }
        else if (word == "SRAI")
        {
            string temp, temp1;
            int temp2;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp2 = stoi(temp1);
            if (regs[stoi(temp)][0] == '-')
            {
                int temp3 = stoi(regs[stoi(temp)].substr(1));
                regs[stoi(word)] = to_string((stoi(regs[stoi(temp)]) >> temp2) * -1);
            }
            else
                regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) >> temp2);
        }
        else if (word == "ADD")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
            
            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) + stoi(regs[stoi(temp1)]));
        }
        else if (word == "SUB")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);//5

            temp = temp.substr(1);
            temp.erase(temp.size()-1);//0

            temp1 = temp1.substr(1);
            

            int x, y;
            cout<<"WORDIS: "<<word<<endl;
            cout<<"TEMPIS: "<<temp<<endl;
            cout<<"TEMP1IS: "<<temp1<<endl;
            x = stoi(regs[stoi(temp)]);
            y = stoi(regs[stoi(temp1)]);
            regs[stoi(word)] = to_string(x - y);
        }
        else if (word == "SLL")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
            

            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) << stoi(regs[stoi(temp1)]));
        }
        else if (word == "SLT")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
            

            if (stoi(regs[stoi(temp)]) < stoi(regs[stoi(temp1)]))
                regs[stoi(word)] = "1";
            else
                regs[stoi(word)] = "0";
        }
        else if (word == "SLTU")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
            

            string x, y;
            if (regs[stoi(temp)][0] == '-')
                x = regs[stoi(temp)].substr(1);
            else
                x = regs[stoi(temp)];

            if (regs[stoi(temp1)][0] == '-')
                y = regs[stoi(temp1)].substr(1);
            else
                y = regs[stoi(temp1)];

            if (stoi(x) < stoi(y))
                regs[stoi(word)] = "1";
            else
                regs[stoi(word)] = "0";
        }
        else if (word == "XOR")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
            

            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) ^ stoi(regs[stoi(temp1)]));
        }
        else if (word == "OR")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
           

            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) | stoi(regs[stoi(temp1)]));
        }
        else if (word == "AND")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
            

            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) & stoi(regs[stoi(temp1)]));
        }
        else if (word == "SRL")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);


            regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) >> stoi(regs[stoi(temp1)]));
        }
        else if (word == "SRA")
        {
            string temp, temp1;

            test >> word >> temp >> temp1;

            word = word.substr(1);
            word.erase(word.size()-1);

            temp = temp.substr(1);
            temp.erase(temp.size()-1);

            temp1 = temp1.substr(1);
            

            if (regs[stoi(temp)][0] == '-')
            {
                int temp3 = stoi(regs[stoi(temp)].substr(1));
                regs[stoi(word)] = to_string((stoi(regs[stoi(temp)]) >> stoi(regs[stoi(temp1)])) * -1);
            }
            else 
                regs[stoi(word)] = to_string(stoi(regs[stoi(temp)]) >> stoi(regs[stoi(temp1)]));
        }

        else if (word == "FENCE" || word == "ECALL" || word == "EBREAK")
        {
            printAll();
            break;
        }
        printAll();
        for_pc++;
    }
    test.close();
    return 0;
}

