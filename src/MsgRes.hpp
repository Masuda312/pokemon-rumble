#pragma once

#include <types.h>
#include <string>
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <CMsgRes.hpp>

struct DateFormatMsgIDs {
    u32 monthLong;
    u32 monthShort;
    u32 dateFmtLongA;
    u32 dateFmtLongB;
    u32 dateFmtShortA;
    u32 dateFmtShortB;
    u32 weekdayEmpty; // ?
    u32 weekdayLong;
    u32 weekdayShortA;
    u32 weekdayShortB;
    u32 weekdayPlacement;
};

struct TimeFormatMsgIDs {
    u32 timeFmtLongA;
    u32 timeFmtLongB;
    u32 timeFmtShortA;
    u32 timeFmtShortB;
    u32 hour12Base;
    u32 amLabel;
    u32 pmLabel;
    u32 labelPlacement;
};

void constructSharedVecMsgRes(u32 size);
void setSharedMsgRes(s32 fileID, const std::tr1::shared_ptr<CMsgRes>& msgRes);
const wchar_t* getLocalizedName(s32 msgID, const wchar_t* fallback);
void formatDate(std::basic_string<wchar_t>* out, s32 year, s32 month, s32 day, u32 formatFlags);
void setTimeFormatMsgIds(const DateFormatMsgIDs* msgIDs);
void formatTime(std::basic_string<wchar_t>* out, s32 hour, s32 minute, s32 second, u32 formatFlags);
