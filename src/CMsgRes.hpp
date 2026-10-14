#pragma once

#include <types.h>

/*
    MESGbmg header:
        0x0 = magic "MESGbmg1"
        0x8 = size
        0xC = sectionCount
        0x10 = encoding
        0x11 = padding
*/

class CMsgRes {
public:
    u8* m_bmgData;
    u8* m_inf1;
    u8* m_bmgFile;
    u8* m_dat1;
    u8* m_str1;

    CMsgRes(u8* bmgFile, bool unk);
    ~CMsgRes();

    void initBmgFileSections();
    void unescapeStringUTF8();
    void unescapeStringUTF16();
    u32 getFileID();
    const wchar_t* getString(s32 index);
};