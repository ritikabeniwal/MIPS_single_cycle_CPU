#include <iostream>
#include <bitset>
#include <string>

#include "Components.h"

SignExtend::SignExtend()
{
    data_i = bitset<16> (0);
    data_o = bitset<32> (0);
}

SignExtend::~SignExtend()
{
}

void SignExtend::input(bitset<16> input){
    data_i = input;
    data_o = this->extend(data_i);
}
bitset<32> SignExtend::get_output(){
    return data_o;
}

bitset<32> SignExtend::extend(bitset<16> input){
    /* implement your sign-extend funciton here */
    // becareful with the most significant bit.
    // if is 0110--> 000...0110
    // if is 1100--> 1111..1100
    // you have to consider two cases.



for(int i=0; i<16; i++){
   
   data_o[i] = data_i[i];
   data_o[i+16] = data_i[15];
}

return data_o;
}
