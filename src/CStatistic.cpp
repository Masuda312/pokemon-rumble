#include <CStatistic.hpp>

DONT_INLINE s32& getStatEntry(std::vector<s32>& statVector, s32 statId) {
    return statVector[statId];
}

s32 CStatistic::getStatValue(StatisticId statId) {
    switch (statId) {
        case -100 ... -98:
            if (statId + 100 < m_generalStats.size())
                return m_generalStats[statId + 100];
            return 0;
        
        case -200:
            return getSaveSlotData(-1)->m_totalDefeated;

        case -199:
            return getSaveSlotData(-1)->m_totalBefriended;

        case -198 ... -101:
        case -97 ... -1:
        case -0x80000000 ... -201:
            return 0;
        
        case 0 ... 0x7FFFFFFF:
            if (statId < m_battleStats.size())
                return m_battleStats[statId];
    }
    return 0;
}


DONT_INLINE void CStatistic::setStatValue(StatisticId statId, s32 value) {
    value = fn_801139B0(getStatCounterStopValue(statId), value);
    s32 temp;

    switch (statId) {
        case -100 ... -98:
            temp = statId + 100;
            m_generalStats.resize(temp);
            getStatEntry(m_generalStats, temp) = value;
            break;
        case -200:
            getSaveSlotData(-1)->m_totalDefeated = value;
            break;

        case -199:
            getSaveSlotData(-1)->m_totalBefriended = value;
            break;

        case -198 ... -101:
        case -97 ... -1:
        case -0x80000000 ... -201:
            return;
        
        case 0 ... 0x7FFFFFFF:
            m_battleStats.resize(statId);
            getStatEntry(m_battleStats, statId) = value;
            break;
    }
}

void CStatistic::addStatValue(StatisticId statId, s32 amount) {
    s32 statValue;
    s32 temp;

    switch (statId) {
        case -100 ... -98:
            temp = statId + 100;
            if (temp < m_generalStats.size()) {
                statValue = m_generalStats[temp];
            } else {
                statValue = 0;
            }
            break;
        case -200:
            statValue = getSaveSlotData(-1)->m_totalDefeated;
            break;

        case -199:
            statValue = getSaveSlotData(-1)->m_totalBefriended;
            break;

        case -198 ... -101:
        case -97 ... -1:
        case -0x80000000 ... -201:
            statValue = 0;
            break;
        
        case 0 ... 0x7FFFFFFF:
            if (statId < m_battleStats.size()) {
                statValue = m_battleStats[statId];
            } else {
                statValue = 0;
            }
            break;
    }

    s32 maxInt = 0x7FFFFFFF;
    s32 newStatValue;

    if (amount > 0) {
        newStatValue = statValue + amount;

        if (statValue > newStatValue) {
            newStatValue = maxInt;
        }
    } else if (amount < 0) {
        newStatValue = statValue + amount;
        if (statValue > newStatValue) {
            s32 sum = newStatValue;
            s32* result = &sum;

            if (sum < 0x7fffffff) {
                result = &maxInt;
            }

            newStatValue = *result;

        } else {
            newStatValue = 0x80000000;
        }
    } else {
        newStatValue = statValue;
    }

    setStatValue(statId, newStatValue);
}

void CStatistic::setStatCounterStopValue(StatisticId statId, s32 maxValue) {
    m_maxStats[statId] = maxValue;
}

s32 CStatistic::getStatCounterStopValue(StatisticId statId) {
    std::map<StatisticId, s32>::iterator it = m_maxStats.find(statId);
    
    if (it != m_maxStats.end()) {
        return it->second;
    }

    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    return 0x7FFFFFFF;
}

void CStatistic::setWazaUsed(s32 moveId, s32 param_2) {
    if (moveId != 0) {
        size_t index = moveId / 32;
        u32 mask = 1 << (moveId % 32);

        if (index >= m_wazaUsed.size()) {
            m_wazaUsed.resize(index + 1);
        }

        if (param_2 == 0) {
            m_wazaUsed[index] &= ~mask;
        } else {
            m_wazaUsed[index] |= mask;
        }
    } 
}