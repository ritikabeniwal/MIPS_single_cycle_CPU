#ifndef COMPONENTS_H_
#define COMPONENTS_H_
#include <bitset>
#include <vector>
using namespace std;
class Control
{
private:
    bitset<6> ctrl_i;
    bitset<1> regDst_o;
    bitset<1> regWrite_o;
    bitset<2> ALUop_o;
    bitset<1> ALUsrc_o;
    bitset<1> Branch_o;
    bitset<1> MemRead_o;
    bitset<1> MemtoReg_o;
    bitset<1> MemWrite_o;

public:
    Control(/* args */);
    ~Control();
    void input(bitset<6> ctrl_input);
    void operation();
    bitset<1> get_regdst();
    bitset<1> get_regwrite();
    bitset<2> get_aluop();
    bitset<1> get_alusrc();
    bitset<1> get_branch();
    bitset<1> get_MemRead();
    bitset<1> get_MemtoReg();
    bitset<1> get_MemWrite();
};
class SignExtend
{
private:
    bitset<16> data_i;
    bitset<32> data_o;

public:
    SignExtend();
    ~SignExtend();
    void input(bitset<16> input);
    bitset<32> get_output();
    bitset<32> extend(bitset<16> input);
};
class AluControl
{
private:
    bitset<6> func_i;    // fuction code
    bitset<2> aluop_i;   // aluop
    bitset<4> aluctrl_o; // aluctrl code to alu
public:
    AluControl(/* args */);
    ~AluControl();
    void input(bitset<6> func, bitset<2> aluop);
    bitset<4> get_output();
    bitset<4> map_aluctrl_code();
};
class Alu
{
private:
    bitset<32> src0_i;
    bitset<32> src1_i;
    bitset<4> aluctrl_i;
    bitset<32> result_o;
    bitset<1> zero_o;

public:
    Alu();
    ~Alu();
    void input(bitset<32> src_0, bitset<32> src_1, bitset<4> alu_ctrl);
    void alu_operation();
    bitset<32> get_aluresult();
    bitset<1> get_zero();
};
class ShiftLeft
{
private:
    bitset<32> data_i;
    bitset<32> data_o;

public:
    ShiftLeft(/* args */);
    ~ShiftLeft();
    void input(bitset<32> data_in);
    bitset<32> get_output();
    bitset<32> sl_operation();
};
class DataMemory
{
private:
    bitset<32> Address_i;
    bitset<32> Writedata_i;
    bitset<32> Readdata_o;

    bitset<1> MemRead_i;
    bitset<1> MemWrite_i;

    vector<string> memory_space;

public:
    DataMemory(/* args */);
    ~DataMemory();

    void input(bitset<32> Address, bitset<32> Writedata, bitset<1> MemRead, bitset<1> MemWrite);
    void operation();
    bitset<32> get_Readdata();
    int bitaddress_to_intlocation();

    void store_writedata_to_location();
    void load_readdata_from_location();
    vector<string> get_memory_space();
};
#endif