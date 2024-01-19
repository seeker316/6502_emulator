#include <cstdint>
#include <array>
#include <vector>
class cpu
{
public:
    cpu();
    ~cpu();

public:
    uint16_t program_counter = 0x0000;

    uint8_t stack_pointer = 0x00;
    uint8_t accumulator = 0x00;
    uint8_t X_reg = 0x00;
    uint8_t Y_reg = 0x00;

    struct flag_reg
    {
        bool carry_flag = 0;
        bool zero_flag = 0;
        bool interrupt_disable_flag = 0;
        bool decimal_mode_flag = 0;
        bool break_flag = 0;
        bool reserved_flag = 0;
        bool overflow_flag = 0;
        bool negative_flag = 0;
    };

    struct bus {

        uint8_t data_bus = 0x00;
        uint16_t address_bus = 0x0000;
    };

private:
    std::array<uint8_t, 64 *1024> memory;


public: //  DECLARING 6502 INSTRUCTION SET

// Load operations functions
    void LDA(); void LDX(); void LDY();
    void STA(); void STX(); void STY();

// Register transfer functions
    void TAX(); void TAY(); void TXA(); void TYA();

// Stack operations
    void TSX(); void TXS(); void PHA();
    void PHP(); void PLA(); void PLP();

// Logical operations
    void AND(); void EOR(); void ORA(); void BIT();

// Arithemetic operations
    void ADC(); void SBC(); void CMP();
    void CPX(); void CPY();

// increments nd decrements
    void INC(); void INX(); void INY();
    void DEC(); void DEX(); void DEY();

// Shifts
    void ASL(); void LSR(); void ROL(); void ROR();

// Jumops and calls 
    void JMP(); void JSR(); void RTS();

// Branches 
    void BCC(); void BCS(); void BEQ(); void BMI();
    void BNE(); void BPL(); void BVC(); void BVS();

//Status flag change
    void CLC(); void CLD(); void CLI();
    void CLV(); void SEC(); void SED(); void SEI();

// system changes
    void BRK(); void NOP(); void RTI();

//illegal opcodes capture function 
    void NAN();

public: // ADDRESSING MODES
    void add_IMP(); // add_IMPlicit addressing mode
    void add_IMM(); // add_IMMediate addressing mode
    void add_ACC(); // accumulator addressing mode
    void add_ZP0(); // zero page addressing mode
    void add_ZPX(); // zero page,X addressing mode
    void add_ZPY(); // zero page, Y addressing mode
    void add_REL(); // add_RELative addressing mode
    void add_ABS(); // add_ABSolute addressing mode
    void add_ABX(); // add_ABSolute addressing mode x
    void add_ABY(); // add_ABSolute addressing mode y
    void add_IND(); // indirect addressing mode
    void add_iIND(); //indexed indirect addressing mode
    void add_INDi(); // indirect indexed addressing mode   

};

struct instruction{
    void (*add_mode_ptr)();
    void (*operation_ptr)();
    uint8_t cycles;
}


std::vector<instruction> ins_table = {
        { &cpu::BRK, &cpu::add_IMP, 7 },{ &cpu::ORA, &cpu::add_iIND, 6 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 3 },{ &cpu::ORA, &cpu::add_ZP0, 3 },{ &cpu::ASL, &cpu::add_ZP0, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::PHP, &cpu::add_IMP, 3 },{ &cpu::ORA, &cpu::add_IMM, 2 },{ &cpu::ASL, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::ORA, &cpu::add_ABS, 4 },{ &cpu::ASL, &cpu::add_ABS, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },
		{ &cpu::BPL, &cpu::add_REL, 2 },{ &cpu::ORA, &cpu::add_INDi, 5 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::ORA, &cpu::add_ZPX, 4 },{ &cpu::ASL, &cpu::add_ZPX, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::CLC, &cpu::add_IMP, 2 },{ &cpu::ORA, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 7 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::ORA, &cpu::add_ABX, 4 },{ &cpu::ASL, &cpu::add_ABX, 7 },{ &cpu::NAN, &cpu::add_IMP, 7 },
		{ &cpu::JSR, &cpu::add_ABS, 6 },{ &cpu::AND, &cpu::add_iIND, 6 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::BIT, &cpu::add_ZP0, 3 },{ &cpu::AND, &cpu::add_ZP0, 3 },{ &cpu::ROL, &cpu::add_ZP0, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::PLP, &cpu::add_IMP, 4 },{ &cpu::AND, &cpu::add_IMM, 2 },{ &cpu::ROL, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::BIT, &cpu::add_ABS, 4 },{ &cpu::AND, &cpu::add_ABS, 4 },{ &cpu::ROL, &cpu::add_ABS, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },
		{ &cpu::BMI, &cpu::add_REL, 2 },{ &cpu::AND, &cpu::add_INDi, 5 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::AND, &cpu::add_ZPX, 4 },{ &cpu::ROL, &cpu::add_ZPX, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::SEC, &cpu::add_IMP, 2 },{ &cpu::AND, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 7 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::AND, &cpu::add_ABX, 4 },{ &cpu::ROL, &cpu::add_ABX, 7 },{ &cpu::NAN, &cpu::add_IMP, 7 },
		{ &cpu::RTI, &cpu::add_IMP, 6 },{ &cpu::EOR, &cpu::add_iIND, 6 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 3 },{ &cpu::EOR, &cpu::add_ZP0, 3 },{ &cpu::LSR, &cpu::add_ZP0, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::PHA, &cpu::add_IMP, 3 },{ &cpu::EOR, &cpu::add_IMM, 2 },{ &cpu::LSR, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::JMP, &cpu::add_ABS, 3 },{ &cpu::EOR, &cpu::add_ABS, 4 },{ &cpu::LSR, &cpu::add_ABS, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },
		{ &cpu::BVC, &cpu::add_REL, 2 },{ &cpu::EOR, &cpu::add_INDi, 5 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::EOR, &cpu::add_ZPX, 4 },{ &cpu::LSR, &cpu::add_ZPX, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::CLI, &cpu::add_IMP, 2 },{ &cpu::EOR, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 7 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::EOR, &cpu::add_ABX, 4 },{ &cpu::LSR, &cpu::add_ABX, 7 },{ &cpu::NAN, &cpu::add_IMP, 7 },
		{ &cpu::RTS, &cpu::add_IMP, 6 },{ &cpu::ADC, &cpu::add_iIND, 6 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 3 },{ &cpu::ADC, &cpu::add_ZP0, 3 },{ &cpu::ROR, &cpu::add_ZP0, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::PLA, &cpu::add_IMP, 4 },{ &cpu::ADC, &cpu::add_IMM, 2 },{ &cpu::ROR, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::JMP, &cpu::add_IND, 5 },{ &cpu::ADC, &cpu::add_ABS, 4 },{ &cpu::ROR, &cpu::add_ABS, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },
		{ &cpu::BVS, &cpu::add_REL, 2 },{ &cpu::ADC, &cpu::add_INDi, 5 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::ADC, &cpu::add_ZPX, 4 },{ &cpu::ROR, &cpu::add_ZPX, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::SEI, &cpu::add_IMP, 2 },{ &cpu::ADC, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 7 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::ADC, &cpu::add_ABX, 4 },{ &cpu::ROR, &cpu::add_ABX, 7 },{ &cpu::NAN, &cpu::add_IMP, 7 },
		{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::STA, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::STY, &cpu::add_ZP0, 3 },{ &cpu::STA, &cpu::add_ZP0, 3 },{ &cpu::STX, &cpu::add_ZP0, 3 },{ &cpu::NAN, &cpu::add_IMP, 3 },{ &cpu::DEY, &cpu::add_IMP, 2 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::TXA, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::STY, &cpu::add_ABS, 4 },{ &cpu::STA, &cpu::add_ABS, 4 },{ &cpu::STX, &cpu::add_ABS, 4 },{ &cpu::NAN, &cpu::add_IMP, 4 },
		{ &cpu::BCC, &cpu::add_REL, 2 },{ &cpu::STA, &cpu::add_INDi, 6 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::STY, &cpu::add_ZPX, 4 },{ &cpu::STA, &cpu::add_ZPX, 4 },{ &cpu::STX, &cpu::add_ZPY, 4 },{ &cpu::NAN, &cpu::add_IMP, 4 },{ &cpu::TYA, &cpu::add_IMP, 2 },{ &cpu::STA, &cpu::add_ABY, 5 },{ &cpu::TXS, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::NOP, &cpu::add_IMP, 5 },{ &cpu::STA, &cpu::add_ABX, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },
		{ &cpu::LDY, &cpu::add_IMM, 2 },{ &cpu::LDA, &cpu::add_iIND, 6 },{ &cpu::LDX, &cpu::add_IMM, 2 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::LDY, &cpu::add_ZP0, 3 },{ &cpu::LDA, &cpu::add_ZP0, 3 },{ &cpu::LDX, &cpu::add_ZP0, 3 },{ &cpu::NAN, &cpu::add_IMP, 3 },{ &cpu::TAY, &cpu::add_IMP, 2 },{ &cpu::LDA, &cpu::add_IMM, 2 },{ &cpu::TAX, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::LDY, &cpu::add_ABS, 4 },{ &cpu::LDA, &cpu::add_ABS, 4 },{ &cpu::LDX, &cpu::add_ABS, 4 },{ &cpu::NAN, &cpu::add_IMP, 4 },
		{ &cpu::BCS, &cpu::add_REL, 2 },{ &cpu::LDA, &cpu::add_INDi, 5 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::LDY, &cpu::add_ZPX, 4 },{ &cpu::LDA, &cpu::add_ZPX, 4 },{ &cpu::LDX, &cpu::add_ZPY, 4 },{ &cpu::NAN, &cpu::add_IMP, 4 },{ &cpu::CLV, &cpu::add_IMP, 2 },{ &cpu::LDA, &cpu::add_ABY, 4 },{ &cpu::TSX, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 4 },{ &cpu::LDY, &cpu::add_ABX, 4 },{ &cpu::LDA, &cpu::add_ABX, 4 },{ &cpu::LDX, &cpu::add_ABY, 4 },{ &cpu::NAN, &cpu::add_IMP, 4 },
		{ &cpu::CPY, &cpu::add_IMM, 2 },{ &cpu::CMP, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::CPY, &cpu::add_ZP0, 3 },{ &cpu::CMP, &cpu::add_ZP0, 3 },{ &cpu::DEC, &cpu::add_ZP0, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::INY, &cpu::add_IMP, 2 },{ &cpu::CMP, &cpu::add_IMM, 2 },{ &cpu::DEX, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::CPY, &cpu::add_ABS, 4 },{ &cpu::CMP, &cpu::add_ABS, 4 },{ &cpu::DEC, &cpu::add_ABS, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },
		{ &cpu::BNE, &cpu::add_REL, 2 },{ &cpu::CMP, &cpu::add_INDi, 5 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::CMP, &cpu::add_ZPX, 4 },{ &cpu::DEC, &cpu::add_ZPX, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::CLD, &cpu::add_IMP, 2 },{ &cpu::CMP, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 7 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::CMP, &cpu::add_ABX, 4 },{ &cpu::DEC, &cpu::add_ABX, 7 },{ &cpu::NAN, &cpu::add_IMP, 7 },
		{ &cpu::CPX, &cpu::add_IMM, 2 },{ &cpu::SBC, &cpu::add_iIND, 6 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::CPX, &cpu::add_ZP0, 3 },{ &cpu::SBC, &cpu::add_ZP0, 3 },{ &cpu::INC, &cpu::add_ZP0, 5 },{ &cpu::NAN, &cpu::add_IMP, 5 },{ &cpu::INX, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_IMM, 2 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_IMP, 2 },{ &cpu::CPX, &cpu::add_ABS, 4 },{ &cpu::SBC, &cpu::add_ABS, 4 },{ &cpu::INC, &cpu::add_ABS, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },
		{ &cpu::BEQ, &cpu::add_REL, 2 },{ &cpu::SBC, &cpu::add_INDi, 5 },{ &cpu::NAN, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 8 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::SBC, &cpu::add_ZPX, 4 },{ &cpu::INC, &cpu::add_ZPX, 6 },{ &cpu::NAN, &cpu::add_IMP, 6 },{ &cpu::SED, &cpu::add_IMP, 2 },{ &cpu::SBC, &cpu::add_ABY, 4 },{ &cpu::NOP, &cpu::add_IMP, 2 },{ &cpu::NAN, &cpu::add_IMP, 7 },{ &cpu::NOP, &cpu::add_IMP, 4 },{ &cpu::SBC, &cpu::add_ABX, 4 },{ &cpu::INC, &cpu::add_ABX, 7 },{ &cpu::NAN, &cpu::add_IMP, 7 },


};

// int main(){

//     cpu my_6502;

//     return 0;
// }