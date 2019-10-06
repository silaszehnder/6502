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

    // 64K of addressable memory
    uint8_t mem[64 * 1024];

    // Opcode Addressing Modes
    uint8_t IMM();
    uint8_t ZP();
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t ABS();
    uint8_t ABSX();
    uint8_t ABSY();
    uint8_t ABSZ();
    uint8_t IND();
    uint8_t INDX();
    uint8_t INDY();
    uint8_t ACC();

    // Opcodes
    // Future opcodes
    uint8_t op_noop();

    // Impl upcodes
    uint8_t op_adc(); uint8_t op_and(); uint8_t op_asl(); uint8_t op_bcc();
    uint8_t op_bcs(); uint8_t op_beq(); uint8_t op_bit(); uint8_t op_bmi();
    uint8_t op_bne(); uint8_t op_bpl(); uint8_t op_brk(); uint8_t op_bvc();
    uint8_t op_bvs(); uint8_t op_clc(); uint8_t op_cld(); uint8_t op_cli();
    uint8_t op_clv(); uint8_t op_cmp(); uint8_t op_cpx(); uint8_t op_cpy();
    uint8_t op_dec(); uint8_t op_dex(); uint8_t op_dey(); uint8_t op_eor();
    uint8_t op_inc(); uint8_t op_inx(); uint8_t op_iny(); uint8_t op_jmp();
    uint8_t op_jsr(); uint8_t op_lda(); uint8_t op_ldx(); uint8_t op_ldy();
    uint8_t op_lsr(); uint8_t op_nop(); uint8_t op_ora(); uint8_t op_pha();
    uint8_t op_php(); uint8_t op_pla(); uint8_t op_plp(); uint8_t op_rol();
    uint8_t op_ror(); uint8_t op_rti(); uint8_t op_rts(); uint8_t op_sbc();
    uint8_t op_sec(); uint8_t op_sed(); uint8_t op_sei(); uint8_t op_sta();
    uint8_t op_stx(); uint8_t op_sty(); uint8_t op_tax(); uint8_t op_tay();
    uint8_t op_tya(); uint8_t op_tsx(); uint8_t op_txa(); uint8_t op_txs();

    using m = mos6502;
    INSTR ops [256] = {
        {"brk", &m::op_brk, nullptr,0}, {"ora", &m::op_ora, &m::INDX,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"ora", &m::op_ora, &m::ZP,3},
        {"asl", &m::op_asl, &m::ZP,5}, {"future", &m::op_noop, nullptr,0},
        {"php", &m::op_php, nullptr,3}, {"ora", &m::op_ora, &m::IMM,2},
        {"asl", &m::op_asl, &m::ACC,2}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"ora", &m::op_ora, &m::ABS,4},
        {"asl", &m::op_asl, &m::ABS,6}, {"future", &m::op_noop, nullptr,0},
        {"bpl", &m::op_bpl, nullptr,2}, {"ora", &m::op_ora, &m::INDY,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"ora", &m::op_ora, &m::ZPX,4},
        {"asl", &m::op_asl, &m::ZPX,6}, {"future", &m::op_noop, nullptr,0},
        {"clc", &m::op_clc, nullptr,2}, {"ora", &m::op_ora, &m::ABSY,4},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"ora", &m::op_ora, &m::ABSX,4},
        {"asl", &m::op_asl, &m::ABSX,7}, {"future", &m::op_noop, nullptr,0},
        {"jsr", &m::op_jsr, nullptr,6}, {"and", &m::op_and, &m::INDX,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"bit", &m::op_bit, &m::ZP,3}, {"and", &m::op_and, &m::ZP,3},
        {"rol", &m::op_rol, &m::ZP,5}, {"future", &m::op_noop, nullptr,0},
        {"plp", &m::op_plp, nullptr,4}, {"and", &m::op_and, &m::IMM,2},
        {"rol", &m::op_rol, &m::ACC,2}, {"future", &m::op_noop, nullptr,0},
        {"bit", &m::op_bit, &m::ABS,4}, {"and", &m::op_and, &m::ABS,4},
        {"rol", &m::op_rol, &m::ABS,6}, {"future", &m::op_noop, nullptr,0},
        {"bmi", &m::op_bmi, nullptr,2}, {"and", &m::op_and, &m::INDY,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"and", &m::op_and, &m::ZPX,4},
        {"rol", &m::op_rol, &m::ZPX,6}, {"future", &m::op_noop, nullptr,0},
        {"sec", &m::op_sec, nullptr,2}, {"and", &m::op_and, &m::ABSY,4},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"and", &m::op_and, &m::ABSX,4},
        {"rol", &m::op_rol, &m::ABSX,7}, {"future", &m::op_noop, nullptr,0},
        {"rti", &m::op_rti, nullptr,6}, {"eor", &m::op_eor, &m::INDX,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"eor", &m::op_eor, &m::ZP,3},
        {"lsr", &m::op_lsr, &m::ZP,5}, {"future", &m::op_noop, nullptr,0},
        {"pha", &m::op_pha, nullptr,3}, {"eor", &m::op_eor, &m::IMM,2},
        {"lsr", &m::op_lsr, &m::ACC,2}, {"future", &m::op_noop, nullptr,0},
        {"jmp", &m::op_jmp, &m::ABS,3}, {"eor", &m::op_eor, &m::ABS,4},
        {"lsr", &m::op_lsr, &m::ABS,6}, {"future", &m::op_noop, nullptr,0},
        {"bvc", &m::op_bvc, nullptr,2}, {"eor", &m::op_eor, &m::INDY,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"eor", &m::op_eor, &m::ZPX,4},
        {"lsr", &m::op_lsr, &m::ZPX,6}, {"future", &m::op_noop, nullptr,0},
        {"cli", &m::op_cli, nullptr,2}, {"eor", &m::op_eor, &m::ABSY,4},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"eor", &m::op_eor, &m::ABSX,4},
        {"lsr", &m::op_lsr, &m::ABSX,7}, {"future", &m::op_noop, nullptr,0},
        {"rts", &m::op_rts, nullptr,6}, {"adc", &m::op_adc, &m::INDX,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"adc", &m::op_adc, &m::ZP,3},
        {"ror", &m::op_ror, &m::ZP,5}, {"future", &m::op_noop, nullptr,0},
        {"pla", &m::op_pla, nullptr,4}, {"adc", &m::op_adc, &m::IMM,2},
        {"ror", &m::op_ror, &m::ACC,2}, {"future", &m::op_noop, nullptr,0},
        {"jmp", &m::op_jmp, &m::IND,5}, {"adc", &m::op_adc, &m::ABS,4},
        {"ror", &m::op_ror, &m::ABS,6}, {"future", &m::op_noop, nullptr,0},
        {"bvs", &m::op_bvs, nullptr,2}, {"adc", &m::op_adc, &m::INDY,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"adc", &m::op_adc, &m::ZPX,4},
        {"ror", &m::op_ror, &m::ZPX,6}, {"future", &m::op_noop, nullptr,0},
        {"sei", &m::op_sei, nullptr,2}, {"adc", &m::op_adc, &m::ABSY,4},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"adc", &m::op_adc, &m::ABSX,4},
        {"ror", &m::op_ror, &m::ABSX,7}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"sta", &m::op_sta, &m::INDX,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"sty", &m::op_sty, &m::ZP,3}, {"sta", &m::op_sta, &m::ZP,3},
        {"stx", &m::op_stx, &m::ZP,3}, {"future", &m::op_noop, nullptr,0},
        {"dey", &m::op_dey, nullptr,2}, {"future", &m::op_noop, nullptr,0},
        {"txa", &m::op_txa, nullptr,2}, {"future", &m::op_noop, nullptr,0},
        {"sty", &m::op_sty, &m::ABS,4}, {"sta", &m::op_sta, &m::ABS,4},
        {"stx", &m::op_stx, &m::ABS,4}, {"future", &m::op_noop, nullptr,0},
        {"bcc", &m::op_bcc, nullptr,2}, {"sta", &m::op_sta, &m::INDY,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"sty", &m::op_sty, &m::ZPX,4}, {"sta", &m::op_sta, &m::ZPX,4},
        {"stx", &m::op_stx, &m::ZPY,4}, {"future", &m::op_noop, nullptr,0},
        {"tya", &m::op_tya, nullptr,2}, {"sta", &m::op_sta, &m::ABSY,5},
        {"txs", &m::op_txs, nullptr,2}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"sta", &m::op_sta, &m::ABSX,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"ldy", &m::op_ldy, &m::IMM,2}, {"lda", &m::op_lda, &m::INDX,6},
        {"ldx", &m::op_ldx, &m::IMM,2}, {"future", &m::op_noop, nullptr,0},
        {"ldy", &m::op_ldy, &m::ZP,3}, {"lda", &m::op_lda, &m::ZP,3},
        {"ldx", &m::op_ldx, &m::ZP,3}, {"future", &m::op_noop, nullptr,0},
        {"tay", &m::op_tay, nullptr,2}, {"lda", &m::op_lda, &m::IMM,2},
        {"tax", &m::op_tax, nullptr,2}, {"future", &m::op_noop, nullptr,0},
        {"ldy", &m::op_ldy, &m::ABS,4}, {"lda", &m::op_lda, &m::ABS,4},
        {"ldx", &m::op_ldx, &m::ABS,4}, {"future", &m::op_noop, nullptr,0},
        {"bcs", &m::op_bcs, nullptr,2}, {"lda", &m::op_lda, &m::INDY,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"ldy", &m::op_ldy, &m::ZPX,4}, {"lda", &m::op_lda, &m::ZPX,4},
        {"ldx", &m::op_ldx, &m::ZPY,4}, {"future", &m::op_noop, nullptr,0},
        {"clv", &m::op_clv, nullptr,2}, {"lda", &m::op_lda, &m::ABSY,4},
        {"tsx", &m::op_tsx, nullptr,2}, {"future", &m::op_noop, nullptr,0},
        {"ldy", &m::op_ldy, &m::ABSX,4}, {"lda", &m::op_lda, &m::ABSX,4},
        {"ldx", &m::op_ldx, &m::ABSY,4}, {"future", &m::op_noop, nullptr,0},
        {"cpy", &m::op_cpy, &m::IMM,2}, {"cmp", &m::op_cmp, &m::INDX,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"cpy", &m::op_cpy, &m::ZP,3}, {"cmp", &m::op_cmp, &m::ZP,3},
        {"dec", &m::op_dec, &m::ZP,5}, {"future", &m::op_noop, nullptr,0},
        {"iny", &m::op_iny, nullptr,2}, {"cmp", &m::op_cmp, &m::IMM,2},
        {"dex", &m::op_dex, nullptr,2}, {"future", &m::op_noop, nullptr,0},
        {"cpy", &m::op_cpy, &m::ABS,4}, {"cmp", &m::op_cmp, &m::ABS,4},
        {"dec", &m::op_dec, &m::ABS,6}, {"future", &m::op_noop, nullptr,0},
        {"bne", &m::op_bne, nullptr,2}, {"cmp", &m::op_cmp, &m::INDY,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"cmp", &m::op_cmp, &m::ZPX,4},
        {"dec", &m::op_dec, &m::ZPX,6}, {"future", &m::op_noop, nullptr,0},
        {"cld", &m::op_cld, nullptr,2}, {"cmp", &m::op_cmp, &m::ABSY,4},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"cmp", &m::op_cmp, &m::ABSX,4},
        {"dec", &m::op_dec, &m::ABSX,7}, {"future", &m::op_noop, nullptr,0},
        {"cpx", &m::op_cpx, &m::IMM,2}, {"sbc", &m::op_sbc, &m::INDX,6},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"cpx", &m::op_cpx, &m::ZP,3}, {"sbc", &m::op_sbc, &m::ZP,3},
        {"inc", &m::op_inc, &m::ZP,5}, {"future", &m::op_noop, nullptr,0},
        {"inx", &m::op_inx, nullptr,2}, {"sbc", &m::op_sbc, &m::IMM,2},
        {"nop", &m::op_nop, nullptr,2}, {"future", &m::op_noop, nullptr,0},
        {"cpx", &m::op_cpx, &m::ABS,4}, {"sbc", &m::op_sbc, &m::ABS,4},
        {"inc", &m::op_inc, &m::ABS,6}, {"future", &m::op_noop, nullptr,0},
        {"beq", &m::op_beq, nullptr,2}, {"sbc", &m::op_sbc, &m::INDY,5},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"sbc", &m::op_sbc, &m::ZPX,4},
        {"inc", &m::op_inc, &m::ZPX,6}, {"future", &m::op_noop, nullptr,0},
        {"sed", &m::op_sed, nullptr,2}, {"sbc", &m::op_sbc, &m::ABSY,4},
        {"future", &m::op_noop, nullptr,0}, {"future", &m::op_noop, nullptr,0},
        {"future", &m::op_noop, nullptr,0}, {"sbc", &m::op_sbc, &m::ABSX,4},
        {"inc", &m::op_inc, &m::ABSX,7}, {"future", &m::op_noop, nullptr,0}
    };
};
