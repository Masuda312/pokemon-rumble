#pragma once

#include "types.h"

struct SD_PpdData {
    union {
        u16 packedMonsNoFormNo;
        struct {
            u16 monsNo : 9;
            u16 formNo : 5;
            u16 sex : 2;
        };  
    };
    u16 moveIds[2];
    u16 level;
    u16 lo_bonusMaxHP;
    u16 lo_bonusAttackPower;
    u16 lo_bonusDefencePower;
    u16 lo_bonusSpeed;
    u16 trait;
    u16 flags;
    u32 piiId;
    u16 hi_bonusMaxHP;
    u16 hi_bonusAttackPower;
    u16 hi_bonusDefencePower;
    u16 hi_bonusSpeed;
    u64 time;
    u32 trainerId;
};

class SD_PiiPersonalData {
public:
    virtual void fn_800BADD0();
    virtual void fn_800BADC0();
    virtual void fn_800BADB0();
    virtual void fn_800BADE0();
    virtual void fn_800BADA0();
    virtual void fn_800BAD90();
    virtual void fn_800BAD80();
    virtual void fn_800BAD70();

    SD_PpdData m_sdPpdData;
};