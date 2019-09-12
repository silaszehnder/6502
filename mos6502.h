#include <vector>
#include <stdint.h>
#include <stdio.h>

class mos6502 {
public:
    mos6502();
private:
    /**** CONSTANTS ****/

    // Opcode Addressing Modes
    enum class Group1 {IMM, ZP, ZPX, ABS, ABSX, ABSY, IDXIND, INDIDX};
    enum class Group2 {ZP, ZPX, ABS, ABSZ, ACC};
    enum class Group3 {ZP, ABS, ZPX, IMM};

    /**** REGISTERS ****/
    // PSR
    union {
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
    }PSR;

    // Accumulator
    union {
        struct {
            // TODO 
        };
        char reg;
    }A;

    // Index register Y
    union {
        struct {
            // TODO
        };
        char reg;
    }Y;

    // Index register X
    union {
        struct {
            // TODO 
        };
        char reg;
    }X;

    // Program counter
    union {
        struct {
            char PCH:8;
            char PCL:8;
        };
        uint16_t reg;
    }PC;

    // Stack pointer
    union {
        struct {
            char unused:2;
            char val:8;
        };
        uint16_t reg;
    }SPR;

    // TODO: I/O registers

    /**** OPCODES ****/
    void op_noop();

    void op_adc();
    void op_and();
    void op_asl();
    void op_bcc();
    void op_bcs();
    void op_beq();
    void op_bit();
    void op_bmi();
    void op_bne();
    void op_bpl();
    void op_brk();
    void op_bvc();
    void op_bvs();
    void op_clc();
    void op_cld();
    void op_cli();
    void op_clv();
    void op_cmp();
    void op_cpx();
    void op_cpy();
    void op_dec();
    void op_dex();
    void op_dey();
    void op_eor();
    void op_inc();
    void op_inx();
    void op_iny();
    void op_jmp();
    void op_jsr();
    void op_lda();
    void op_ldx();
    void op_ldy();
    void op_lsr();
    void op_nop();
    void op_ora();
    void op_pha();
    void op_php();
    void op_pla();
    void op_plp();
    void op_rol();
    void op_ror();
    void op_rti();
    void op_rts();
    void op_sbc();
    void op_sec();
    void op_sed();
    void op_sei();
    void op_sta();
    void op_stx();
    void op_sty();
    void op_tax();
    void op_tay();
    void op_tya();
    void op_tsx();
    void op_txa();
    void op_txs();
    //enum class Group1 {IMM, ZP, ZPX, ABS, ABSX, ABSY, IDXIND, INDIDX};
    //enum class Group2 {ZP, ZPX, ABS, ABSZ, ACC};
    //enum class Group3 {ZP, ABS, ZPX, IMM};

    void (mos6502::*ops[256])() {
        &mos6502::op_brk,
        &mos6502::op_ora,           // (Indirect, X)
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_ora,           // Zero Page
        &mos6502::op_asl,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_php,
        &mos6502::op_ora,           // Immediate
        &mos6502::op_asl,           // Accumulator
        &mos6502::op_noop,
        &mos6502::op_bpl,           //
        &mos6502::op_ora,           // (Indirect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_ora,           // Zero Page, X
        &mos6502::op_asl,           // Zero Page, X
        &mos6502::op_noop,
        &mos6502::op_clc,
        &mos6502::op_ora,           // Absolute, Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_ora,           // Absolute, X
        &mos6502::op_asl,           // Absolute, X
        &mos6502::op_noop,
        &mos6502::op_jsr,
        &mos6502::op_and,           // (Indirect, X)
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_bit,           // Zero Page
        &mos6502::op_and,           // Zero Page
        &mos6502::op_rol,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_plp,
        &mos6502::op_and,           // Immediate
        &mos6502::op_rol,           // Accumulator
        &mos6502::op_noop,
        &mos6502::op_bit,           // Absolute
        &mos6502::op_and,           // Absolute
        &mos6502::op_rol,           // Absolute
        &mos6502::op_noop,
        &mos6502::op_bmi,
        &mos6502::op_and,           // (Indirect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_and,           // Zero Page, X
        &mos6502::op_rol,           // Zero Page, X
        &mos6502::op_noop,
        &mos6502::op_sec,
        &mos6502::op_and,           // Absolute, Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_and,           // Absolute, X
        &mos6502::op_rol,           // Absolute, X
        &mos6502::op_noop,
        &mos6502::op_rti,
        &mos6502::op_eor,           // (Indirect, X)
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_eor,           // Zero Page
        &mos6502::op_lsr,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_pha,
        &mos6502::op_eor,           // Immediate
        &mos6502::op_lsr,           // Accumulator
        &mos6502::op_noop,
        &mos6502::op_jmp,           // Absolute
        &mos6502::op_eor,           // Absolute
        &mos6502::op_lsr,           // Absolute
        &mos6502::op_noop,
        &mos6502::op_bvc,
        &mos6502::op_eor,           // (Indirect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_eor,           // Zero Page, X
        &mos6502::op_lsr,           // Zero Page, X
        &mos6502::op_noop,
        &mos6502::op_cli,
        &mos6502::op_eor,           // Absolute, Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_eor,           // Absolute, X
        &mos6502::op_lsr,           // Absolute, X
        &mos6502::op_noop,
        &mos6502::op_rts,
        &mos6502::op_adc,           // (Indirect, X)
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_adc,           // Zero Page
        &mos6502::op_ror,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_pla,
        &mos6502::op_adc,           // Immediate
        &mos6502::op_ror,           // Accumulator
        &mos6502::op_noop,
        &mos6502::op_jmp,           // Indirect
        &mos6502::op_adc,           // Absolute
        &mos6502::op_ror,           // Absolute
        &mos6502::op_noop,
        &mos6502::op_bvs,
        &mos6502::op_adc,           // (Indirect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_adc,           // Zero Page, X
        &mos6502::op_ror,           // Zero Page, X
        &mos6502::op_noop,
        &mos6502::op_sei,
        &mos6502::op_adc,           // Absolute, Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_adc,           // Absolute, X
        &mos6502::op_ror,           // Absolute, X
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_sta,           // (Indirect, X)
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_sty,           // Zero Page
        &mos6502::op_sta,           // Zero Page
        &mos6502::op_stx,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_dey,
        &mos6502::op_noop,
        &mos6502::op_txa,
        &mos6502::op_noop,
        &mos6502::op_sty,           // Absolute
        &mos6502::op_sta,           // Absolute
        &mos6502::op_stx,           // Absolute
        &mos6502::op_noop,
        &mos6502::op_bcc,
        &mos6502::op_sta,           // (Indirect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_sty,           // Zero Page, X
        &mos6502::op_sta,           // Zero Page, X
        &mos6502::op_stx,           // Zero Page, Y
        &mos6502::op_noop,
        &mos6502::op_tya,
        &mos6502::op_sta,           // Absolute, Y
        &mos6502::op_txs,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_sta,           // Absolute, X
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_ldy,           // Immediate
        &mos6502::op_lda,           // (Indirect, X)
        &mos6502::op_ldx,           // Immediate
        &mos6502::op_noop,
        &mos6502::op_ldy,           // Zero Page
        &mos6502::op_lda,           // Zero Page
        &mos6502::op_ldx,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_tay,
        &mos6502::op_lda,           // Immediate
        &mos6502::op_tax,
        &mos6502::op_noop,
        &mos6502::op_ldy,           // Absolute
        &mos6502::op_lda,           // Absolute
        &mos6502::op_ldx,           // Absolute
        &mos6502::op_noop,
        &mos6502::op_bcs,
        &mos6502::op_lda,           // (Indirect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_ldy,           // Zero Page, X
        &mos6502::op_lda,           // Zero Page, X
        &mos6502::op_ldx,           // Zero Page, Y
        &mos6502::op_noop,
        &mos6502::op_clv,
        &mos6502::op_lda,           // Absolute, Y
        &mos6502::op_tsx,
        &mos6502::op_noop,
        &mos6502::op_ldy,           // Absolute, X
        &mos6502::op_lda,           // Absolute, X
        &mos6502::op_ldx,           // Absolute, Y
        &mos6502::op_noop,
        &mos6502::op_cpy,           // Immediate
        &mos6502::op_cmp,           // (Indirect, X)
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_cpy,           // Zero Page
        &mos6502::op_cmp,           // Zero Page
        &mos6502::op_dec,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_iny,
        &mos6502::op_cmp,           // Immediate
        &mos6502::op_dex,
        &mos6502::op_noop,
        &mos6502::op_cpy,           // Absolute
        &mos6502::op_cmp,           // Absolute
        &mos6502::op_dec,           // Absolute
        &mos6502::op_noop,
        &mos6502::op_bne,
        &mos6502::op_cmp,           // (Indrect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_cmp,           // Zero Page, X
        &mos6502::op_dec,           // Zero Page, X
        &mos6502::op_noop,
        &mos6502::op_cld,
        &mos6502::op_cmp,           // Absolute, Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_cmp,           // Absolute, X
        &mos6502::op_dec,           // Absolute, X
        &mos6502::op_noop,
        &mos6502::op_cpx,           // Immediate
        &mos6502::op_sbc,           // (Indirect, X)
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_cpx,           // Zero Page
        &mos6502::op_sbc,           // Zero Page
        &mos6502::op_inc,           // Zero Page
        &mos6502::op_noop,
        &mos6502::op_inx,
        &mos6502::op_sbc,           // Immediate
        &mos6502::op_nop,
        &mos6502::op_noop,
        &mos6502::op_cpx,           // Absolute
        &mos6502::op_sbc,           // Absolute
        &mos6502::op_inc,           // Absolute
        &mos6502::op_noop,
        &mos6502::op_beq,
        &mos6502::op_sbc,           // (Indirect), Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_sbc,           // Zero Page, X
        &mos6502::op_inc,           // Zero Page, X
        &mos6502::op_noop,
        &mos6502::op_sed,
        &mos6502::op_sbc,           // Absolute, Y
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_noop,
        &mos6502::op_sbc,           // Absolute, X
        &mos6502::op_inc,           // Absolute, X
        &mos6502::op_noop
    };
};
