#include <bitset>
#include <string>
#include<iostream>
#include"Components.h"
using namespace std;

Alu::Alu()
{
    src0_i = bitset<32> (0);
    src1_i = bitset<32> (0);
    aluctrl_i = bitset<4> (0);
    result_o = bitset<32> (0);
    zero_o = bitset<1> (0); 
}

Alu::~Alu()
{
}
void Alu::input(bitset<32> src_0, bitset<32> src_1, bitset<4> alu_ctrl){
    src0_i = src_0;
    src1_i = src_1;
    aluctrl_i = alu_ctrl;
    alu_operation(); // determine operation and assign the result to result_o and zero_o
}
void Alu::alu_operation(){
    /* Your implementation of the Alu  */
    /* 1. Need to assign calculation result to result_o
       2. Need to set zero_o to 1 if result_o is zero. 
    */
   
       
    if(aluctrl_i == 0b0010)
       {
          result_o = src0_i.to_ulong() + src1_i.to_ulong();
       }
        else  if(aluctrl_i == 0b0110)
      {
         result_o=  src0_i.to_ulong() - src1_i.to_ulong();
      }
    else  if(aluctrl_i == 0b0000)
     {
        result_o=  src0_i & src1_i ;
     }
     
    else  if(aluctrl_i == 0b0001)
    {
       result_o=  src0_i | src1_i ;
    }
      if (result_o == 0b0)
       {
        zero_o = 0b1;
       }
}
bitset<32> Alu::get_aluresult()
{ return result_o;}
bitset<1> Alu::get_zero()
{ return zero_o;}
