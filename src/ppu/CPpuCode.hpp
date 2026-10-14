#pragma once

#include "types.h"
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <cstdlib>
#include <memory>

namespace NPpu {

class CCode {
public:
    char* m_scriptFileName; // 0x00
    u32 m_unk1; // 0x04
    u32 m_scriptDataSize; // 0x08
    s32 m_pool2Count; // 0x0C
    s32 m_pool1Count; // 0x10
    u32* m_scriptData; // 0x14
    // in the pkc headers the 2 pools seem to be switched up
    char** m_pool2; // 0x18
    u16** m_pool1; // 0x1C wchar?

    virtual void CCode_vfunc_dtor_80170920(); // 0x20
    virtual void CCode_vfunc_80170920();
    virtual void CCode_vfunc_fn_801706B0();
};

} // namespace NPpu

class CPpuCode : public NPpu::CCode,
                 public std::tr1::enable_shared_from_this<CPpuCode> {
public:
    virtual void CPpuCode_vfunc_80105250();
    virtual void acquire();
    virtual void release();

    s32 m_acquireCount; // 0x2C
    std::tr1::shared_ptr<CPpuCode> m_self; // 0x30
    // std::tr1::shared_ptr<CFileData> m_fileData; // 0x38
    u32 unk0; // 0x3C
    u32 m_somethingLen; // 0x40

    bool parseCode(char* scriptFileName, u32* scriptFile);
};
