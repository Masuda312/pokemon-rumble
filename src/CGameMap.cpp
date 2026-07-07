#include <CGameMap.hpp>
// extern std::tr1::shared_ptr<CUiBase> FUN_800AA730(std::tr1::weak_ptr<CUiBase>* arg);

//CGameMap::CGameMap(const SomeStageResource& arg) : m_mapDesc(arg.mapDesc), m_ppuEnv(arg.ppuEnv) {
//    // WIP
//}

//u8 CGameMap::FUN_800a7f70() {
//    u32 *puVar1;
//    int iVar2;
//    int iVar3;
//    undefined4 local_18 [4];
//  
//    puVar1 = getCurrentStageId();
//    local_18[0] = *puVar1;
//    iVar2 = FUN_80125180(local_18);
//    if (iVar2 != 0) {
//        iVar2 = 0;
//        do {
//            iVar3 = CDlgPiiSelector_vfunc_80094130(m_dlgPiiSelector, iVar2);
//            if (iVar3 != 0) {
//                return 1;
//            }
//
//            iVar2 = iVar2 + 1;
//        } while (iVar2 < 4);
//    }
//
//    return m_hideUIFlag;
//}

MapDesc* CGameMap::getMapDesc() {
    return m_mapDesc;
}

BWorld* getWorld(std::tr1::shared_ptr<BWorld> world) {
    return world.get();
}

CShadowCamera* getShadowCamera(std::tr1::shared_ptr<CShadowCamera> shadowCamera) {
    return shadowCamera.get();
}

CDividedGround* getDividedGround(std::tr1::shared_ptr<CDividedGround> dividedGround) {
    return dividedGround.get();
}

bool CGameMap::isUIOpen(std::tr1::shared_ptr<CUiBase>* sharedPtr) {
    if (!*sharedPtr) {
        return false;
    }
    std::tr1::shared_ptr<CUiBase> temp = m_field19_0x1c.lock();
    if (temp == *sharedPtr) {
        return true;
    }
    if ((temp) && (!temp->vfunc18())) {
        return false;
    }

    temp.reset();
    
    m_field19_0x1c = *sharedPtr;
    return true;
}

void CGameMap::resetOpenUi_fn_800a9b60(std::tr1::shared_ptr<CUiBase>* sharedPtr) {
    std::tr1::shared_ptr<CUiBase> temp = m_field19_0x1c.lock();
    if (temp && temp == *sharedPtr) {
        m_field19_0x1c.reset();
    }
}

s32 CGameMap::getBattleRoyalTimer() {
    return m_battleRoyalTimer;
}

bool CGameMap::isTimerSpeedActive() {
    return m_battleRoyalTimerSpeed;
}

void CGameMap::resetBattleRoyalTimerSpeed() {
    m_battleRoyalTimerSpeed = 0;
}

void CGameMap::addBattleRoyalTimer(s32 deltaFrames) {
    m_battleRoyalTimer += deltaFrames;

    if (deltaFrames <= 0) {
        return;
    }

    m_battleRoyalDisplay->notifyTimeAdded();
}

void CGameMap::setBattleRoyalTimer(s32 battleRoyalTimer, s32 battleRoyalTimerSpeed) {
    m_battleRoyalTimer = battleRoyalTimer;
    m_battleRoyalTimerSpeed = battleRoyalTimerSpeed;
}

void CGameMap::setMovementLockTimer(s32 lockTimer) {
    s32 *result = lockTimer < m_movementLockTimer ? &m_movementLockTimer : &lockTimer;

    m_movementLockTimer = *result;
}

void CGameMap::setHideUiFlag(u8 hideUiFlag) {
    m_hideUIFlag = hideUiFlag;
}

CUiBase* CGameMap::getOpenUi() {
    std::tr1::shared_ptr<CUiBase> temp(m_field19_0x1c.lock());
    return temp.get();
}

CPostEffect* CGameMap::getPostEffect() {
    return m_postEffect.get();
}

CNumericInput* CGameMap::getNumericInput() {
    return m_numericInput.get();
}

CEnemyInfo* CGameMap::getEnemyInfo() {
    return m_enemyInfo.get();
}

CMsgBalloon* CGameMap::getMsgBalloon() {
    return m_msgBalloon.get();
}

Unknown* CGameMap::getUnknownClass() {
    return m_unknown.get();
}

CPauseMenu* CGameMap::getPauseMenu() {
    return m_pauseMenu.get();
}

CLayoutManager* CGameMap::getLayoutManager() {
    return m_layoutManager.get();
}

CComboDisplay* CGameMap::getComboDisplay() {
    return m_comboDisplay.get();
}

CBattleRoyalDisplay* CGameMap::getBattleRoyalDisplay() {
    return m_battleRoyalDisplay.get();
}

CMoneyLifeDisplay* CGameMap::getMoneyLifeDisplay() {
    return m_moneyLifeDisplay.get();
}

CNoticeDisplay* CGameMap::getNoticeDisplay() {
    return m_noticeDisplay.get();
}

CDlgMsgWin* CGameMap::getDlgMsgWin() {
    return m_dlgMsgWin.get();
}

CDlgInfo* CGameMap::getDlgInfo() {
    return m_dlgInfo.get();
}

CDlgCollection* CGameMap::getDlgCollection() {
    return m_dlgCollection.get();
}

CDlgPiiList* CGameMap::getDlgPiiList() {
    return m_dlgPiiList.get();
}

CDlgPiiSelector* CGameMap::getDlgPiiSelector() {
    return m_dlgPiiSelector.get();
}

CMiniMap* CGameMap::getMiniMap() {
    return m_miniMap.get();
}

CWorldObjStatDisplay* CGameMap::getWorldStatDisplay() {
    return m_worldObjStatDisplay.get();
}

BWorld* CGameMap::getWorld() {
    return m_bWorld.get();
}
