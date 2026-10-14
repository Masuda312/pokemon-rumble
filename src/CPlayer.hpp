#pragma once

#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <types.h>
#include <CPiiBox.hpp>
#include <CPiiPersonalData.hpp>

class CControllerWiiRemote;

class CPlayerSub10 {
public:
    bool m_active;
    CPiiBox m_piiBox;
    std::tr1::shared_ptr<CPiiPersonalData> m_ppd;
    std::tr1::shared_ptr<CPiiPersonalData> m_incomingPpd;
};

class CPlayer {
public:
    char pad_0x04[0x08];
    u32 m_playerIndex;
    CControllerWiiRemote* m_controllerWiiRemote;
    CPlayerSub10 m_playerSub10;
    char pad3[0x08];
};
