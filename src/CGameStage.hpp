#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <types.h>
#include <CGameMap.hpp>

class CGameStage {
public:
    virtual void vfunc_800BDB40();
    virtual void vfunc_800BD350();
    virtual void vfunc_800BD380();
    virtual void vfunc_800BD3B0();
    virtual void vfunc_800BD3E0();
    virtual void vfunc_800BDC50();
    virtual CGameMap* getGameMap();
    virtual u32 getLives();
    virtual void setLives(s32 lives);
    virtual void changeStage(u32* stageIdPtr); // is changeStage or similar (puts 00010101 onto r0 which is the current area and progresses it to 00010102, 00010103, etc. when you change areas within the map)
    virtual void setStageTransitionState(s32 transitionState);
    virtual void vfunc_800BD2E0();
    virtual void vfunc_800BD340();

    char pad[0x14];
    u32 m_stageId;
    s32 m_lives;
    std::tr1::shared_ptr<CGameMap> m_GameMapPtr;
    u32 m_stageTransitionState;
};