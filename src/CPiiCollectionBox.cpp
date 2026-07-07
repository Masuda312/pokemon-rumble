#include <CPiiCollectionBox.hpp>
extern s32 gMaxDefeated;

void CPiiCollectionBox::setCollectionState(u32 dexNo, u32 formNo, s32 collectionState, bool isShiny) {
    PiiCollectionEntries* entry = &m_entries[dexNo];

    if (entry->m_collectionType < collectionState) {
        entry->m_collectionType = collectionState;
    }

    if (collectionState == 3) {
        s32 iVar1 = formNo >> 0x1f;
        if (isShiny) {
            entry->m_collectedShiny |= 1 << iVar1;
        } else {
            entry->m_collectedNormal |= 1 << iVar1;
        }
    }
    if (collectionState == 2) {
        s32 newDefeatedCount = entry->m_defeated + 1;
        s32* tmp = &newDefeatedCount;
        
        if (9999999 < newDefeatedCount) {
            tmp = &gMaxDefeated;
        }

        entry->m_defeated = *tmp;
    }
}

s32 CPiiCollectionBox::getCollectionType(u32 dexNo) {
    return m_entries[dexNo].m_collectionType;
}

s32 CPiiCollectionBox::getCollectedNormal(u32 dexNo) {
    return m_entries[dexNo].m_collectedNormal;
}

s32 CPiiCollectionBox::getCollectedShiny(u32 dexNo) {
    return m_entries[dexNo].m_collectedShiny;
}

//void CPiiCollectionBox::setCollectionBRR(u32 dexNo, s32 mode, s32 brRank) {
//    if (brRank == m_entries[dexNo].m_normalRank + mode) {
//        return;
//    }
//
//    m_entries[dexNo].m_normalRank + mode = brRank;
//}