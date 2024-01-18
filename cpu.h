#include <cstdint>
#include <array>

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

// increments nd decrements
    void INC(); void INX(); void INY();
    void DEC(); void DEX(); void DEY();

// Shifts
    void ASL(); void LSR(); void ROL(); void ROR();

// Branches 
    void BCC(); void BCS(); void BEQ(); void BMI();
    void BNE(); void BPL(); void BVC(); void BVS();

//Status flag change
    void CLC(); void CLD(); void CLI();
    void CLV(); void SEC(); void SED(); void SEI();

// system changes
    void BRK(); void NOP(); void RTI();


public: // ADDRESSING MODES
    void add_IMP(); // implicit addressing mode
    void add_ACC(); // accumulator addressing mode
    void add_ZP(); // zero page addressing mode
    void add_ZPX(); // zero page,X addressing mode
    void add_ZPX(); // zero page, Y addressing mode
    void add_REL(); // relative addressing mode
    void add_ABS(); // absolute addressing mode
    void add_ABSX(); // absolute addressing mode x
    void add_ABSY(); // absolute addressing mode y
    void add_IND(); // indirect addressing mode
    void add_iIND(); //indexed indirect addressing mode
    void add_INDi(); // indirect indexed addressing mode
    


};


// int main(){

//     cpu my_6502;

//     return 0;
// }