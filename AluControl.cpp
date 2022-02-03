#include <bitset>
#include <string>
#include<iostream>
#include"Components.h"

AluControl::AluControl(/* args */)
{
    func_i = bitset<6> (0);
    aluop_i = bitset<2> (0);
    aluctrl_o = bitset<4> (0);
}

AluControl::~AluControl()
{
}

void AluControl::input(bitset<6> func, bitset<2> aluop){
    func_i = func;
    aluop_i = aluop;
    aluctrl_o = this->map_aluctrl_code();
}

bitset<4> AluControl::get_output(){
    return aluctrl_o;
}

bitset<4> AluControl::map_aluctrl_code()
{
    /* Implement your ALU Control here 
    every input is already assign to private member, you can use directly.
    what you need to return: the correct ALU control code  
    hint: use aluop_i(ALUop) and func_i(function code) to decide what is the alu control code.*/
    
     if (aluop_i == 0b10 && func_i ==0b100000)
    aluctrl_o = 0b0010;
    
    else if (aluop_i ==0b10 && func_i == 0b100010 )
    aluctrl_o = 0b0110;
    
    else if (aluop_i == 0b10 && func_i == 0b100101)
    aluctrl_o = 0b0001;
    
    else if (aluop_i ==0b10 && func_i == 0b100100)
    aluctrl_o =0b0000;
    
    else if (aluop_i ==0b10 && func_i ==(0b101010))
    aluctrl_o = 0b0111;
    
    else if (aluop_i == 0b01)
    aluctrl_o = 0b0110;
    
    else if (aluop_i == 0b00)
    aluctrl_o = 0b0010;

return aluctrl_o;

}
