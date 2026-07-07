#include <types.h>
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <CPiiPersonalData.hpp>

class CPiiBox {
public:    
    struct PiiBoxNode {
        PiiBoxNode* prev;
        PiiBoxNode* next;
        std::tr1::shared_ptr<CPiiPersonalData> ppd;
    };
public:
    u32 m_unk1;
    u32 m_limit;
    u32 m_size;
    PiiBoxNode* m_piiBoxTail;
    PiiBoxNode* m_piiBoxHead;
};