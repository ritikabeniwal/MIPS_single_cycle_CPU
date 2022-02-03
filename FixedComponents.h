/*
DO NOT MODIFY THIS FILE!!!!!!!!!!
AND DO NOT MODIFY THE ".CPP" OF COMPONENTS INSIDE THIS FILE !!!!!!!
*/
#ifndef FIXEDCOMPONENTS_H_
#define FIXEDCOMPONENTS_H_
#include<bitset>
#include<vector>
using namespace std;
class ProgramCounter
{
private:
    bitset<32> pc_i;
    bitset<32> pc_o;
public:
    ProgramCounter();
    ~ProgramCounter();
    void input(bitset<32> pc_input);
    bitset<32> get_output();
};
class InstructionMemory
{
private:
    bitset<32> instr_i;
    bitset<32> instr_o;
    // to simulate actual memory
    // string size ==  8 per element
    // fetch location n to n+3 and append the string
    // for example:
    // before fetch: v[n] = "00000000", v[n+1]="11011101", ...
    // after fetch:  0000000011011101...
    vector<string> instr_set;
public:
    InstructionMemory();
    ~InstructionMemory();
    void input(bitset<32> pc_out);
    bitset<32> get_intsr_out();
};
class RegisterFile
{
private:
    bitset<5> rs_i ;
    bitset<5> rt_i;
    bitset<5> rd_i;
    bitset<32> write_data_i;
    bitset<1> regWrite_i;
    bitset<32> rs_o;
    bitset<32> rt_o;
    vector< bitset<32> > reg_file;
public:
    RegisterFile(/* args */);
    ~RegisterFile();
    void write(bitset<32> alu_result);
    void input(bitset<5> rs, bitset<5> rt, bitset<5> rd, bitset<32> write_data, bitset<1> regWrite_in);
    bitset<32> get_rs ();
    bitset<32> get_rt ();
    vector< bitset<32> > get_reg_file();
};
class Adder
{
private:
    bitset<32> add_i_0;
    bitset<32> add_i_1;
    bitset<32> add_o;;
public:
    Adder();
    ~Adder();
    void input(bitset<32> in_0, bitset<32> in_1);
    bitset<32> get_output();
};
class MuxRd // 5bits mux
{
private:
    bitset<5> mux_i_0;
    bitset<5> mux_i_1;
    bitset<1> mux_select;
    bitset<5> mux_o;
public:
    MuxRd();
    ~MuxRd();
    void input(bitset<1> select, bitset<5> in_0, bitset<5> in_1);
    bitset<5> get_output();
};
class Mux // 32bits mux
{
private:
    bitset<32> mux_i_0;
    bitset<32> mux_i_1;
    bitset<1> mux_select;
    bitset<32> mux_o;
public:
    Mux();
    ~Mux();
    void input(bitset<1> select, bitset<32> in_0, bitset<32> in_1);
    bitset<32> get_output();
};
class AndGate
{
private:
    bitset<1> data_i_0;
    bitset<1> data_i_1;
    bitset<1> data_o;
public:
    AndGate(/* args */);
    ~AndGate();
    void input(bitset<1> data0, bitset<1> data1);
    bitset<1> and_operation();
    bitset<1> get_output();
};

#endif