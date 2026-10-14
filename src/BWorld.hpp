#pragma once

#include <types.h>
#include <vector>
#include <map>
#include <g3d.h>
#include <MSL_COMMON/detail/msl_smart_pointers.hpp>

// forward declarations
class BWorldObj;
class BWorldCamera;
class CDividedGround;
class CShadowCamera;
class CStageCamera;
class CWaza;

struct WorldObjEntry {
    u32 unk1;
    u32 unk2;
    std::tr1::shared_ptr<BWorldObj> worldObj;
};

class BWorld : std::tr1::enable_shared_from_this<BWorld> {
public:
    virtual void vfunc();

    BWorld();

    u32 m_unk1;
    u32 m_unk2;
    u32 m_unk3;
    bool enableOutlines; // 0x18 setting it to false causes all outlines to disappear
    std::tr1::shared_ptr<nw4r::g3d::ScnRoot> m_scnRoot; // 0x1C
    std::tr1::shared_ptr<nw4r::g3d::ScnGroup> m_scnGroup; // 0x24
    std::tr1::shared_ptr<nw4r::g3d::ScnGroup> m_scnGroup2; // 0x2C 2nd one?
    std::vector<std::tr1::shared_ptr<BWorldCamera> > m_cameras; // 0x34 seems to contain CStageCamera and CShadowCamera shared ptrs
    std::tr1::shared_ptr<CStageCamera> m_stageCamera; // 0x40
    std::tr1::shared_ptr<CShadowCamera> m_shadowCamera; // 0x48
    std::tr1::shared_ptr<CDividedGround> m_dividedGround; // 0x50 
    std::vector<WorldObjEntry> m_worldObjs; // 0x58
    void* m_unk4;
    void* m_unk5;
    //std::set<std::tr1::shared_ptr<CWaza>> m_waza; // seems to be std::set because it definitely is a map object and has no key
    //std::tr1::shared_ptr<CKDTree<BModelObj> m_modelObjKDTree; // 0x78
    //std::tr1::shared_ptr<BWorld::EffectData> m_effectData; // 0x80
    //std::tr1::shared_ptr<BWorld::OutlineData> m_outlineData; // 0x88

    BWorldObj* getObj(u32 index);
};