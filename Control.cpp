#include <bitset>
#include <string>
#include<iostream>
#include"Components.h"
using namespace std;


Control::Control()
{
    ctrl_i     = bitset<6> (0);
    regDst_o   = bitset<1> (0);
    regWrite_o = bitset<1> (0); 
    ALUop_o    = bitset<2> (0);
    ALUsrc_o   = bitset<1> (0);
    Branch_o   = bitset<1> (0); 
    MemRead_o  = bitset<1> (0);
    MemtoReg_o = bitset<1> (0);
    MemWrite_o = bitset<1> (0);
}

Control::~Control()
{
}

void Control::input(bitset<6> ctrl_input)
{
    ctrl_i = ctrl_input;
    this->operation();
}
void Control::operation(){
    /* implement your own control method here*/
    // tips: map the opcode to the instruction type (r-type, i-type...etc) and decide the value for output signal.
    // private member XXX_i is for input, XXX_o is for output.


    //Rtype
    if (ctrl_i == 0b000000)
    {
       regDst_o=  0b1;
       Branch_o = 0b0;
       regWrite_o = 0b1;
       ALUop_o =  0b10;
       ALUsrc_o = 0b0;
       MemRead_o= 0b0;
       MemtoReg_o= 0b0;
       MemWrite_o= 0b0;
    }
    
    //addi
    else if (ctrl_i == 0b001000)
    {
       regDst_o= 0b0;
       Branch_o = 0b0;
       regWrite_o =  0b1;
       ALUop_o = 0b00;
       ALUsrc_o = 0b1;
       MemRead_o= 0b0;
       MemtoReg_o= 0b0;
       MemWrite_o= 0b0;
    }

//beq


else if (ctrl_i == 0b000100)
    {
       regDst_o=  0b0;
       Branch_o = 0b1;
       regWrite_o =  0b0;
       ALUop_o = 0b01;
       ALUsrc_o =  0b0;
       MemRead_o=  0b0;
       MemtoReg_o=  0b0;
       MemWrite_o=  0b0;
    }

//lw

else if (ctrl_i == 0b100011)
    { 
       regDst_o=  0b0;
       Branch_o =  0b0;
       regWrite_o =  0b1;
       ALUop_o = 0b00;
       ALUsrc_o =  0b1;
       MemRead_o=  0b1;
       MemtoReg_o= 0b1;
       MemWrite_o=  0b0;
    }

//sw

else if (ctrl_i == 0b101011)
    {
       regDst_o= 0b1;
       Branch_o = 0b0;
       regWrite_o = 0b0;
       ALUop_o = 0b00;
       ALUsrc_o = 0b1;
       MemRead_o=  0b0;
       MemtoReg_o= 0b1;
       MemWrite_o= 0b1;
    }
    
}
bitset<1> Control::get_regdst(){
    return regDst_o;
}
bitset<1> Control::get_regwrite(){
    return regWrite_o;
}
bitset<2> Control::get_aluop(){
    return ALUop_o;
}
bitset<1> Control::get_alusrc(){
    return ALUsrc_o;
}
bitset<1> Control::get_branch(){
    return Branch_o;
}
bitset<1> Control::get_MemRead(){
    return MemRead_o;
}
bitset<1> Control::get_MemtoReg(){
    return MemtoReg_o;
}
bitset<1> Control::get_MemWrite(){
    return MemWrite_o;
}
