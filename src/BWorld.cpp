#include <BWorld.hpp>

BWorldObj* BWorld::getObj(u32 index) {
    if (index == 0) { return 0; }

    return m_worldObjs[index % m_worldObjs.size()].worldObj.get();
}