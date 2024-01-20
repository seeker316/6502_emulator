#include "cpu.h"
#include <iostream>


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

}

cpu::~cpu()
{
 //Destructor
}

// Function Defintions Start Here..............

//Load operations definitions
void cpu::LDA()
{
    std::cout <<"LDA"<< std::endl;
}

void cpu::LDX()
{
    std::cout <<"LDX"<< std::endl;
}

void cpu::LDY()
{
    std::cout <<"LDY"<< std::endl;
}

void cpu::STA()
{
    std::cout <<"STA"<< std::endl;
}

void cpu::STX()
{
    std::cout <<"STX"<< std::endl;
}

void cpu::STY()
{
    std::cout <<"STY"<< std::endl;
}

//Register transfer operations definitions
void cpu::TAX()
{
    std::cout <<"TAX"<< std::endl;
}

void cpu::TAY()
{
    std::cout <<"TAY"<< std::endl;
}

void cpu::TXA()
{
    std::cout <<"TXA"<< std::endl;
}

void cpu::TYA()
{
    std::cout <<"TYA"<< std::endl;
}

//Stack operations definitions
void cpu::TSX()
{
    std::cout <<"TSX"<< std::endl;
}

void cpu::TXS()
{
    std::cout <<"TXS"<< std::endl;
}

void cpu::PHA()
{
    std::cout <<"PHA"<< std::endl;
}

void cpu::PHP()
{
    std::cout <<"PHP"<< std::endl;
}

void cpu::PLA()
{
    std::cout <<"PLA"<< std::endl;
}

void cpu::PLP()
{
    std::cout <<"PLP"<< std::endl;
}

//Logical operations definitions

void cpu::AND()
{
    std::cout <<"AND"<< std::endl;
}

void cpu::EOR()
{
    std::cout <<"EOR"<< std::endl;
}

void cpu::ORA()
{
    std::cout <<"ORA"<< std::endl;
}

void cpu::BIT()
{
    std::cout <<"BIT"<< std::endl;
}

//Arithemteic operations definitions
void cpu::ADC()
{
    std::cout <<"ADC"<< std::endl;
}

void cpu::SBC()
{
    std::cout <<"SBC"<< std::endl;
}

void cpu::CMP()
{
    std::cout <<"CMP"<< std::endl;
}

void cpu::CPX()
{
    std::cout <<"CPX"<< std::endl;
}

void cpu::CPY()
{
    std::cout <<"CPY"<< std::endl;
}


//Increments and Decrement operations definitions

void cpu::INC()
{
    std::cout <<"INC"<< std::endl;
}

void cpu::INX()
{
    std::cout <<"INX"<< std::endl;
}

void cpu::INY()
{
    std::cout <<"INY"<< std::endl;
}

void cpu::DEC()
{
    std::cout <<"DEC"<< std::endl;
}

void cpu::DEX()
{
    std::cout <<"DEX"<< std::endl;
}

void cpu::DEY()
{
    std::cout <<"DEY"<< std::endl;
}

//Shift operations definitions
void cpu::ASL()
{
    std::cout <<"ASL"<< std::endl;
}

void cpu::LSR()
{
    std::cout <<"LSR"<< std::endl;
}

void cpu::ROL()
{
    std::cout <<"ROL"<< std::endl;
}

void cpu::ROR()
{
    std::cout <<"ROR"<< std::endl;
}

//Jump and Call operations definitions

void cpu::JMP()
{
    std::cout <<"JMP"<< std::endl;
}

void cpu::JSR()
{
    std::cout <<"JSR"<< std::endl;
}

void cpu::RTS()
{
    std::cout <<"RTS"<< std::endl;
}

//Branching operations definitions
void cpu::BCC()
{
    std::cout <<"BCC"<< std::endl;
}

void cpu::BCS()
{
    std::cout <<"BCS"<< std::endl;
}

void cpu::BEQ()
{
    std::cout <<"BEQ"<< std::endl;
}

void cpu::BMI()
{
    std::cout <<"BMI"<< std::endl;
}

void cpu::BNE()
{
    std::cout <<"BNE"<< std::endl;
}

void cpu::BPL()
{
    std::cout <<"BPL"<< std::endl;
}

void cpu::BVC()
{
    std::cout <<"BVC"<< std::endl;
}

void cpu::BVS()
{
    std::cout <<"BVS"<< std::endl;
}

//Status flag changes operations definitions
void cpu::CLC()
{
    std::cout <<"CLC"<< std::endl;
}

void cpu::CLD()
{
    std::cout <<"CLD"<< std::endl;
}

void cpu::CLI()
{
    std::cout <<"CLI"<< std::endl;
}

void cpu::CLV()
{
    std::cout <<"CLV"<< std::endl;
}

void cpu::SEC()
{
    std::cout <<"SEC"<< std::endl;
}

void cpu::SED()
{
    std::cout <<"SED"<< std::endl;
}

void cpu::SEI()
{
    std::cout <<"SEI"<< std::endl;
}

//SYSTEM CHANGES operations definitions
void cpu::BRK()
{
    std::cout <<"BRK"<< std::endl;
}

void cpu::RTI()
{
    std::cout <<"RTI"<< std::endl;
}

//Illegal opcodes definitions

void cpu::NOP()
{
    std::cout <<"NOP"<< std::endl;
}

void cpu::JAM()
{
    std::cout <<"JAM"<< std::endl;
}

void cpu::SLO()
{
    std::cout <<"SLO"<< std::endl;
}

void cpu::RLA()
{
    std::cout <<"RLA"<< std::endl;
}

void cpu::SRE()
{
    std::cout <<"SRE"<< std::endl;
}

void cpu::RRA()
{
    std::cout <<"RRA"<< std::endl;
}

void cpu::SAX()
{
    std::cout <<"SAX"<< std::endl;
}

void cpu::SHA()
{
    std::cout <<"SHA"<< std::endl;
}

void cpu::LAX()
{
    std::cout <<"LAX"<< std::endl;
}

void cpu::DCP()
{
    std::cout <<"DCP"<< std::endl;
}

void cpu::ISC()
{
    std::cout <<"ISC"<< std::endl;
}

void cpu::ANC()
{
    std::cout <<"ANC"<< std::endl;
}

void cpu::ALR()
{
    std::cout <<"ALR"<< std::endl;
}

void cpu::ARR()
{
    std::cout <<"ARR"<< std::endl;
}

void cpu::ANE()
{
    std::cout <<"ANE"<< std::endl;
}

void cpu::TAS()
{
    std::cout <<"TAS"<< std::endl;
}

void cpu::LXA()
{
    std::cout <<"LXA"<< std::endl;
}

void cpu::LAS()
{
    std::cout <<"LAS"<< std::endl;
}

void cpu::SBX()
{
    std::cout <<"SBX"<< std::endl;
}

void cpu::SHY()
{
    std::cout <<"SHY"<< std::endl;
}

void cpu::SHX()
{
    std::cout <<"SHX"<< std::endl;
}

//Addressing modes definitions
void cpu::add_IMP()
{
    std::cout <<"add_IMP"<< std::endl;
}

void cpu::add_IMM()
{
    std::cout <<"add_IMM"<< std::endl;
}

void cpu::add_ACC()
{
    std::cout <<"add_ACC"<< std::endl;
}

void cpu::add_ZP0()
{
    std::cout <<"add_ZP0"<< std::endl;
}

void cpu::add_ZPX()
{
    std::cout <<"add_ZPX"<< std::endl;
}

void cpu::add_ZPY()
{
    std::cout <<"add_ZPY"<< std::endl;
}

void cpu::add_REL()
{
    std::cout <<"add_REL"<< std::endl;
}

void cpu::add_ABS()
{
    std::cout <<"add_ABS"<< std::endl;
}

void cpu::add_ABX()
{
    std::cout <<"add_ABX"<< std::endl;
}

void cpu::add_ABY()
{
    std::cout <<"add_ABY"<< std::endl;
}

void cpu::add_IND()
{
    std::cout <<"add_IND"<< std::endl;
}

void cpu::add_iIND()
{
    std::cout <<"add_iIND"<< std::endl;
}

void cpu::add_INDi()
{
    std::cout <<"add_INDi"<< std::endl;
}

//Helper function Definitions

void cpu::flash_mem(std::initializer_list<uint8_t> val) {
    if (val.size() > memory.size()) {
        std::cerr << "Error: Too many values provided for the memory array." << std::endl;
        return;
    }

    std::copy(val.begin(), val.end(), memory.begin());
}

void cpu::print_mem(uint8_t upto_add) const {
    for (uint8_t i = 0; i <= upto_add; ++i) {
        std::cout << "memory[" << static_cast<int>(i) << "] = " << std::hex << static_cast<int>(memory[i]) << std::endl;

    }
}

cpu::instruction cpu::fetch_ins()
{   
    instruction fetch_ret;

    uint8_t opcode = memory[program_counter];
    // std::cout << "opcode = " << std::hex << static_cast<int>(opcode) << std::endl;
    

    fetch_ret.add_mode_ptr = ins_table[opcode].add_mode_ptr;
    fetch_ret.operation_ptr = ins_table[opcode].operation_ptr;
    fetch_ret.cycles = ins_table[opcode].cycles;

    return fetch_ret;
}

void cpu::exe_ins(void (cpu::*addModeType)(), void (cpu::*operation)(), uint8_t cycles) {

    // Call the address mode function
    (this->*addModeType)();

    // Call the operation function
    (this->*operation)();
}


int main()
{
    std::cout <<"COMPILED SUCCESSFULLY"<< std::endl;

    cpu my_6502;
    uint8_t print_mem_upto = 0x05;

    my_6502.flash_mem({0xA9, 0x42}); //LDA add_IMM
    my_6502.print_mem(print_mem_upto);

    cpu::instruction ins_info = my_6502.fetch_ins();

    my_6502.exe_ins(ins_info.add_mode_ptr, ins_info.operation_ptr, ins_info.cycles);


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

