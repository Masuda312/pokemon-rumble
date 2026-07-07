#include "CGameStage.hpp"

CGameMap* CGameStage::getGameMap() {
  return m_GameMapPtr.get();
}

u32 CGameStage::getLives() {
  return m_lives;
}

void CGameStage::setLives(s32 lives) {
  s32 values[3];
  values[0] = 3;
  values[1] = 0;
  values[2] = lives;

  s32* result = &values[1]; 
  if (lives > 0) {
    result = &values[2];
  }
  if (*result > 3) {
    result = &values[0];
  }
  
  m_lives = *result;
}

void CGameStage::changeStage(u32* stageIdPtr) {
    m_stageTransitionState = 1;
    m_stageId = *stageIdPtr;
}

void CGameStage::setStageTransitionState(s32 transitionState) {
  switch (transitionState) {
    default:
      m_stageTransitionState = 3;
      break;
    case 1:
      m_stageTransitionState = 5;
      break;
    case 2:
      m_stageTransitionState = 6;
      break;
    case 3:
      m_stageTransitionState = 7;
      break;
    case 4: 
      m_stageTransitionState = 4;
      break;
  }
}