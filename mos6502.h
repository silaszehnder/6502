#include <vector>
#include <string>
#include <stdint.h>
#include <stdio.h>

class mos6502 {
public:
    mos6502();
private:
    /**** REGISTERS ****/

    // PSR
    union PSR {
        struct {
            char N:1;
            char V:1;
            char unused:1;
            char B:1;
            char D:1;
            char I:1;
            char Z:1;
            char C:1;
        };
        char reg;
    };

    // Accumulator
    union A {
        struct {
            // TODO 
        };
        char reg;
    };

    // Index register Y
    union Y {
        struct {
            // TODO
        };
        char reg;
    };

    // Index register X
    union X {
        struct {
            // TODO 
        };
        char reg;
    };

    // Program counter
    union PC {
        struct {
            char PCH:8;
            char PCL:8;
        };
        uint16_t reg;
    };

    // Stack pointer
    union SPR {
        struct {
            char unused:2;
            char val:8;
        };
        uint16_t reg;
    };

    // TODO: I/O registers

    struct INSTR {
        std::string name;
        uint8_t (mos6502::*op)(void) = nullptr;    
        uint8_t (mos6502::*addr)(void) = nullptr;    
        uint8_t cycles;
    };

    // Opcode Addressing Modes
    uint8_t IMM();
    uint8_t ZP();
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t ABS();
    uint8_t ABSX();
    uint8_t ABSY();
    uint8_t ABSZ();
    uint8_t INDX();
    uint8_t INDY();
    uint8_t ACC();

    // Opcodes
    uint8_t op_noop();

    uint8_t op_adc(); uint8_t op_and(); uint8_t op_asl(); uint8_t op_bcc(); uint8_t op_bcs(); uint8_t op_beq(); uint8_t op_bit();
    uint8_t op_bmi(); uint8_t op_bne(); uint8_t op_bpl(); uint8_t op_brk(); uint8_t op_bvc(); uint8_t op_bvs(); uint8_t op_clc();
    uint8_t op_cld(); uint8_t op_cli(); uint8_t op_clv(); uint8_t op_cmp(); uint8_t op_cpx(); uint8_t op_cpy(); uint8_t op_dec();
    uint8_t op_dex(); uint8_t op_dey(); uint8_t op_eor(); uint8_t op_inc(); uint8_t op_inx(); uint8_t op_iny(); uint8_t op_jmp();
    uint8_t op_jsr(); uint8_t op_lda(); uint8_t op_ldx(); uint8_t op_ldy(); uint8_t op_lsr(); uint8_t op_nop(); uint8_t op_ora();
    uint8_t op_pha(); uint8_t op_php(); uint8_t op_pla(); uint8_t op_plp(); uint8_t op_rol(); uint8_t op_ror(); uint8_t op_rti();
    uint8_t op_rts(); uint8_t op_sbc(); uint8_t op_sec(); uint8_t op_sed(); uint8_t op_sei(); uint8_t op_sta(); uint8_t op_stx();
    uint8_t op_sty(); uint8_t op_tax(); uint8_t op_tay(); uint8_t op_tya(); uint8_t op_tsx(); uint8_t op_txa(); uint8_t op_txs();

    using m = mos6502;
    INSTR ops [256] = {
        {"brk", &m::op_brk, nullptr}, {"ora", &m::op_ora, &m::INDX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"ora", &m::op_ora, &m::ZP},
        {"asl", &m::op_asl, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"php", &m::op_php, nullptr}, {"ora", &m::op_ora, &m::IMM},
        {"asl", &m::op_asl, &m::ACC}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"ora", &m::op_ora, &m::ABS},
        {"asl", &m::op_asl, &m::ABS, {"future", &m::op_noop, nullptr},
        {"bpl", &m::op_bpl, nullptr}, {"ora", &m::op_ora, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"ora", &m::op_ora, &m::ZPX},
        {"asl", &m::op_asl, &m::ZPX}, {"future", &m::op_noop, nullptr},
        {"clc", &m::op_clc, nullptr}, {"ora", &m::op_ora, &m::ABSY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"ora", &m::op_ora, &m::ABSX},
        {"asl", &m::op_asl, &m::ABSX}, {"future", &m::op_noop, nullptr},
        {"jsr", &m::op_jsr, nullptr}, {"and", &m::op_and, &m::INDX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"bit", &m::op_bit, &m::ZP}, {"and", &m::op_and, &m::ZP},
        {"rol", &m::op_rol, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"plp", &m::op_plp, nullptr}, {"and", &m::op_and, &m::IMM},
        {"rol", &m::op_rol, &m::ACC}, {"future", &m::op_noop, nullptr},
        {"bit", &m::op_bit, &m::ABS}, {"and", &m::op_and, &m::ABS},
        {"rol", &m::op_rol, &m::ABS}, {"future", &m::op_noop, nullptr},
        {"bmi", &m::op_bmi, nullptr}, {"and", &m::op_and, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"and", &m::op_and, &m::ZPX},
        {"rol", &m::op_rol, &m::ZPX}, {"future", &m::op_noop, nullptr},
        {"sec", &m::op_sec, nullptr}, {"and", &m::op_and, &m::ABSY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"and", &m::op_and, &m::ABSX},
        {"rol", &m::op_rol, &m::ABSX}, {"future", &m::op_noop, nullptr},
        {"rti", &m::op_rti, nullptr}, {"eor", &m::op_eor, &m::INDX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"eor", &m::op_eor, &m::ZP},
        {"lsr", &m::op_lsr, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"pha", &m::op_pha, nullptr}, {"eor", &m::op_eor, &m::IMM},
        {"lsr", &m::op_lsr, &m::ACC}, {"future", &m::op_noop, nullptr},
        {"jmp", &m::op_jmp, &m::ABS}, {"eor", &m::op_eor, &m::ABS},
        {"lsr", &m::op_lsr, &m::ABS}, {"future", &m::op_noop, nullptr},
        {"bvc", &m::op_bvc, nullptr}, {"eor", &m::op_eor, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"eor", &m::op_eor, &m::ZPX},
        {"lsr", &m::op_lsr, &m::ZPX}, {"future", &m::op_noop, nullptr},
        {"cli", &m::op_cli, nullptr}, {"eor", &m::op_eor, &m::ABSY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"eor", &m::op_eor, &m::ABSX},
        {"lsr", &m::op_lsr, &m::ABSX}, {"future", &m::op_noop, nullptr},
        {"cli", &m::op_cli, nullptr}, {"eor", &m::op_eor, &m::ABSY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"eor", &m::op_eor, &m::ABSX},
        {"lsr", &m::op_lsr, &m::ABSX}, {"future", &m::op_noop, nullptr},
        {"rts", &m::op_rts, nullptr}, {"adc", &m::op_adc, &m::INDX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"adc", &m::op_adc, &m::ZP},
        {"ror", &m::op_ror, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"pla", &m::op_pla, nullptr}, {"adc", &m::op_adc, &m::IMM},
        {"ror", &m::op_ror, &m::ACC}, {"future", &m::op_noop, nullptr},
        {"jmp", &m::op_jmp, &m::IND}, {"adc", &m::op_adc, &m::ABS},
        {"ror", &m::op_ror, &m::ABS}, {"future", &m::op_noop, nullptr},
        {"bvs", &m::op_bvs, nullptr}, {"adc", &m::op_adc, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"adc", &m::op_adc, &m::ZPX},
        {"ror", &m::op_ror, &m::ZPX}, {"future", &m::op_noop, nullptr},
        {"sei", &m::op_sei, nullptr}, {"adc", &m::op_adc, &m::ABSY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"adc", &m::op_adc, &m::ABSX},
        {"ror", &m::op_ror, &m::ABSX}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"sta", &m::op_sta, &m::INDX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"sty", &m::op_sty, &m::ZP}, {"sta", &m::op_sta, &m::ZP},
        {"stx", &m::op_stx, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"dey", &m::op_dey, nullptr}, {"future", &m::op_noop, nullptr},
        {"txa", &m::op_txa, nullptr}, {"future", &m::op_noop, nullptr},
        {"sty", &m::op_sty, &m::ABS}, {"sta", &m::op_sta, &m::ABS},
        {"stx", &m::op_stx, &m::ABS}, {"future", &m::op_noop, nullptr},
        {"bcc", &m::op_bcc, nullptr}, {"sta", &m::op_sta, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"sty", &m::op_sty, &m::ZPX}, {"sta", &m::op_sta, &m::ZPX},
        {"stx", &m::op_stx, &m::ZPY}, {"future", &m::op_noop, nullptr},
        {"tya", &m::op_tya, nullptr}, {"sta", &m::op_sta, &m::ABSY},
        {"txs", &m::op_txs, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"sta", &m::op_sta, &m::ABSX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"ldy", &m::op_ldy, &m::IMM}, {"lda", &m::op_lda, &m::INDX},
        {"ldx", &m::op_ldx, &m::IMM}, {"future", &m::op_noop, nullptr},
        {"ldy", &m::op_ldy, &m::ZP}, {"lda", &m::op_lda, &m::ZP},
        {"ldx", &m::op_ldx, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"tay", &m::op_tay, nullptr}, {"lda", &m::op_lda, &m::IMM},
        {"tax", &m::op_tax, nullptr}, {"future", &m::op_noop, nullptr},
        {"ldy", &m::op_ldy, &m::ABS}, {"lda", &m::op_lda, &m::ABS},
        {"ldx", &m::op_ldx, &m::ABS}, {"future", &m::op_noop, nullptr},
        {"bcs", &m::op_bcs, nullptr}, {"lda", &m::op_lda, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"ldy", &m::op_ldy, &m::ZPX}, {"lda", &m::op_lda, &m::ZPX},
        {"ldx", &m::op_ldx, &m::ZPY}, {"future", &m::op_noop, nullptr},
        {"clv", &m::op_clv, nullptr}, {"lda", &m::op_lda, &m::ABSY},
        {"tsx", &m::op_tsx, nullptr}, {"future", &m::op_noop, nullptr},
        {"ldy", &m::op_ldy, &m::ABSX}, {"lda", &m::op_lda, &m::ABSX},
        {"ldx", &m::op_ldx, &m::ABSY}, {"future", &m::op_noop, nullptr},
        {"cpy", &m::op_cpy, &m::IMM}, {"cmp", &m::op_cmp, &m::INDX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"cpy", &m::op_cpy, &m::ZP}, {"cmp", &m::op_cmp, &m::ZP},
        {"dec", &m::op_dec, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"iny", &m::op_iny, nullptr}, {"cmp", &m::op_cmp, &m::IMM},
        {"dex", &m::op_dex, nullptr}, {"future", &m::op_noop, nullptr},
        {"cpy", &m::op_cpy, &m::ABS}, {"cmp", &m::op_cmp, &m::ABS},
        {"dec", &m::op_dec, &m::ABS}, {"future", &m::op_noop, nullptr},
        {"bne", &m::op_bne, nullptr}, {"cmp", &m::op_cmp, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"cmp", &m::op_cmp, &m::ZPX},
        {"dec", &m::op_dec, &m::ZPX}, {"future", &m::op_noop, nullptr},
        {"cld", &m::op_cld, nullptr}, {"cmp", &m::op_cmp, &m::ABSY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"cmp", &m::op_cmp, &m::ABSX},
        {"dec", &m::op_dec, &m::ABSX}, {"future", &m::op_noop, nullptr},
        {"cpx", &m::op_cpx, &m::IMM}, {"sbc", &m::op_sbc, &m::INDX},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"cpx", &m::op_cpx, &m::ZP}, {"sbc", &m::op_sbc, &m::ZP},
        {"inc", &m::op_inc, &m::ZP}, {"future", &m::op_noop, nullptr},
        {"inx", &m::op_inx, nullptr}, {"sbc", &m::op_sbc, &m::IMM},
        {"nop", &m::op_nop, nullptr}, {"future", &m::op_noop, nullptr},
        {"cpx", &m::op_cpx, &m::ABS}, {"sbc", &m::op_sbc, &m::ABS},
        {"inc", &m::op_inc, &m::ABS}, {"future", &m::op_noop, nullptr},
        {"beq", &m::op_beq, nullptr}, {"sbc", &m::op_sbc, &m::INDY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"sbc", &m::op_sbc, &m::ZPX},
        {"inc", &m::op_inc, &m::ZPX}, {"future", &m::op_noop, nullptr},
        {"sed", &m::op_sed, nullptr}, {"sbc", &m::op_sbc, &m::ABSY},
        {"future", &m::op_noop, nullptr}, {"future", &m::op_noop, nullptr},
        {"future", &m::op_noop, nullptr}, {"sbc", &m::op_sbc, &m::ABSX},
        {"inc", &m::op_inc, &m::ABSX}, {"future", &m::op_noop, nullptr},
    };
};
