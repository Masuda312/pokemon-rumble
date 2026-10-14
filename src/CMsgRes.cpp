#include <CMsgRes.hpp>
#include <cstring>
#include <wctype.h>
#include <ctype.h>

CMsgRes::CMsgRes(u8* bmgFile, bool unk) {
    m_bmgData = 0;
    m_inf1 = 0;
    m_dat1 = 0;
    m_str1 = 0;
    m_bmgFile = bmgFile;
    initBmgFileSections();

    if (unk) {
        if (m_bmgData[0x10] == 2) {
            unescapeStringUTF16();
        }
        else {
            unescapeStringUTF8();
        }
    }
}

CMsgRes::~CMsgRes() {}

void CMsgRes::unescapeStringUTF8() {
    if (m_bmgData[0x10] != 2) {
        u8* dat = m_dat1; 
        s32 size = *(s32*)(dat + 0x4);
        u8* read = dat + 0x8;
        bool trail = false;
        u8* write = read;
        bool isSjis = (m_bmgData[0x10] == 3);

        while (read < dat + size) {
            if (trail) {
                trail = false;
                *write++ = *read++;
            } 
            else {
                char c = *read;

                if (c == '\\') {
                    c = read[1];
                    read += 2;

                    switch (c) {
                        case 'r':
                            *write++ = '\r';
                            break;
                        case 'f':
                            *write++ = '\f';
                            break;
                        case 'x': {
                            u32 val = 0;
                            char ch;

                            for (s32 i = 0; i < 2 && isxdigit(ch = (char)*read); i++) {
                                u32 digit;
                                if (isdigit(ch)) {
                                    digit = ch - '0';
                                }
                                else {
                                    digit = tolower(ch) - 'a' + 10;
                                }
                                val = (val << 4) | digit;
                                read++;
                            }

                            *write++ = (u8)val;
                            break;
                        }
                        default:
                            *write++ = c;
                            break;
                    }
                
                }
                else if (c == 0) {
                    trail = false;
                    *write = 0;
                    read++;
                    write = read;
                }
                else {
                    if (isSjis) {
                        trail = false;

                        if ((c > 0x80 && c < 0xA0) || (c > 0xDF && c < 0xFD)) { 
                            trail = true;
                        }
                    }

                    *write++ = *read++;
                }
            }
        }
    }
}

void CMsgRes::unescapeStringUTF16() {
    if (m_bmgData[0x10] == 2) {
        u8* dat = m_dat1;
        s32 size = *(s32*)(dat + 0x4);
        u16* read = (u16*)(dat + 0x8);
        u16* write;
        u16* end = (u16*)(dat + size);
        write = read;

        while (read < end) {
            u16 c = *read;

            if (c == L'\\') {
                c = read[1];
                read += 2;

                u32 val = 0;
                u32 ch;

                switch (c) {
                    case 'r':
                        *write++ = '\r';
                        break;
                    case 'f':
                        *write++ = '\f';
                        break;
                    case 'x':
                        val = 0;
                        
                        for (s32 i = 0; i < 2 && iswxdigit(ch = *read); i++) {
                            val = (val << 4) | (iswdigit(ch) ? ch - '0' : towlower(ch) - 'a' + 10);
                            read++;
                        }

                        *write++ = (u16)val;
                        break;
                    case 'u':
                        val = 0;

                        for (s32 i = 0; i < 4 && iswxdigit(ch = *read); i++) {
                            val = (val << 4) | (iswdigit(ch) ? ch - '0' : towlower(ch) - 'a' + 10);
                            read++;
                        }

                        *write
                        ++ = (u16)val;
                        break;
                    default:
                        *write++ = c;
                        break;
                }
            }
            else if (c == 0) {
                *write = 0;
                read++;
                write = read;
            }
            else {
                *write++ = c;
                read++;
            }
        }
    }
}

void CMsgRes::initBmgFileSections() {
    if (m_inf1) {
        return;
    }

    u8* section = m_bmgFile;

    if (section != 0) {
        m_bmgData = section;

        s32 remaining = *(s32*)(section + 0x8);
        section += 0x20;
        remaining -= 0x20;

        while (remaining > 0) {
            if (memcmp(section, "INF1" , 4) == 0) {
                m_inf1 = section;
            }
            else if (memcmp(section, "DAT1", 4) == 0) {
                m_dat1 = section;
            } 
            else if (memcmp(section, "STR1", 4) == 0) {
                m_str1 = section;
            }
            
      
            s32 offset = *(s32*)(section + 0x4);
            remaining -= offset;
            section += offset;
        }
    }
}

u32 CMsgRes::getFileID() {
    if (m_inf1) {
        return *(u16*)(m_inf1 + 0xC);
    }

    return -1;
}

const wchar_t* CMsgRes::getString(s32 index) {
    return (wchar_t*)(m_dat1 + *(u32*)(m_inf1 + index * 8 + 0x10) + 8);
}