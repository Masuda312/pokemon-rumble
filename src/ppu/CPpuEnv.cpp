#include <ppu/CPpuEnv.hpp>

void CPpuEnv::release() {
    --m_acquireCount;

    if (m_acquireCount == 0) {
        std::tr1::shared_ptr<CPpuEnv> temp = m_self;
        m_self.reset();
        temp.reset();
    }
}

void CPpuEnv::acquire() {
    if (m_acquireCount == 0) {
        m_self = this->shared_from_this();
    }

    ++m_acquireCount;
}