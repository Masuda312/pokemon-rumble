#include <types.h>
#include <vector>
#include <SlotData.hpp>

class SaveData {
public:
    u8 m_currentSlot;
    std::vector<SlotData> m_slotData;
};

SlotData* getSaveSlotData(s32 slot);