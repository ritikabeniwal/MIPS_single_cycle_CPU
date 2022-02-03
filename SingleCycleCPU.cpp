#include<iostream>
#include<string>
#include<bitset> 
#include<vector>
#include"Components.h"
#include"FixedComponents.h"
using namespace std;

bitset<5> getbits5(bitset<32> bits, int start_loc, int end_loc);
bitset<6> getbits6(bitset<32> bits, int start_loc, int end_loc);
bitset<16> getbits16(bitset<32> bits, int start_loc, int end_loc);
void Single_Cycle_CPU();

int main(){
    
    cout<<"starting the Single Cycle CPU"<<endl;
    
    Single_Cycle_CPU();
    
    return 0;
}

void Single_Cycle_CPU(){

    /* set arguments and parameters */
    bitset<32> pc_in = bitset<32> ("00000000000000000000000000000000"); // 32 bits  
    bitset<32> to_write_data =  bitset<32> ("00000000000000000000000000000000");
    bitset<32> END_SIGNAL = bitset<32> ("11111111111111111111111111111111");
    int CLKCYCLE = 0;
    
    /* Create Components For Single Cycle CPU */
    ProgramCounter PC;
    InstructionMemory IM;
    Control CTRL;
    MuxRd MUXrd; // mux for 5bits
    RegisterFile REG_FILE;
    SignExtend SIGNEXTEND;
    Mux MUXalu1;
    Alu ALU;
    AluControl ALU_CONTROL;
    AndGate ANDGATE;
    ShiftLeft SHIFTLEFT;
    Adder ADDER_PC;
    Adder ADDER_BRANCH;
    Mux MUXbranch;  
    DataMemory DATAMEMORY;
    Mux MUXmemory;

    
    while (true)  //Note: Use while loop to simulate the clock
    {

        /* Program Counter */
        PC.input(pc_in);
        bitset<32> pc_out = PC.get_output();

        /* Instruction Memory */
        // intruction_in representing the instruction memory location to be fetch 
        bitset<32> instruction_in = pc_out;      //what is the input for Instruction Memory?    

        IM.input(instruction_in);
        // Instruction Output
        bitset<32> instr_out = IM.get_intsr_out(); 
        if(instr_out == END_SIGNAL)
            break;
        // what are the bits' "start location" and "end location here"?
        // bitset arrange bits 31,30,29,28...1,0
        // for im_to_alu_ctrl, the answer will be  bitset<6> i_function_code = getbits6(instr_out, 5, 0);
        bitset<5> im_to_rs = getbits5(instr_out, 25, 21);  
        bitset<5> im_to_rt = getbits5(instr_out, 20, 16);          
        bitset<5> im_to_rd = getbits5(instr_out, 15, 11);
        bitset<6> i_opcode = getbits6(instr_out, 31, 26); // opcode
        bitset<6> i_function_code = getbits6(instr_out, 5, 0); // function code is bit[5:0] (6bits)
        bitset<16> im_to_sign_ext = getbits16(instr_out, 15, 0);


        /* Control Unit*/
        bitset<6> ctrl_in = i_opcode;  //what is the input of the control.

        CTRL.input(ctrl_in);
        // Control Unit Outputs: Write down the outputs from control  
        
        bitset<1> regdst = CTRL.get_regdst();
        bitset<1> branch = CTRL.get_branch();
        bitset<1> regWrite = CTRL.get_regwrite();
        bitset<2> ALUop = CTRL.get_aluop();
        bitset<1> AluSrc = CTRL.get_alusrc();
      bitset<1> Memread = CTRL.get_MemRead();
      bitset<1> MemtoReg = CTRL.get_MemtoReg();
      bitset<1> Memwrite = CTRL.get_MemWrite();
       
        
        /* Mux for rd select */
        bitset<1> rd_select = regdst;  // what is the mux select signal?
        MUXrd.input(rd_select, im_to_rt, im_to_rd);
        im_to_rd = MUXrd.get_output();

        /* Register File */
        //input
        /* what is the input for Reg file ? */
        bitset<5> rs = im_to_rs;
        bitset<5> rt = im_to_rt;
        bitset<5> rd = im_to_rd;
        bitset<32> write_data = to_write_data;
        bitset<1> regWrite_in = regWrite;
        REG_FILE.input(rs, rt, rd, write_data, regWrite_in);
        //output
        bitset<32> readdata_1 = REG_FILE.get_rs();
        bitset<32> readdata_2 = REG_FILE.get_rt(); 

        /* Sign-Extend */
        bitset<16> sign_ext_in =  im_to_sign_ext;        // input for sign-extend
        SIGNEXTEND.input(sign_ext_in);
        bitset<32> se_result = SIGNEXTEND.get_output();

        /* Mux for ALU1 select */
        bitset<1> alusrc1_select = AluSrc; //input for mux select
        MUXalu1.input( alusrc1_select,readdata_2,se_result );
        bitset<32> to_alusrc_2 = MUXalu1.get_output();

        /* ALUop get the ALU control input for ALU*/
        bitset<6> alu_ctrl_in =  i_function_code; // **please select an output from instruction memory.
        bitset<2> alu_ctrl_in1 = ALUop; // ** please select an output from control unit.
        ALU_CONTROL.input(alu_ctrl_in, alu_ctrl_in1);
        bitset<4> aluctrl_to_alu = ALU_CONTROL.get_output();         

        /* ALU */
        bitset<32> alusrc_0 = readdata_1;   // enter the input src0
        bitset<32> alusrc_1 =  to_alusrc_2 ;  // enter the input for src1
        bitset<4> aluctrl_in = aluctrl_to_alu ; // enter the input for aluctrl code
        ALU.input(alusrc_0,alusrc_1,aluctrl_in);
        bitset<32> alu_result = ALU.get_aluresult();
        bitset<1> alu_zero = ALU.get_zero();

        /* Data Memory */
        bitset<32> Address = alu_result;
        bitset<32> Writedata = readdata_2;
        bitset<1> MemWrite = Memwrite;
        bitset<1> MemRead = Memread;
        DATAMEMORY.input(Address, Writedata, MemRead, MemWrite);
        bitset<32> Readdata = DATAMEMORY.get_Readdata();

        /* Data Memory and ALU MUX */
        MUXmemory.input(MemtoReg, alu_result, Readdata);
        bitset<32> data_result = MUXmemory.get_output();

        /* Write back to register file */
        REG_FILE.write(data_result);

        /* Find the next PC value */

        ADDER_PC.input(pc_out, bitset<32>(4)); //what are the input for this adder?
        bitset<32> pc_add_4 = ADDER_PC.get_output();
        
        SHIFTLEFT.input(se_result);          
        bitset<32> branch_instr_offset = SHIFTLEFT.get_output(); 
        
        // Memory is byte base, and fetch 4 byte (32bit) per instruction
        // Need to shift left to get the offset to the target(branch destination) intruction memory location 

        ADDER_BRANCH.input(pc_add_4, branch_instr_offset); //what is the input for the adder.
        bitset<32> adder_to_mux_branch_1 = ADDER_BRANCH.get_output();

        ANDGATE.input(branch, alu_zero); // what is the input for the ANDgate
        bitset<1> branch_select = ANDGATE.get_output();

        MUXbranch.input(branch_select,pc_add_4, adder_to_mux_branch_1); //mux for BRANCH add and PC_Counter add
        bitset<32> next_pc = MUXbranch.get_output();

        pc_in = next_pc;

        /* End PC finding */

        CLKCYCLE++;

    }

    // print the result into txt
    cout<< "Total Clock Cycles:"<<CLKCYCLE<<endl;
    cout<<"Register File:"<<endl;
    vector< bitset<32> > reg_stat = REG_FILE.get_reg_file();
    vector<string> mem_stat = DATAMEMORY.get_memory_space();
    for(int i = 0; i<reg_stat.size(); i++){
        cout<<"reg["<<i<<"]:"<<reg_stat[i].to_ulong()<<endl;
    }
    for(int i = 0; i<mem_stat.size(); i++){
        cout<<"mem["<<i<<"th byte]:"<<mem_stat[i]<<endl;
    }
    
}

bitset<5> getbits5(bitset<32> bits, int start_loc, int end_loc){
    string bits32 = bits.to_string();
    int sloc = 31-start_loc;
    int eloc = 31-end_loc;
    int bsize = eloc-sloc+1;
    return bitset<5> (bits32.substr(sloc,bsize));
    
}
bitset<6> getbits6(bitset<32> bits, int start_loc, int end_loc){
    string bits32 = bits.to_string();
    int sloc = 31-start_loc;
    int eloc = 31-end_loc;
    int bsize = eloc-sloc+1;
    return bitset<6> (bits32.substr(sloc,bsize));
}
bitset<16> getbits16(bitset<32> bits, int start_loc, int end_loc){
    string bits32 = bits.to_string();
    int sloc = 31-start_loc;
    int eloc = 31-end_loc;
    int bsize = eloc-sloc+1;
    return bitset<16> (bits32.substr(sloc,bsize));
}
