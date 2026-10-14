#include <types.h>
#include <map>
#include <algorithm>
#include <climits>
#include <vector>
#include <SaveData.hpp>

extern const s32 &fn_801139B0(const s32 &a, const s32 &b);

class CStatistic {
public:
    enum StatisticId {
        STAT_DEFEATED = -200,
        STAT_BEFRIENDED = -199,
        STAT_SWITCHES = -100,
        STAT_FAILED_SWITCHES = -99,
        STAT_TOTAL_MONEY_EARNED = -98,
        STAT_USED_MOVES = 1,
        STAT_HITS = 2,
        STAT_SUPER_EFFECTIVE_HITS = 3,
        STAT_ENEMIES_BECAME_WOBBLY = 4,
        STAT_WOBBLY_DEFEATED = 5,
        STAT_LONGEST_COMBO = 6,
        STAT_MAX_HIT_DAMAGE_DEALT = 7,
        STAT_MAX_HIT_DAMAGE_RECEIVED = 8,
        STAT_STAGES_CLEARED = 9,
        STAT_BATTLE_ROYALE_WINS = 10,
        STAT_STAGES_LOST = 11,
        STAT_BATTLE_ROYALE_LOSSES = 12,
        STAT_TOTAL_FAINTED = 13,
        STAT_RELEASED = 15,
        STAT_RECRUITED = 16,
        STAT_MOVES_TAUGHT = 17,
        STAT_TOTAL_GOODBYE_GIFTS = 18,
        STAT_TOTAL_SPENT_ON_RECRUITS = 19,
        STAT_TOTAL_SPENT_ON_MOVES = 20,
    };
public:
    std::vector<s32> m_generalStats; // 0x0
    std::vector<s32> m_unkvec1; // 0xC
    std::vector<s32> m_battleStats; // 0x18
    std::vector<s32> m_unkvec2; // 0x24
    std::vector<s32> m_wazaUsed; // 0x30
    char pad0x54[0x14]; // 0x30 -> 0x50
    std::map<StatisticId, s32> m_maxStats;

    CStatistic();
    s32 getStatValue(StatisticId statId);
    void setStatValue(StatisticId statId, s32 value);
    void addStatValue(StatisticId statId, s32 amount);
    void setStatCounterStopValue(StatisticId statId, s32 maxValue);
    s32 getStatCounterStopValue(StatisticId statId);
    bool isWazaUsed(s32 param_1);
    void setWazaUsed(s32 moveId, s32 param_2);
    s32 getWazaUsedCount();
};

s32& getStatEntry(std::vector<s32>& statVector, s32 statId);