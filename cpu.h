#include <cstdint>
#include <array>
#include <vector>

class cpu
{
public:
    cpu();
    ~cpu();

public:

    uint8_t data_bus = 0x00;
    uint16_t address_bus = 0x0000;

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

public:
    struct instruction
    {
        void (cpu::*add_mode_ptr)();
        void (cpu::*operation_ptr)();
        uint8_t cycles;                                     
    };

private:
    std::array<uint8_t, 64 * 1024> memory;
    std::vector<instruction> ins_table;



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

// Jumps and calls 
    void JMP(); void JSR(); void RTS();

// Branches 
    void BCC(); void BCS(); void BEQ(); void BMI();
    void BNE(); void BPL(); void BVC(); void BVS();

//Status flag changes
    void CLC(); void CLD(); void CLI();
    void CLV(); void SEC(); void SED(); void SEI();

// system changes
    void BRK(); void RTI();

//illegal opcodes capture function 
    void NOP(); void JAM(); void SLO(); void RLA(); 
    void SRE(); void RRA(); void SAX(); void SHA();
    void LAX(); void DCP(); void ISC(); void ANC();
    void ALR(); void ARR(); void ANE(); void TAS();
    void LXA(); void LAS(); void SBX(); void SHY();
    void SHX(); 

public: // ADDRESSING MODES
    void add_IMP(); // implicit addressing mode
    void add_IMM(); // immediate addressing mode
    void add_ACC(); // accumulator addressing mode XXX
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

public: //Helper functions
    void flash_mem(std::initializer_list<uint8_t> val); //helper function for flashing memory
    void flash_mem_at_loc(uint8_t val, uint16_t loc); //helper function for flashing mem at specific location
    void print_mem(uint8_t upto_add) const; //Helper function for printing memory
    instruction fetch_ins(); //Helper function to fetch instructions
    void exe_ins(void (cpu::*addModeType)(), void (cpu::*operation)(), uint8_t cycles);

public: //helper variables
    uint8_t temp_add;
};

