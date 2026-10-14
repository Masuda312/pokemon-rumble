#pragma once

#include <types.h>
#include <vector>

class CPiiCollectionBox {
public:
    enum CollectionTypes {
        UNKNOWN,
        DEFEATED,
        GOT,
    };
    struct PiiCollectionEntries {
        s32 collectionType;
        s32 normalRank;
        s32 advancedRank;
        s32 exRank;
        s32 defeatCount;
        s32 collectedNormal;
        s32 collectedShiny;
    };
    static_assert(sizeof(PiiCollectionEntries) == 0x1C);

public:
    std::vector<PiiCollectionEntries> m_entries;
    std::vector<PiiCollectionEntries> m_savedEntries;

    void setCollectionType(s32 dexNo, s32 formNo, s32 collectionState, bool isShiny);
    s32 getCollectionType(u32 dexNo);
    PiiCollectionEntries* getPiiCollectionEntries(u32 dexNo);
    s32 getCollectedNormal(u32 dexNo);
    s32 getCollectedShiny(u32 dexNo);
    void setCollectionBRR(u32 dexNo, s32 mode, s32 brRank);
    s32 getCollectionBRR(u32 dexNo, s32 mode);
    s32 getDefeatCount(u32 dexNo);
};