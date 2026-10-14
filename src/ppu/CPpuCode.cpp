#include <CPpuCode.hpp>

void CPpuCode::release() {
    --m_acquireCount;

    if (m_acquireCount == 0) {
        std::tr1::shared_ptr<CPpuCode> temp = m_self;
        m_self.reset();
        temp.reset();
    }
}

void CPpuCode::acquire() {
    if (m_acquireCount == 0) {
        m_self = this->shared_from_this();
    }

    ++m_acquireCount;
}

bool CPpuCode::parseCode(char* scriptFileName, u32* scriptFile) {
    if (m_pool2 != 0) {
        free(m_pool2);
    }

    m_pool2 = 0;
    if (m_pool1 != 0) {
        free(m_pool1);
    }

    u32 magic = scriptFile[0];
    m_pool1 = 0;

    m_scriptData = 0;
    m_scriptFileName = scriptFileName;

    switch (magic) {
        case 0x201A706B:
        case 0x706B1A20: 
            break;
        case 0x201A6B70:
            m_scriptFileName = 0;
            return false;
        case 0x6b701a20:
            m_scriptFileName = 0;
            return false;
        default:
            m_scriptFileName = 0;
            return false;
    }
    
    u32 pool1Count = scriptFile[4];

    u32 unk1 = scriptFile[1];
    u32 scriptDataSize = scriptFile[2];
    u32 pool2Count = scriptFile[6];

    m_unk1 = unk1;

    size_t pool1AllocationSize = pool1Count * sizeof(u16*); 

    m_scriptDataSize = scriptDataSize;
    m_pool2Count = pool2Count;
    m_pool1Count = pool1Count;
    m_scriptData = scriptFile + 8;

    if (pool1AllocationSize != 0) {
        m_pool1 = (u16**)malloc(pool1AllocationSize);

        if (scriptFile[3] != 0) {
            u32 pool1Offset = 0;
            u16* pool1Data = (u16*)(((u8*)scriptFile) + (m_scriptDataSize + 0x20));

            for (s32 i = 0; i < m_pool1Count; i++) {
                m_pool1[pool1Offset] = pool1Data;

                u16 value;

                do {
                    value = *pool1Data;
                    pool1Data++;
                } while (value != 0);

                pool1Offset += 1;
            }
        }
    }

    size_t pool2AllocationSize = m_pool2Count * 4;
    if (pool2AllocationSize != 0) {
        char** pool2 = (char**)malloc(pool2AllocationSize);
        u32 pool2Size = scriptFile[5];
        m_pool2 = pool2;

        if (pool2Size != 0) {
            s32 pool2Offset = 0;
            char* pool2Data = (char*)((m_scriptDataSize + scriptFile[3]) + ((u8*)scriptFile + 0x20));

            for (s32 i = 0; i < m_pool2Count; i++) {
                m_pool2[pool2Offset] = pool2Data;

                char value;

                do {
                    value = *pool2Data;
                    pool2Data++;
                } while (value != 0);

                pool2Offset += 1;
            }
        }
    }

    return true;
}