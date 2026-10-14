#include <CPiiCollectionBox.hpp>
static const s32 gMaxDefeated = 0x98967f;

void CPiiCollectionBox::setCollectionType(s32 dexNo, s32 formNo, s32 collectionState, bool isShiny) {
    PiiCollectionEntries* entry = &m_entries[dexNo];

    if (entry->collectionType < collectionState) {
        entry->collectionType = collectionState;
    }

    if (collectionState == 3) {
        if (isShiny) {
            entry->collectedShiny |= 1 << (formNo % 32);
        } else {
            entry->collectedNormal |= 1 << (formNo % 32);
        }
    }
    if (collectionState == 2) {
        s32 newDefeatCount = entry->defeatCount + 1;

        const s32* result = 9999999 < newDefeatCount ? &gMaxDefeated : &newDefeatCount;

        entry->defeatCount = *result;
    }
}

s32 CPiiCollectionBox::getCollectionType(u32 dexNo) {
    return m_entries[dexNo].collectionType;
}

CPiiCollectionBox::PiiCollectionEntries* CPiiCollectionBox::getPiiCollectionEntries(u32 dexNo) {
    return &m_entries[dexNo];
}

s32 CPiiCollectionBox::getCollectedNormal(u32 dexNo) {
    return m_entries[dexNo].collectedNormal;
}

s32 CPiiCollectionBox::getCollectedShiny(u32 dexNo) {
    return m_entries[dexNo].collectedShiny;
}

void CPiiCollectionBox::setCollectionBRR(u32 dexNo, s32 mode, s32 brRank) {
    s32* rank = &m_entries[dexNo].normalRank + mode;

    if (*rank >= brRank) {
        return;
    }

    *rank = brRank;
}

s32 CPiiCollectionBox::getCollectionBRR(u32 dexNo, s32 mode) {
    s32* rank = &m_entries[dexNo].normalRank + mode;
    return *rank;
}

s32 CPiiCollectionBox::getDefeatCount(u32 dexNo) {
    return m_entries[dexNo].defeatCount;
}