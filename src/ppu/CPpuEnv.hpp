#pragma once

#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <ppu/CEnvironment.hpp>

class CPpuEnv : public NPpu::CEnvironemnt, 
                public std::tr1::enable_shared_from_this<CPpuEnv> {
public:
    UNKOWN_DATA(0x0, 0x20, u8);

    u32 m_acquireCount;
    std::tr1::shared_ptr<CPpuEnv> m_self;
    
    virtual void acquire();
    virtual void release();
};
static_assert(sizeof(CPpuEnv) == 0x3c);
