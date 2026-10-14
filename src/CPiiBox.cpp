#include <CPiiBox.hpp>
#include <new>

CPiiBox::CPiiBox(u32 BoxType, u32 limit) {
    PiiBoxNode* piiBoxTail = (PiiBoxNode*)&m_piiBoxTail;
    m_boxType = BoxType;
    m_limit = limit;
    m_size = 0;
    piiBoxTail->next = piiBoxTail;
    piiBoxTail->prev = piiBoxTail;
}

u32 CPiiBox::fn_800E0310(std::tr1::shared_ptr<CPiiPersonalData>& ppd) {
    if (ppd) {
        BITFLAG_CLEAR(ppd->m_flags, UNK_FLAG1);
        BITFLAG_CLEAR(ppd->m_flags, UNK_FLAG2);
        switch (m_boxType) {
            case 1:
                BITFLAG_SET(ppd->m_flags, UNK_FLAG1);
                break;
            case 2:
                BITFLAG_SET(ppd->m_flags, UNK_FLAG2);
                break;
        }
    }

    removePpd(ppd);

    if (m_size + 1 > m_limit) {
        return false;
    } else {
        PiiBoxNode* head = m_piiBoxHead;
        PiiBoxNode* node = static_cast<PiiBoxNode*>(operator new(sizeof(PiiBoxNode)));
        
        new (&node->ppd) std::tr1::shared_ptr<CPiiPersonalData>(ppd);

        head->prev->next = node;
        node->prev = head->prev;
        head->prev = node;
        node->next = head;
        ++m_size;
        return true;
    }
}

DONT_INLINE bool CPiiBox::removePpd(std::tr1::shared_ptr<CPiiPersonalData> ppd) {
    PiiBoxNode* tail = (PiiBoxNode*)&m_piiBoxTail;
    for (PiiBoxNode* i = m_piiBoxHead; i != tail; i = i->next) {
        if (i->ppd != ppd) continue;

        i->prev->next = i->next;
        i->next->prev = i->prev;

        i->ppd.~shared_ptr();
        ::operator delete(i);
        --m_size;
        return true;
    }

    return false;
}

void CPiiBox::healAll() {
    for (PiiBoxNode* i = m_piiBoxHead; i != (PiiBoxNode*)&m_piiBoxTail; i = i->next) {
        i->ppd->fillUpHP();
    }
}

void CPiiBox::clearNewFlag() {
    PiiBoxNode* tail = (PiiBoxNode*)&m_piiBoxTail;
    for (PiiBoxNode* i = m_piiBoxHead; i != tail; i = i->next) {
        BITFLAG_CLEAR(i->ppd->m_flags, NEW_FLAG);
    }
}