#include "cpu.h"
#include <iostream>
#include <iomanip>

/*
Bugs that could be an issue ... can an element of ad array be indexed with hex
in this case accessing memory location through address bus used in absolute add_mode

line 209 might be a possible issue


*/

cpu::cpu()
{ 
    ins_table = {
        //                       0                                1                               2                               3                                 4                               5                               6                              7                                   8                            9                               A                                 B                             C                                D                                E                               F                                
        /* 0 */ { &cpu::BRK, &cpu::add_IMP, 7 },{ &cpu::ORA, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SLO, &cpu::add_iIND, 8 },{ &cpu::NOP, &cpu::add_ZP0, 3 },{ &cpu::ORA, &cpu::add_ZP0, 3 },{ &cpu::ASL, &cpu::add_ZP0, 5 },{ &cpu::SLO, &cpu::add_ZP0, 5 },{ &cpu::PHP, &cpu::add_IMP, 3 },{ &cpu::ORA, &cpu::add_IMM, 2 },{ &cpu::ASL, &cpu::add_IMP, 2 },{ &cpu::ANC, &cpu::add_IMP, 2 },{ &cpu::NOP, &cpu::add_ABS, 4 },{ &cpu::ORA, &cpu::add_ABS, 4 },{ &cpu::ASL, &cpu::add_ABS, 6 },{ &cpu::SLO, &cpu::add_ABS, 6 },
        /* 1 */ { &cpu::BPL, &cpu::add_REL, 2 },{ &cpu::ORA, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SLO, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::ORA, &cpu::add_ZPX, 4 },{ &cpu::ASL, &cpu::add_ZPX, 6 },{ &cpu::SLO, &cpu::add_ZPX, 6 },{ &cpu::CLC, &cpu::add_IMP, 2 },{ &cpu::ORA, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SLO, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::ORA, &cpu::add_ABX, 4 },{ &cpu::ASL, &cpu::add_ABX, 7 },{ &cpu::SLO, &cpu::add_ABX, 7 },
        /* 2 */ { &cpu::JSR, &cpu::add_ABS, 6 },{ &cpu::AND, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RLA, &cpu::add_iIND, 8 },{ &cpu::BIT, &cpu::add_ZP0, 3 },{ &cpu::AND, &cpu::add_ZP0, 3 },{ &cpu::ROL, &cpu::add_ZP0, 5 },{ &cpu::RLA, &cpu::add_ZP0, 5 },{ &cpu::PLP, &cpu::add_IMP, 4 },{ &cpu::AND, &cpu::add_IMM, 2 },{ &cpu::ROL, &cpu::add_IMP, 2 },{ &cpu::ANC, &cpu::add_IMP, 2 },{ &cpu::BIT, &cpu::add_ABS, 4 },{ &cpu::AND, &cpu::add_ABS, 4 },{ &cpu::ROL, &cpu::add_ABS, 6 },{ &cpu::RLA, &cpu::add_ABS, 6 },
        /* 3 */	{ &cpu::BMI, &cpu::add_REL, 2 },{ &cpu::AND, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RLA, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::AND, &cpu::add_ZPX, 4 },{ &cpu::ROL, &cpu::add_ZPX, 6 },{ &cpu::RLA, &cpu::add_ZPX, 6 },{ &cpu::SEC, &cpu::add_IMP, 2 },{ &cpu::AND, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::RLA, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::AND, &cpu::add_ABX, 4 },{ &cpu::ROL, &cpu::add_ABX, 7 },{ &cpu::RLA, &cpu::add_ABX, 7 },
        /* 4 */	{ &cpu::RTI, &cpu::add_IMP, 6 },{ &cpu::EOR, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SRE, &cpu::add_iIND, 8 },{ &cpu::NOP, &cpu::add_ZP0, 3 },{ &cpu::EOR, &cpu::add_ZP0, 3 },{ &cpu::LSR, &cpu::add_ZP0, 5 },{ &cpu::SRE, &cpu::add_ZP0, 5 },{ &cpu::PHA, &cpu::add_IMP, 3 },{ &cpu::EOR, &cpu::add_IMM, 2 },{ &cpu::LSR, &cpu::add_IMP, 2 },{ &cpu::ALR, &cpu::add_IMP, 2 },{ &cpu::JMP, &cpu::add_ABS, 3 },{ &cpu::EOR, &cpu::add_ABS, 4 },{ &cpu::LSR, &cpu::add_ABS, 6 },{ &cpu::SRE, &cpu::add_ABS, 6 },
        /* 5 */ { &cpu::BVC, &cpu::add_REL, 2 },{ &cpu::EOR, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SRE, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::EOR, &cpu::add_ZPX, 4 },{ &cpu::LSR, &cpu::add_ZPX, 6 },{ &cpu::SRE, &cpu::add_ZPX, 6 },{ &cpu::CLI, &cpu::add_IMP, 2 },{ &cpu::EOR, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SRE, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::EOR, &cpu::add_ABX, 4 },{ &cpu::LSR, &cpu::add_ABX, 7 },{ &cpu::SRE, &cpu::add_ABX, 7 },
        /* 6 */	{ &cpu::RTS, &cpu::add_IMP, 6 },{ &cpu::ADC, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RRA, &cpu::add_iIND, 8 },{ &cpu::NOP, &cpu::add_ZP0, 3 },{ &cpu::ADC, &cpu::add_ZP0, 3 },{ &cpu::ROR, &cpu::add_ZP0, 5 },{ &cpu::RRA, &cpu::add_ZP0, 5 },{ &cpu::PLA, &cpu::add_IMP, 4 },{ &cpu::ADC, &cpu::add_IMM, 2 },{ &cpu::ROR, &cpu::add_IMP, 2 },{ &cpu::ARR, &cpu::add_IMP, 2 },{ &cpu::JMP, &cpu::add_IND, 5 },{ &cpu::ADC, &cpu::add_ABS, 4 },{ &cpu::ROR, &cpu::add_ABS, 6 },{ &cpu::RRA, &cpu::add_ABS, 6 },
        /* 7 */	{ &cpu::BVS, &cpu::add_REL, 2 },{ &cpu::ADC, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RRA, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::ADC, &cpu::add_ZPX, 4 },{ &cpu::ROR, &cpu::add_ZPX, 6 },{ &cpu::RRA, &cpu::add_ZPX, 6 },{ &cpu::SEI, &cpu::add_IMP, 2 },{ &cpu::ADC, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::RRA, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::ADC, &cpu::add_ABX, 4 },{ &cpu::ROR, &cpu::add_ABX, 7 },{ &cpu::RRA, &cpu::add_ABX, 7 },
        /* 8 */	{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::STA, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SAX, &cpu::add_IMP, 6 }, { &cpu::STY, &cpu::add_ZP0, 3 },{ &cpu::STA, &cpu::add_ZP0, 3 },{ &cpu::STX, &cpu::add_ZP0, 3 },{ &cpu::SAX, &cpu::add_ZP0, 3 },{ &cpu::DEY, &cpu::add_IMP, 2 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::TXA, &cpu::add_IMP, 2 },{ &cpu::ANE, &cpu::add_IMP, 2 },{ &cpu::STY, &cpu::add_ABS, 4 },{ &cpu::STA, &cpu::add_ABS, 4 },{ &cpu::STX, &cpu::add_ABS, 4 },{ &cpu::SAX, &cpu::add_ABS, 4 },
        /* 9 */	{ &cpu::BCC, &cpu::add_REL, 2 },{ &cpu::STA, &cpu::add_INDi, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SHA, &cpu::add_IMP, 6 }, { &cpu::STY, &cpu::add_ZPX, 4 },{ &cpu::STA, &cpu::add_ZPX, 4 },{ &cpu::STX, &cpu::add_ZPY, 4 },{ &cpu::SAX, &cpu::add_ZPX, 4 },{ &cpu::TYA, &cpu::add_IMP, 2 },{ &cpu::STA, &cpu::add_ABY, 5 },{ &cpu::TXS, &cpu::add_IMP, 2 },{ &cpu::TAS, &cpu::add_ABY, 5 },{ &cpu::SHY, &cpu::add_ABX, 5 },{ &cpu::STA, &cpu::add_ABX, 5 },{ &cpu::SHX, &cpu::add_ABY, 5 },{ &cpu::SHA, &cpu::add_ABY, 5 },
        /* A */	{ &cpu::LDY, &cpu::add_IMM, 2 },{ &cpu::LDA, &cpu::add_iIND, 6 },{ &cpu::LDX, &cpu::add_IMM, 2 },{ &cpu::LAX, &cpu::add_IMP, 6 }, { &cpu::LDY, &cpu::add_ZP0, 3 },{ &cpu::LDA, &cpu::add_ZP0, 3 },{ &cpu::LDX, &cpu::add_ZP0, 3 },{ &cpu::LAX, &cpu::add_ZP0, 3 },{ &cpu::TAY, &cpu::add_IMP, 2 },{ &cpu::LDA, &cpu::add_IMM, 2 },{ &cpu::TAX, &cpu::add_IMP, 2 },{ &cpu::LXA, &cpu::add_IMP, 2 },{ &cpu::LDY, &cpu::add_ABS, 4 },{ &cpu::LDA, &cpu::add_ABS, 4 },{ &cpu::LDX, &cpu::add_ABS, 4 },{ &cpu::LAX, &cpu::add_ABS, 4 },
        /* B */	{ &cpu::BCS, &cpu::add_REL, 2 },{ &cpu::LDA, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::LAX, &cpu::add_IMP, 5 }, { &cpu::LDY, &cpu::add_ZPX, 4 },{ &cpu::LDA, &cpu::add_ZPX, 4 },{ &cpu::LDX, &cpu::add_ZPY, 4 },{ &cpu::LAX, &cpu::add_ZPX, 4 },{ &cpu::CLV, &cpu::add_IMP, 2 },{ &cpu::LDA, &cpu::add_ABY, 4 },{ &cpu::TSX, &cpu::add_IMP, 2 },{ &cpu::LAS, &cpu::add_ABY, 4 },{ &cpu::LDY, &cpu::add_ABX, 4 },{ &cpu::LDA, &cpu::add_ABX, 4 },{ &cpu::LDX, &cpu::add_ABY, 4 },{ &cpu::LAX, &cpu::add_ABY, 4 },
        /* C */	{ &cpu::CPY, &cpu::add_IMM, 2 },{ &cpu::CMP, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::DCP, &cpu::add_IMP, 8 }, { &cpu::CPY, &cpu::add_ZP0, 3 },{ &cpu::CMP, &cpu::add_ZP0, 3 },{ &cpu::DEC, &cpu::add_ZP0, 5 },{ &cpu::DCP, &cpu::add_ZP0, 5 },{ &cpu::INY, &cpu::add_IMP, 2 },{ &cpu::CMP, &cpu::add_IMM, 2 },{ &cpu::DEX, &cpu::add_IMP, 2 },{ &cpu::SBX, &cpu::add_IMP, 2 },{ &cpu::CPY, &cpu::add_ABS, 4 },{ &cpu::CMP, &cpu::add_ABS, 4 },{ &cpu::DEC, &cpu::add_ABS, 6 },{ &cpu::DCP, &cpu::add_ABS, 6 },
        /* D */	{ &cpu::BNE, &cpu::add_REL, 2 },{ &cpu::CMP, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::DCP, &cpu::add_IMP, 8 }, { &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::CMP, &cpu::add_ZPX, 4 },{ &cpu::DEC, &cpu::add_ZPX, 6 },{ &cpu::DCP, &cpu::add_ZPX, 6 },{ &cpu::CLD, &cpu::add_IMP, 2 },{ &cpu::CMP, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::DCP, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::CMP, &cpu::add_ABX, 4 },{ &cpu::DEC, &cpu::add_ABX, 7 },{ &cpu::DCP, &cpu::add_ABX, 7 },
        /* E */	{ &cpu::CPX, &cpu::add_IMM, 2 },{ &cpu::SBC, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::ISC, &cpu::add_IMP, 8 }, { &cpu::CPX, &cpu::add_ZP0, 3 },{ &cpu::SBC, &cpu::add_ZP0, 3 },{ &cpu::INC, &cpu::add_ZP0, 5 },{ &cpu::ISC, &cpu::add_ZP0, 5 },{ &cpu::INX, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_IMM, 2 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_IMP, 2 },{ &cpu::CPX, &cpu::add_ABS, 4 },{ &cpu::SBC, &cpu::add_ABS, 4 },{ &cpu::INC, &cpu::add_ABS, 6 },{ &cpu::ISC, &cpu::add_ABS, 6 },
        /* F */	{ &cpu::BEQ, &cpu::add_REL, 2 },{ &cpu::SBC, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::ISC, &cpu::add_IMP, 8 }, { &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::SBC, &cpu::add_ZPX, 4 },{ &cpu::INC, &cpu::add_ZPX, 6 },{ &cpu::ISC, &cpu::add_ZPX, 6 },{ &cpu::SED, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::ISC, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::SBC, &cpu::add_ABX, 4 },{ &cpu::INC, &cpu::add_ABX, 7 },{ &cpu::ISC, &cpu::add_ABX, 7 },

        //REMEMBER  A-0,2,4,6  ADD MODE A CHECK INSTRUCTION TABLE WEBSITE     
        };

    // program_counter = 0x1000;
    stack_base_add = 0x0100;    //0x0100 is the base address of the stack.
    stack_pointer = 0xFF;        // This is a common choice for the stack in many 6502 systems.
                                // the range of stack becomes 0x0100 to 0x01FF in the memory
}

cpu::~cpu()
{
 //Destructor
}

// Function Defintions Start Here..............

//Load operations definitions
void cpu::LDA() //tested status : working
{   
    accumulator = data_bus;
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"LDA"<< std::endl;
}

void cpu::LDX() //tested status : working
{   
    X_reg = data_bus;
    set_flag(Z, X_reg == 0x00);
    set_flag(N, X_reg & 0x80);
    std::cout <<"LDX"<< std::endl;
}

void cpu::LDY() //tested status : working
{   
    Y_reg = data_bus;
    set_flag(Z, Y_reg == 0x00);
    set_flag(N, Y_reg & 0x80);
    std::cout <<"LDY"<< std::endl;
}

void cpu::STA() 
{   
    memory[address_bus] = accumulator;
    std::cout <<"STA"<< std::endl;
}

void cpu::STX()
{   
    memory[address_bus] = X_reg;
    std::cout <<"STX"<< std::endl;
}

void cpu::STY()
{   
    memory[address_bus] = Y_reg;
    std::cout <<"STY"<< std::endl;
}

//Register transfer operations definitions
void cpu::TAX()
{   
    X_reg = accumulator;
    set_flag(Z, X_reg == 0x00);
    set_flag(N, X_reg & 0x80);
    std::cout <<"TAX"<< std::endl;
}

void cpu::TAY()
{   
    Y_reg = accumulator;
    set_flag(Z, Y_reg == 0x00);
    set_flag(N, Y_reg & 0x80);
    std::cout <<"TAY"<< std::endl;
}

void cpu::TXA()
{   
    accumulator = X_reg;
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"TXA"<< std::endl;
}

void cpu::TYA()
{   accumulator = Y_reg;
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"TYA"<< std::endl;
}

//Stack operations definitions
void cpu::TSX()
{   
    X_reg = stack_pointer + stack_base_add;
    set_flag(Z, X_reg == 0x00);
    set_flag(N, X_reg & 0x80);
    std::cout <<"TSX"<< std::endl;
}

void cpu::TXS()
{   
    stack_pointer = X_reg;

    std::cout <<"TXS"<< std::endl;
}

void cpu::PHA()
{   memory[stack_pointer + stack_base_add] = accumulator;
    stack_pointer--;
    std::cout <<"PHA"<< std::endl;
}

void cpu::PHP()
{   
    memory[stack_pointer + stack_base_add] = status_reg;
    stack_pointer--;
    std::cout <<"PHP"<< std::endl;
}

void cpu::PLA()
{   
    stack_pointer++;
    accumulator = memory[stack_pointer + stack_base_add];
    
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"PLA"<< std::endl;
}

void cpu::PLP()
{   
    stack_pointer++;
    status_reg = memory[stack_pointer + stack_base_add];
    
    std::cout <<"PLP"<< std::endl;
}

//Logical operations definitions

void cpu::AND()
{   accumulator = (accumulator & data_bus);
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"AND"<< std::endl;
}

void cpu::EOR()
{   accumulator = (accumulator ^ data_bus);
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"EOR"<< std::endl;
}

void cpu::ORA()
{   accumulator = (accumulator | data_bus);
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"ORA"<< std::endl;
}

void cpu::BIT()
{   
    set_flag(Z, accumulator & data_bus);
    set_flag(N, data_bus >> 7);
    set_flag(N, (data_bus >> 6) & 0x2 );
    std::cout <<"BIT"<< std::endl;
}

//Arithemteic operations definitions
//both ADC and SBC are complex instructions....I refered to javidx code
void cpu::ADC()
{   
    result_16 = accumulator + data_bus + get_flag(C);
    set_flag(C, result_16 > 0xFF);
    // SetFlag(V, (~((uint16_t)accumulator ^ (uint16_t)data_bus) & ((uint16_t)accumulator ^ (uint16_t)result_8)) & 0x0080);
    set_flag(V, (~(accumulator ^ data_bus) & (accumulator ^ (uint8_t)result_16)) & 0x0080); 
    
    accumulator = (result_16 & 0x00FF);
    
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"ADC"<< std::endl;
}

void cpu::SBC()
{   
    result_16  = accumulator + (data_bus ^ 0x00FF) + get_flag(C);
    set_flag(C, result_16 & 0xFF00);
    // SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
    set_flag(V, ((uint8_t)result_16 ^ (accumulator)) & ( (uint8_t)result_16 ^ (data_bus ^ 0x00FF) ) & 0x0080);

    accumulator = (result_16 & 0xFF00);

    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);

    std::cout <<"SBC"<< std::endl;
}

void cpu::CMP()
{   
    result_8 = accumulator - data_bus;
    set_flag(C, result_8 >= data_bus);
	set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    std::cout <<"CMP"<< std::endl;
}

void cpu::CPX()
{   
    result_8 = X_reg - data_bus;
    set_flag(C, result_8 >= data_bus);
	set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    std::cout <<"CPX"<< std::endl;
}

void cpu::CPY()
{   
    result_8 = Y_reg - data_bus;
    set_flag(C, result_8 >= data_bus);
	set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    std::cout <<"CPY"<< std::endl;
}


//Increments and Decrement operations definitions

void cpu::INC()
{   
    result_8 = data_bus++;
    set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    flash_mem_at_loc(result_8, address_bus);

    std::cout <<"INC"<< std::endl;
}

void cpu::INX()
{   
    result_8 = X_reg++;
    set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    X_reg = result_8;
    std::cout <<"INX"<< std::endl;
}

void cpu::INY()
{   
    result_8 = Y_reg++;
    set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    Y_reg = result_8;

    std::cout <<"INY"<< std::endl;
}

void cpu::DEC()
{   
    result_8 = data_bus--;
    set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    flash_mem_at_loc(result_8, address_bus);
    std::cout <<"DEC"<< std::endl;
}

void cpu::DEX()
{   
    result_8 = X_reg--;
    set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    X_reg = result_8;
    std::cout <<"DEX"<< std::endl;
}

void cpu::DEY()
{   
    result_8 = Y_reg--;
    set_flag(Z, result_8 == 0x0000);
	set_flag(N, result_8 & 0x0080);
    Y_reg = result_8;
    std::cout <<"DEY"<< std::endl;
}

//Shift operations definitions
void cpu::ASL()
{   
    if(fetch_ret.add_mode_ptr == &cpu::add_IMP){
        set_flag(C, accumulator & 0x80);
        accumulator = accumulator << 1;
        result_8 = accumulator;
    }
    else{
        set_flag(C, data_bus & 0x80);
        result_8 = data_bus << 1;
        flash_mem_at_loc(result_8, address_bus);

    }
    set_flag(Z, result_8 == 0x0000);
    set_flag(N, result_8 & 0x0080);
    std::cout <<"ASL"<< std::endl;
}

void cpu::LSR()
{   
    if(fetch_ret.add_mode_ptr == &cpu::add_IMP){
        set_flag(C, accumulator & 0x01);
        accumulator = accumulator >> 1;
        result_8 = accumulator;
    }
    else{
        set_flag(C, data_bus & 0x01);
        result_8 = data_bus >> 1;
        flash_mem_at_loc(result_8, address_bus);

    }
    set_flag(Z, result_8 == 0x0000);
    set_flag(N, result_8 & 0x0080);
    std::cout <<"LSR"<< std::endl;
}

void cpu::ROL()
{   
    uint8_t temp_c = get_flag(C);

    if(fetch_ret.add_mode_ptr == &cpu::add_IMP){
        set_flag(C, accumulator & 0x80);
        accumulator = accumulator << 1;
        accumulator = accumulator | temp_c; 
        result_8 = accumulator;
    }
    else{
        set_flag(C, data_bus & 0x80);
        result_8 = data_bus << 1;
        result_8 = result_8 | temp_c;
        flash_mem_at_loc(result_8, address_bus);

    }
    set_flag(Z, result_8 == 0x0000);
    set_flag(N, result_8 & 0x0080);
    std::cout <<"ROL"<< std::endl;
}

void cpu::ROR()
{   
    uint8_t temp_c = get_flag(C);
    
    if(fetch_ret.add_mode_ptr == &cpu::add_IMP){
        set_flag(C, accumulator & 0x80);
        accumulator = accumulator >> 1;
        accumulator = accumulator | (temp_c << 7); 
        result_8 = accumulator;
    }
    else{
        set_flag(C, data_bus & 0x80);
        result_8 = data_bus << 1;
        result_8 = result_8 | (temp_c << 7); 
        flash_mem_at_loc(result_8, address_bus);

    }
    set_flag(Z, result_8 == 0x0000);
    set_flag(N, result_8 & 0x0080);
    std::cout <<"ROR"<< std::endl;
}

//Jump and Call operations definitions

void cpu::JMP()
{   
    program_counter = address_bus;
    std::cout <<"JMP"<< std::endl;
}

void cpu::JSR()
{   
    memory[stack_pointer+stack_base_add] = (uint8_t)(program_counter>>8);
    stack_pointer--;
    memory[stack_pointer+stack_base_add] = (uint8_t)(program_counter);
    stack_pointer--;
    program_counter = address_bus;
    std::cout <<"JSR"<< std::endl;
}

void cpu::RTS()
{   
    stack_pointer++;
    program_counter = memory[stack_pointer+stack_base_add];
    stack_pointer++;
    program_counter = program_counter | (memory[stack_pointer+stack_base_add]<<8);
    std::cout <<"RTS"<< std::endl;
}

//Branching operations definitions
void cpu::BCC()
{   
    if(get_flag(C) == 0x00){
        program_counter = address_bus;
    }
    std::cout <<"BCC"<< std::endl;
}

void cpu::BCS()
{   
    if(get_flag(C) != 0x00){
        program_counter = address_bus;
    }
    std::cout <<"BCS"<< std::endl;
}

void cpu::BEQ()
{   
    if(get_flag(Z) != 0x00){
        program_counter = address_bus;
    }
    std::cout <<"BEQ"<< std::endl;
}

void cpu::BMI()
{   
    if(get_flag(N) != 0x00){
        program_counter = address_bus;
    }

    std::cout <<"BMI"<< std::endl;
}

void cpu::BNE()
{   
    if(get_flag(Z) == 0x00){
        program_counter = address_bus;
    }
    std::cout <<"BNE"<< std::endl;
}

void cpu::BPL()
{   
    if(get_flag(N) == 0x00){
        program_counter = address_bus;
    }
    std::cout <<"BPL"<< std::endl;
}

void cpu::BVC()
{   
    if(get_flag(V) == 0x00){
        program_counter = address_bus;
    }
    std::cout <<"BVC"<< std::endl;
}

void cpu::BVS()
{   
    if(get_flag(V) != 0x00){
        program_counter = address_bus;
    }
    std::cout <<"BVS"<< std::endl;
}

//Status flag changes operations definitions
void cpu::CLC()
{   
    set_flag(C,0);
    std::cout <<"CLC"<< std::endl;
}

void cpu::CLD()
{   
    set_flag(D,0);
    std::cout <<"CLD"<< std::endl;
}

void cpu::CLI()
{   
    set_flag(I,0);
    std::cout <<"CLI"<< std::endl;
}

void cpu::CLV()
{   
    set_flag(V,0);
    std::cout <<"CLV"<< std::endl;
}

void cpu::SEC()
{   
    set_flag(C,1);
    std::cout <<"SEC"<< std::endl;
}

void cpu::SED()
{   
    set_flag(D,1);
    std::cout <<"SED"<< std::endl;
}

void cpu::SEI()
{   
    set_flag(I,1);
    std::cout <<"SEI"<< std::endl;
}

//SYSTEM CHANGES operations definitions
void cpu::BRK()
{   

    memory[stack_pointer+stack_base_add] = (uint8_t)(program_counter>>8);
    stack_pointer--;
    memory[stack_pointer+stack_base_add] = (uint8_t)(program_counter);
    stack_pointer--;

    set_flag(B,1);
    memory[stack_pointer+stack_base_add] = status_reg;
    stack_pointer--;

    set_flag(I,1);
    program_counter = (memory[interrupt_vector_loc] | (memory[interrupt_vector_loc] << 8));
    
    std::cout <<"BRK"<< std::endl;
}

void cpu::RTI()
{   
    stack_pointer++;
    status_reg = memory[stack_pointer+stack_base_add];
    set_flag(B,0);
    set_flag(I,0);

    stack_pointer++;
    program_counter = memory[stack_pointer+stack_base_add];
    stack_pointer++;
    program_counter = program_counter | (memory[stack_pointer+stack_base_add]<<8);
    
    std::cout <<"RTI"<< std::endl;
}

//Illegal opcodes definitions

void cpu::NOP() //
{   
    std::cout <<"NOP"<< std::endl;
}

void cpu::JAM() //
{   
    while (true)
    { 
      program_counter++;
      fetch_ins();
      data_bus = 0xFF;  
    }
    
    std::cout <<"JAM"<< std::endl;
}

void cpu::SLO() //
{   
    ASL();
    ORA();
    std::cout <<"SLO"<< std::endl;
}

void cpu::RLA() //
{   
    ROL();
    AND();
    std::cout <<"RLA"<< std::endl;
}

void cpu::SRE() //
{   
    LSR();
    EOR();
    std::cout <<"SRE"<< std::endl;
}

void cpu::RRA() //
{   
    ROR();
    ADC();
    std::cout <<"RRA"<< std::endl;
}

void cpu::SAX() //
{   
    data_bus = (accumulator & X_reg);
    std::cout <<"SAX"<< std::endl;
}

void cpu::SHA() //
{   
    address_bus = (accumulator & X_reg) & (address_bus >> 8);
    std::cout <<"SHA"<< std::endl;
}

void cpu::LAX() //
{   
    LDA();
    LDX();
    std::cout <<"LAX"<< std::endl;
}

void cpu::DCP() //
{   
    DEC();
    CMP();
    std::cout <<"DCP"<< std::endl;
}

void cpu::ISC() //
{
    INC();
    SBC();
    std::cout <<"ISC"<< std::endl;
}

void cpu::ANC() //
{   
    AND();
        if(fetch_ret.add_mode_ptr == &cpu::add_IMP){
        set_flag(C, accumulator & 0x80);
    }
    else{
        set_flag(C, data_bus & 0x80);
    }
    std::cout <<"ANC"<< std::endl;
}

void cpu::ALR()  //
{   
    AND();
    LSR();
    std::cout <<"ALR"<< std::endl;
}

void cpu::ARR() //
{   
    AND();
    ROR();
    std::cout <<"ARR"<< std::endl;
}

void cpu::ANE() //
{   
    accumulator = data_bus & X_reg;
    set_flag(Z, accumulator == 0x00);
    set_flag(N, accumulator & 0x80);
    std::cout <<"ANE"<< std::endl;
}

void cpu::TAS() //
{   
    stack_pointer = accumulator & X_reg;
    address_bus = (accumulator & X_reg) & ((address_bus >> 8) + 0x01);

    std::cout <<"TAS"<< std::endl;
}

void cpu::LXA() //
{   
    X_reg = accumulator;
    std::cout <<"LXA"<< std::endl;
    set_flag(Z, X_reg == 0x00);
    set_flag(N, X_reg & 0x80);
}

void cpu::LAS() //
{   
    accumulator = stack_pointer;
    accumulator = accumulator & data_bus;
    stack_pointer = accumulator;

    std::cout <<"LAS"<< std::endl;
}

void cpu::SBX() //
{   
    X_reg = accumulator - X_reg;
    set_flag(Z, X_reg == 0x00);
    set_flag(N, X_reg & 0x80);
    std::cout <<"SBX"<< std::endl;
}

void cpu::SHY() //
{
    address_bus = ((address_bus>>8) + 0x1) &  Y_reg;
    std::cout <<"SHY"<< std::endl;
}

void cpu::SHX() //
{   
    address_bus = ((address_bus>>8) + 0x1) &  X_reg;
    std::cout <<"SHX"<< std::endl;
}

void cpu::USBC() //
{
    SBC();
    NOP();
    std::cout <<"USBC"<< std::endl;
}
//Addressing modes definitions
void cpu::add_IMP()
{   
    program_counter++;
    std::cout <<"add_IMP"<< std::endl;
}

void cpu::add_IMM() //tested status : working
{   // simplest of the addressing modes nothing much to explain just takes the value next to the instruction
    // from memory indicated by the program counter

    cpu::program_counter++;
    cpu::data_bus = cpu::memory[program_counter];
    std::cout <<"add_IMM"<< std::endl;
}

void cpu::add_ACC() // not in instruction table
{   
    std::cout <<"add_ACC"<< std::endl;
}

void cpu::add_ZP0() //tested status : working
{   
    cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::data_bus = cpu::memory[cpu::address_bus];

    std::cout <<"add_ZP0"<< std::endl;
}

void cpu::add_ZPX() //tested status : working
{   
    cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::address_bus = cpu::address_bus + cpu::X_reg;
    cpu::data_bus = cpu::memory[cpu::address_bus];

    std::cout <<"add_ZPX"<< std::endl;
}

void cpu::add_ZPY() //tested status : working
{   
    cpu::program_counter++;

    cpu::address_bus = cpu::memory[program_counter];
    cpu::address_bus = cpu::address_bus + cpu::Y_reg;
    
    cpu::data_bus = cpu::memory[cpu::address_bus];

    std::cout <<"add_ZPY"<< std::endl;
}

void cpu::add_REL() //tested status : working
{   cpu::program_counter++;
    int8_t offset = cpu::memory[cpu::program_counter];
    cpu::address_bus = cpu::program_counter + offset;

    std::cout <<"add_REL"<< std::endl;
}

void cpu::add_ABS() //tested status : working
{   // basically what this code does is mem = [10 30]
    // our data is located at the add given by the above data in memory
    // since 6502 is little endian our the address is located at 3010
    // therefore the data in adress bus becomes 3010 and the data is located at the address in the address bus
    cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::program_counter++;
    cpu::address_bus = cpu::address_bus | (memory[program_counter]<<8); 
    
    cpu::data_bus = cpu::memory[cpu::address_bus];

    std::cout <<"add_ABS"<< std::endl;
}

void cpu::add_ABX() //tested status : working
{   
    cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::program_counter++;
    cpu::address_bus = cpu::address_bus | (memory[program_counter]<<8); 

    cpu::address_bus = cpu::address_bus + cpu::X_reg;

    cpu::data_bus = cpu::memory[cpu::address_bus];
    std::cout <<"add_ABX"<< std::endl;
}

void cpu::add_ABY() //tested status : working
{   cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::program_counter++;
    cpu::address_bus = cpu::address_bus | (memory[program_counter]<<8); 

    cpu::address_bus = cpu::address_bus + cpu::Y_reg;

    cpu::data_bus = cpu::memory[cpu::address_bus];
    std::cout <<"add_ABY"<< std::endl;
}

void cpu::add_IND() //tested status : working
{   
    cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::program_counter++;
    cpu::address_bus = cpu::address_bus | (memory[program_counter]<<8);
    cpu::temp_add = cpu::memory[cpu::address_bus];
    cpu::address_bus = cpu::temp_add | (cpu::memory[++cpu::address_bus]<<8);

    
    std::cout <<"add_IND"<< std::endl;
}

void cpu::add_iIND()    //tested status : working
{   
    cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::address_bus = cpu::address_bus + cpu::X_reg;
    cpu::temp_add = cpu::memory[cpu::address_bus];
    cpu::address_bus = cpu::temp_add | (cpu::memory[++cpu::address_bus]<<8);
    cpu::data_bus = cpu::memory[cpu::address_bus];


    std::cout <<"add_iIND"<< std::endl;
}

void cpu::add_INDi()    //tested status : working
{   
    cpu::program_counter++;
    cpu::address_bus = cpu::memory[program_counter];
    cpu::temp_add = cpu::memory[cpu::address_bus];
    cpu::address_bus = cpu::temp_add | (cpu::memory[++cpu::address_bus]<<8);
    cpu::address_bus = cpu::address_bus + cpu::Y_reg;
    cpu::data_bus = cpu::memory[cpu::address_bus];

    std::cout <<"add_INDi"<< std::endl;
}

//Helper function Definitions

// void cpu::flash_mem(std::initializer_list<uint8_t> val) {
//     if (val.size() > memory.size()) {
//         std::cerr << "Error: Too many values provided for the memory array." << std::endl;
//         return;
//     }

//     std::copy(val.begin(), val.end(), memory.begin());
// }

void cpu::flash_mem(const std::vector<uint8_t>& val) {
        if (val.size() > memory.size()) {
            std::cerr << "Error: Too many values provided for the memory array." << std::endl;
            return;
        }

        std::copy(val.begin(), val.end(), memory.begin());
    }

void cpu::flash_mem_at_loc(uint8_t val ,uint16_t loc)
{
    cpu::memory[loc] = val;

}

void cpu::print_mem(uint8_t upto_add) const {
    std::cout <<std::endl;
    std::cout << "----------MEMORY----------" <<std::endl;
    for (uint8_t i = 0; i <= upto_add; ++i){
        std::cout << " memory[" << static_cast<int>(i) << "] = " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(memory[i]);

        if (i % 5 == 4 || i == upto_add) {
            std::cout << std::endl;  // Move to the next line
        } 
        else {
            std::cout << " ";  // Add space between elements in the same line
        }
    }
    std::cout <<std::endl;
}

void cpu::fetch_ins()
{   
    // instruction fetch_ret;

    uint8_t opcode = memory[program_counter];
    // std::cout << "opcode = " << std::hex << static_cast<int>(opcode) << std::endl;
    

    fetch_ret.add_mode_ptr = ins_table[opcode].add_mode_ptr;
    fetch_ret.operation_ptr = ins_table[opcode].operation_ptr;
    fetch_ret.cycles = ins_table[opcode].cycles;

    // return fetch_ret;
}

void cpu::exe_ins(void (cpu::*addModeType)(), void (cpu::*operation)(), uint8_t cycles) {
    std::cout <<std::endl;
    std::cout << "----------EXECUTED FUNCTIONS----------" <<std::endl;
    // Call the address mode function
    (this->*addModeType)();

    // Call the operation function
    (this->*operation)();

    cpu::program_counter++;

    std::cout <<std::endl;
}


// Sets or clears a specific bit of the status register
void cpu::set_flag(flag f, bool v)
{
	if (v)
		cpu::status_reg |= f;
	else
		cpu::status_reg &= ~f;
}

// // Returns the value of a specific bit of the status register
uint8_t cpu::get_flag(flag f)
{
	return ((cpu::status_reg & f) > 0) ? 1 : 0;
}

void printEmulatorTitle() {

    
    std::cout << "   #######################################" << std::endl;
    std::cout << " #########################################" << std::endl;
    std::cout << " #                                     ###" << std::endl;
    std::cout << " #   666666  555555   000000  222222   ### " << std::endl;
    std::cout << " #   66      55       00  00      22   ###" << std::endl;
    std::cout << " #   666666  555555   00  00  222222   ###" << std::endl;
    std::cout << " #   6   66      55   00  00  2        ###" << std::endl;
    std::cout << " #   666666  555555   000000  222222   ###" << std::endl;
    std::cout << " #                                     ###" << std::endl;
    std::cout << " ########################################" << std::endl;
    std::cout << std::endl;
}

int main()
{   printEmulatorTitle();
    std::cout <<"<<<COMPILED SUCCESSFULLY>>>"<< std::endl;

    
    cpu my_6502;
    
    std::vector<uint8_t> flash_code = {0xA9,0x10,0xA9,0x10}; //OPCODES WHICH WILL BE FLASHED
    uint8_t print_mem_upto = 0x15;
    int flashed_code_size = flash_code.size()+1;
    int cpu_stats_upto = flashed_code_size; //NOTE: CPU stats are printed in a step of 2, since the pc is incremented at execute function.

    std::cout << "DEBUG_FLASH CODE SIZE" << std::hex << flash_code.size() << std::endl;

    my_6502.flash_mem(flash_code);
    my_6502.flash_mem_at_loc(0x20,0x10); // add_bus = 2010
    // my_6502.flash_mem_at_loc(-0x03,0x1001);
    // my_6502.flash_mem_at_loc(0xAA,0x3553);
    my_6502.accumulator = 0xCC;
    my_6502.X_reg = 0xAA;
    my_6502.Y_reg = 0xFF;
    my_6502.print_mem(print_mem_upto);

    while (my_6502.program_counter <= flashed_code_size) //The while loop is configured to execute instructions until reaching the final position of the flashed code.
    {                                          
        my_6502.fetch_ins();

        my_6502.exe_ins( my_6502.fetch_ret.add_mode_ptr, my_6502.fetch_ret.operation_ptr, my_6502.fetch_ret.cycles);
        
        if(my_6502.program_counter <= cpu_stats_upto) //This if statement is to print CPU stats, used for debugging.
        {
            //print data bus and address bus
            std::cout <<std::endl;
            std::cout << "----------BUSES----------" <<std::endl;
            std::cout << "DATABUS : 0x" << std::hex << static_cast<int>(my_6502.data_bus) << std::endl;
            std::cout << "ADDRESSBUS : 0x" << std::hex << static_cast<int>(my_6502.address_bus) << std::endl;
            std::cout <<std::endl;
            
            std::cout <<std::endl;
            std::cout << "----------REGISTERS----------" <<std::endl;
            std::cout << "PROGRAM COUNTER : 0x" << std::hex << static_cast<int>(my_6502.program_counter) << std::endl;
            std::cout << "ACCUMULATOR REG : 0x" << std::hex << static_cast<int>(my_6502.accumulator) << std::endl;
            std::cout << "X REG : 0x" << std::hex << static_cast<int>(my_6502.X_reg) << std::endl;
            std::cout << "Y REG : 0x" << std::hex << static_cast<int>(my_6502.Y_reg) << std::endl;
            std::cout << "STACK POINTER : 0x" << std::hex << static_cast<int>(my_6502.stack_pointer) << std::endl;
            std::cout << "STATUS REG FLAGS :" << std::endl;
            std::cout << "N=" << ((my_6502.status_reg >> 7) & 1) << " ";
            std::cout << "V=" << ((my_6502.status_reg >> 6) & 1) << " ";
            std::cout << "U=" << ((my_6502.status_reg >> 5) & 1) << " ";
            std::cout << "B=" << ((my_6502.status_reg >> 4) & 1) << " ";
            std::cout << "D=" << ((my_6502.status_reg >> 3) & 1) << " ";
            std::cout << "I=" << ((my_6502.status_reg >> 2) & 1) << " ";
            std::cout << "Z=" << ((my_6502.status_reg >> 1) & 1) << " ";
            std::cout << "C=" << (my_6502.status_reg & 1) << std::endl;

            std::cout <<std::endl;

            my_6502.print_mem(print_mem_upto);
    
        }
        
    }
    std::cout << "**********COMPLETED EXECUTION**********" <<std::endl;
    return 0;
}


  

// ins_table = {
//         //                       0                                1                               2                               3                                 4                               5                               6                              7                                   8                            9                               A                                 B                             C                                D                                E                               F                                
//         /* 0 */ { &cpu::BRK, &cpu::add_IMP, 7 },{ &cpu::ORA, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SLO, &cpu::add_iIND, 8 },{ &cpu::NOP, &cpu::add_ZP0, 3 },{ &cpu::ORA, &cpu::add_ZP0, 3 },{ &cpu::ASL, &cpu::add_ZP0, 5 },{ &cpu::SLO, &cpu::add_ZP0, 5 },{ &cpu::PHP, &cpu::add_IMP, 3 },{ &cpu::ORA, &cpu::add_IMM, 2 },{ &cpu::ASL, &cpu::add_IMP, 2 },{ &cpu::ANC, &cpu::add_IMP, 2 },{ &cpu::NOP, &cpu::add_ABS, 4 },{ &cpu::ORA, &cpu::add_ABS, 4 },{ &cpu::ASL, &cpu::add_ABS, 6 },{ &cpu::SLO, &cpu::add_ABS, 6 },
//         /* 1 */ { &cpu::BPL, &cpu::add_REL, 2 },{ &cpu::ORA, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SLO, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::ORA, &cpu::add_ZPX, 4 },{ &cpu::ASL, &cpu::add_ZPX, 6 },{ &cpu::SLO, &cpu::add_ZPX, 6 },{ &cpu::CLC, &cpu::add_IMP, 2 },{ &cpu::ORA, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SLO, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::ORA, &cpu::add_ABX, 4 },{ &cpu::ASL, &cpu::add_ABX, 7 },{ &cpu::SLO, &cpu::add_ABX, 7 },
//         /* 2 */ { &cpu::JSR, &cpu::add_ABS, 6 },{ &cpu::AND, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RLA, &cpu::add_iIND, 8 },{ &cpu::BIT, &cpu::add_ZP0, 3 },{ &cpu::AND, &cpu::add_ZP0, 3 },{ &cpu::ROL, &cpu::add_ZP0, 5 },{ &cpu::RLA, &cpu::add_ZP0, 5 },{ &cpu::PLP, &cpu::add_IMP, 4 },{ &cpu::AND, &cpu::add_IMM, 2 },{ &cpu::ROL, &cpu::add_IMP, 2 },{ &cpu::ANC, &cpu::add_IMP, 2 },{ &cpu::BIT, &cpu::add_ABS, 4 },{ &cpu::AND, &cpu::add_ABS, 4 },{ &cpu::ROL, &cpu::add_ABS, 6 },{ &cpu::RLA, &cpu::add_ABS, 6 },
//         /* 3 */	{ &cpu::BMI, &cpu::add_REL, 2 },{ &cpu::AND, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RLA, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::AND, &cpu::add_ZPX, 4 },{ &cpu::ROL, &cpu::add_ZPX, 6 },{ &cpu::RLA, &cpu::add_ZPX, 6 },{ &cpu::SEC, &cpu::add_IMP, 2 },{ &cpu::AND, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::RLA, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::AND, &cpu::add_ABX, 4 },{ &cpu::ROL, &cpu::add_ABX, 7 },{ &cpu::RLA, &cpu::add_ABX, 7 },
//         /* 4 */	{ &cpu::RTI, &cpu::add_IMP, 6 },{ &cpu::EOR, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SRE, &cpu::add_iIND, 8 },{ &cpu::NOP, &cpu::add_ZP0, 3 },{ &cpu::EOR, &cpu::add_ZP0, 3 },{ &cpu::LSR, &cpu::add_ZP0, 5 },{ &cpu::SRE, &cpu::add_ZP0, 5 },{ &cpu::PHA, &cpu::add_IMP, 3 },{ &cpu::EOR, &cpu::add_IMM, 2 },{ &cpu::LSR, &cpu::add_IMP, 2 },{ &cpu::ALR, &cpu::add_IMP, 2 },{ &cpu::JMP, &cpu::add_ABS, 3 },{ &cpu::EOR, &cpu::add_ABS, 4 },{ &cpu::LSR, &cpu::add_ABS, 6 },{ &cpu::SRE, &cpu::add_ABS, 6 },
//         /* 5 */ { &cpu::BVC, &cpu::add_REL, 2 },{ &cpu::EOR, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SRE, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::EOR, &cpu::add_ZPX, 4 },{ &cpu::LSR, &cpu::add_ZPX, 6 },{ &cpu::SRE, &cpu::add_ZPX, 6 },{ &cpu::CLI, &cpu::add_IMP, 2 },{ &cpu::EOR, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SRE, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::EOR, &cpu::add_ABX, 4 },{ &cpu::LSR, &cpu::add_ABX, 7 },{ &cpu::SRE, &cpu::add_ABX, 7 },
//         /* 6 */	{ &cpu::RTS, &cpu::add_IMP, 6 },{ &cpu::ADC, &cpu::add_iIND, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RRA, &cpu::add_iIND, 8 },{ &cpu::NOP, &cpu::add_ZP0, 3 },{ &cpu::ADC, &cpu::add_ZP0, 3 },{ &cpu::ROR, &cpu::add_ZP0, 5 },{ &cpu::RRA, &cpu::add_ZP0, 5 },{ &cpu::PLA, &cpu::add_IMP, 4 },{ &cpu::ADC, &cpu::add_IMM, 2 },{ &cpu::ROR, &cpu::add_IMP, 2 },{ &cpu::ARR, &cpu::add_IMP, 2 },{ &cpu::JMP, &cpu::add_IND, 5 },{ &cpu::ADC, &cpu::add_ABS, 4 },{ &cpu::ROR, &cpu::add_ABS, 6 },{ &cpu::RRA, &cpu::add_ABS, 6 },
//         /* 7 */	{ &cpu::BVS, &cpu::add_REL, 2 },{ &cpu::ADC, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::RRA, &cpu::add_INDi, 8 },{ &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::ADC, &cpu::add_ZPX, 4 },{ &cpu::ROR, &cpu::add_ZPX, 6 },{ &cpu::RRA, &cpu::add_ZPX, 6 },{ &cpu::SEI, &cpu::add_IMP, 2 },{ &cpu::ADC, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::RRA, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::ADC, &cpu::add_ABX, 4 },{ &cpu::ROR, &cpu::add_ABX, 7 },{ &cpu::RRA, &cpu::add_ABX, 7 },
//         /* 8 */	{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::STA, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SAX, &cpu::add_IMP, 6 }, { &cpu::STY, &cpu::add_ZP0, 3 },{ &cpu::STA, &cpu::add_ZP0, 3 },{ &cpu::STX, &cpu::add_ZP0, 3 },{ &cpu::SAX, &cpu::add_ZP0, 3 },{ &cpu::DEY, &cpu::add_IMP, 2 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::TXA, &cpu::add_IMP, 2 },{ &cpu::ANE, &cpu::add_IMP, 2 },{ &cpu::STY, &cpu::add_ABS, 4 },{ &cpu::STA, &cpu::add_ABS, 4 },{ &cpu::STX, &cpu::add_ABS, 4 },{ &cpu::SAX, &cpu::add_ABS, 4 },
//         /* 9 */	{ &cpu::BCC, &cpu::add_REL, 2 },{ &cpu::STA, &cpu::add_INDi, 6 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::SHA, &cpu::add_IMP, 6 }, { &cpu::STY, &cpu::add_ZPX, 4 },{ &cpu::STA, &cpu::add_ZPX, 4 },{ &cpu::STX, &cpu::add_ZPY, 4 },{ &cpu::SAX, &cpu::add_ZPX, 4 },{ &cpu::TYA, &cpu::add_IMP, 2 },{ &cpu::STA, &cpu::add_ABY, 5 },{ &cpu::TXS, &cpu::add_IMP, 2 },{ &cpu::TAS, &cpu::add_ABY, 5 },{ &cpu::SHY, &cpu::add_ABX, 5 },{ &cpu::STA, &cpu::add_ABX, 5 },{ &cpu::SHX, &cpu::add_ABY, 5 },{ &cpu::SHA, &cpu::add_ABY, 5 },
//         /* A */	{ &cpu::LDY, &cpu::add_IMM, 2 },{ &cpu::LDA, &cpu::add_iIND, 6 },{ &cpu::LDX, &cpu::add_IMM, 2 },{ &cpu::LAX, &cpu::add_IMP, 6 }, { &cpu::LDY, &cpu::add_ZP0, 3 },{ &cpu::LDA, &cpu::add_ZP0, 3 },{ &cpu::LDX, &cpu::add_ZP0, 3 },{ &cpu::LAX, &cpu::add_ZP0, 3 },{ &cpu::TAY, &cpu::add_IMP, 2 },{ &cpu::LDA, &cpu::add_IMM, 2 },{ &cpu::TAX, &cpu::add_IMP, 2 },{ &cpu::LXA, &cpu::add_IMP, 2 },{ &cpu::LDY, &cpu::add_ABS, 4 },{ &cpu::LDA, &cpu::add_ABS, 4 },{ &cpu::LDX, &cpu::add_ABS, 4 },{ &cpu::LAX, &cpu::add_ABS, 4 },
//         /* B */	{ &cpu::BCS, &cpu::add_REL, 2 },{ &cpu::LDA, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::LAX, &cpu::add_IMP, 5 }, { &cpu::LDY, &cpu::add_ZPX, 4 },{ &cpu::LDA, &cpu::add_ZPX, 4 },{ &cpu::LDX, &cpu::add_ZPY, 4 },{ &cpu::LAX, &cpu::add_ZPX, 4 },{ &cpu::CLV, &cpu::add_IMP, 2 },{ &cpu::LDA, &cpu::add_ABY, 4 },{ &cpu::TSX, &cpu::add_IMP, 2 },{ &cpu::LAS, &cpu::add_ABY, 4 },{ &cpu::LDY, &cpu::add_ABX, 4 },{ &cpu::LDA, &cpu::add_ABX, 4 },{ &cpu::LDX, &cpu::add_ABY, 4 },{ &cpu::LAX, &cpu::add_ABY, 4 },
//         /* C */	{ &cpu::CPY, &cpu::add_IMM, 2 },{ &cpu::CMP, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::DCP, &cpu::add_IMP, 8 }, { &cpu::CPY, &cpu::add_ZP0, 3 },{ &cpu::CMP, &cpu::add_ZP0, 3 },{ &cpu::DEC, &cpu::add_ZP0, 5 },{ &cpu::DCP, &cpu::add_ZP0, 5 },{ &cpu::INY, &cpu::add_IMP, 2 },{ &cpu::CMP, &cpu::add_IMM, 2 },{ &cpu::DEX, &cpu::add_IMP, 2 },{ &cpu::SBX, &cpu::add_IMP, 2 },{ &cpu::CPY, &cpu::add_ABS, 4 },{ &cpu::CMP, &cpu::add_ABS, 4 },{ &cpu::DEC, &cpu::add_ABS, 6 },{ &cpu::DCP, &cpu::add_ABS, 6 },
//         /* D */	{ &cpu::BNE, &cpu::add_REL, 2 },{ &cpu::CMP, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::DCP, &cpu::add_IMP, 8 }, { &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::CMP, &cpu::add_ZPX, 4 },{ &cpu::DEC, &cpu::add_ZPX, 6 },{ &cpu::DCP, &cpu::add_ZPX, 6 },{ &cpu::CLD, &cpu::add_IMP, 2 },{ &cpu::CMP, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::DCP, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::CMP, &cpu::add_ABX, 4 },{ &cpu::DEC, &cpu::add_ABX, 7 },{ &cpu::DCP, &cpu::add_ABX, 7 },
//         /* E */	{ &cpu::CPX, &cpu::add_IMM, 2 },{ &cpu::SBC, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::ISC, &cpu::add_IMP, 8 }, { &cpu::CPX, &cpu::add_ZP0, 3 },{ &cpu::SBC, &cpu::add_ZP0, 3 },{ &cpu::INC, &cpu::add_ZP0, 5 },{ &cpu::ISC, &cpu::add_ZP0, 5 },{ &cpu::INX, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_IMM, 2 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_IMP, 2 },{ &cpu::CPX, &cpu::add_ABS, 4 },{ &cpu::SBC, &cpu::add_ABS, 4 },{ &cpu::INC, &cpu::add_ABS, 6 },{ &cpu::ISC, &cpu::add_ABS, 6 },
//         /* F */	{ &cpu::BEQ, &cpu::add_REL, 2 },{ &cpu::SBC, &cpu::add_INDi, 5 },{ &cpu::JAM, &cpu::add_IMP, 2 },{ &cpu::ISC, &cpu::add_IMP, 8 }, { &cpu::NOP, &cpu::add_ZPX, 4 },{ &cpu::SBC, &cpu::add_ZPX, 4 },{ &cpu::INC, &cpu::add_ZPX, 6 },{ &cpu::ISC, &cpu::add_ZPX, 6 },{ &cpu::SED, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::ISC, &cpu::add_ABY, 7 },{ &cpu::NOP, &cpu::add_ABX, 4 },{ &cpu::SBC, &cpu::add_ABX, 4 },{ &cpu::INC, &cpu::add_ABX, 7 },{ &cpu::ISC, &cpu::add_ABX, 7 },

// //         //REMEMBER  A-0,2,4,6  ADD MODE A CHECK INSTRUCTION TABLE WEBSITE     
//         };

