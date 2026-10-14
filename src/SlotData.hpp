#pragma once

#include <types.h>
#include <SD_PiiPersonalData.hpp>
#include <vector>

class SlotData {
public:
    char pad[0x12D8];
    s32 m_totalDefeated; // 0x12D8
    s32 m_totalBefriended; // 0x12DC

    std::vector<SD_PiiPersonalData> m_sdPpd; // 0x1308
};