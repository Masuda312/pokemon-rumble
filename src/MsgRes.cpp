#include <types.h>
#include <vector>
#include <cstdio>
#include <string>
#include <MSL_Common/detail/msl_smart_pointers.hpp>
#include <revolution/OS.h>
#include <cwctype>

#include <MsgRes.hpp>
#include <CMsgRes.hpp>

std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<CMsgRes> > > gSharedVecCMsgRes;

void constructSharedVecMsgRes(u32 size) {
    gSharedVecCMsgRes.reset(new std::vector<std::tr1::shared_ptr<CMsgRes> >(size));
}

DateFormatMsgIDs gDateFormatMsgIDs = {
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff
};

const wchar_t* gMonthFallbacks[12] = {
    L"1", L"2", L"3", L"4", L"5", L"6", 
    L"7", L"8", L"9", L"10", L"11", L"12"
};

const wchar_t* gWeekdayFallbacks[7] = {
    L"\u65e5", L"\u6708", L"\u706b", L"\u6c34", L"\u6728", L"\u91d1", L"\u571f"
};

static wchar_t gZeroString[] = L"0\0\0";

TimeFormatMsgIDs gTimeFormatMsgIds = {
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff,
    0xffffffff
};

void setSharedMsgRes(s32 fileID, const std::tr1::shared_ptr<CMsgRes>& msgRes) {
    if (!gSharedVecCMsgRes) { return; }

    if (fileID < (s32)gSharedVecCMsgRes->size()) {
        (*gSharedVecCMsgRes)[fileID] = msgRes;
    }
}

const wchar_t* getLocalizedName(s32 msgID, const wchar_t* fallback) {
    CMsgRes* msgRes;
    s32 msgResIdx = msgID >> 0x10;

    if ((gSharedVecCMsgRes) && msgResIdx >= 0 && msgResIdx < gSharedVecCMsgRes->size() && ((*gSharedVecCMsgRes)[msgResIdx])) {
        msgRes = (*gSharedVecCMsgRes)[msgResIdx].get();
    }
    else {
        msgRes = 0;
    }

    if (!msgRes) {
        return fallback;
    }

    const wchar_t* str = msgRes->getString(msgID & 0xFFFF);

    return !str ? fallback : str;
}

void setTimeFormatMsgIds(const DateFormatMsgIDs* msgIDs) {
    gDateFormatMsgIDs = *msgIDs;
}

// offsets off by 0x10 because i dont know how to get the "vector length error" to generate before the other stuff in .data section
void formatDate(std::basic_string<wchar_t>* out, s32 year, s32 month, s32 day, u32 formatFlags) {
    wchar_t dateBuf[0x100];

    if ((formatFlags & 1)) {
        const wchar_t* extra;
        u32 monthFormat;
        
        if ((formatFlags & 0x40)) {
            monthFormat = gDateFormatMsgIDs.monthLong;
        } else {
            monthFormat = gDateFormatMsgIDs.monthShort;
        }
        
        s32 monthId = month + monthFormat;

        const wchar_t* monthName = getLocalizedName(--monthId, 0);

        if (!monthName) {
            u32 monthIndex = month - 1;
            monthName = gMonthFallbacks[monthIndex];
        }

        extra = day == 1 ? getLocalizedName(gDateFormatMsgIDs.weekdayEmpty, L"\0") : L"\0"; 

        if ((formatFlags & 8)) {
            snprintf(dateBuf, 0x100, getLocalizedName(gDateFormatMsgIDs.dateFmtLongB, L"%1$ls/%2$d"), monthName, day, extra);
        }
        else {
            snprintf(dateBuf, 0x100, getLocalizedName(gDateFormatMsgIDs.dateFmtLongA, L"%1$d/%2$ls/%3$d"), year, monthName, day, extra);
        }
    } 
    else {
        if ((formatFlags & 8)) {
            snprintf(dateBuf, 0x100, getLocalizedName(gDateFormatMsgIDs.dateFmtShortB, L"%1$d/%2$d/%3$d"), month, day);
        } else {
            snprintf(dateBuf, 0x100, getLocalizedName(gDateFormatMsgIDs.dateFmtShortA, L"%1$d/%2$d/%3$d"), year, month, day);
        }
    }

    if (!(formatFlags & 0x20)) {
        *out = dateBuf;
    }
    else {
        OSCalendarTime calTime;
        memset(&calTime, 0, sizeof(calTime));
        calTime.year = year;
        calTime.month = month - 1;
        calTime.mday = day;

        s64 ticks = OSCalendarTimeToTicks(&calTime);
        OSTicksToCalendarTime(ticks, &calTime);

        u32 calTimeWday = calTime.wday;
        u32 weekLength;
        if ((formatFlags & 0x40)) {
            weekLength = gDateFormatMsgIDs.weekdayLong;
        } else if ((formatFlags & 2)) {
            weekLength = gDateFormatMsgIDs.weekdayShortA;
        } else {
            weekLength = gDateFormatMsgIDs.weekdayShortB;
        }

        s32 weekdayID = calTimeWday;

        const wchar_t* weekdayName = getLocalizedName(weekdayID += weekLength, 0);

        if (!weekdayName) {
            weekdayName = gWeekdayFallbacks[calTimeWday];
        }

        s32 weekdayPlacement = wcstol(getLocalizedName(gDateFormatMsgIDs.weekdayPlacement, gZeroString), 0, 10);

        if (weekdayPlacement == 0) {
            std::basic_string<wchar_t> weekdayStr(weekdayName);
            std::basic_string<wchar_t> weekdayWithSpace = weekdayStr + L' ';
            std::basic_string<wchar_t> result = weekdayWithSpace + dateBuf;
            *out = result;
        } else {
            std::basic_string<wchar_t> dateStr(dateBuf);
            std::basic_string<wchar_t> dateWithSpace = dateStr + L' ';
            std::basic_string<wchar_t> result = dateWithSpace + weekdayName;
            *out = result;
        }
    }

    // probably not what the source did
    out->uppercase_at(0);
}

void setTimeFormatMsgIds(const TimeFormatMsgIDs* msgIDs) {
    gTimeFormatMsgIds = *msgIDs;
}

void formatTime(std::basic_string<wchar_t>* out, s32 hour, s32 minute, s32 second, u32 formatFlags) {
    s32 hoursPerCycle;
    wchar_t timeBuf[0x100];

    if ((formatFlags & 0x10)) { 
        hoursPerCycle = 12; 
    }   
    else if (formatFlags & 0x20) {
        hoursPerCycle = 24;
    }
    else {
        hoursPerCycle = (wcstol(getLocalizedName(gTimeFormatMsgIds.hour12Base, gZeroString), 0, 10) == 24) ? 24 : 12;
    }

    s32 displayHour = hour % hoursPerCycle;
    if (hoursPerCycle == 12 && displayHour == 0) {
        displayHour = 12;
    }

    if ((formatFlags & 1)) {
        if ((formatFlags & 8)) {
            snprintf(timeBuf, 0x100, getLocalizedName(gTimeFormatMsgIds.timeFmtLongB, L"%d:%02d"),displayHour, minute);
        }
        else {
            snprintf(timeBuf, 0x100, getLocalizedName(gTimeFormatMsgIds.timeFmtLongA, L"%d:%02d:%02d"), displayHour, minute, second);
        }
    } 
    else if ((formatFlags & 8)) {
        snprintf(timeBuf, 0x100, getLocalizedName(gTimeFormatMsgIds.timeFmtShortB, L"%d:%02d"), displayHour, minute);
    }
    else {
        snprintf(timeBuf, 0x100, getLocalizedName(gTimeFormatMsgIds.timeFmtShortA, L"%d:%02d:%02d"), displayHour, minute, second);
    }

    if (hoursPerCycle == 24) {
        *out = timeBuf;
    }
    else {
        const wchar_t* ampmLabel = hour < 12 ? getLocalizedName(gTimeFormatMsgIds.amLabel, L"AM") : getLocalizedName(gTimeFormatMsgIds.pmLabel, L"PM");

        s32 labelPlacement = wcstol(getLocalizedName(gTimeFormatMsgIds.labelPlacement, gZeroString), 0, 10);

        if (labelPlacement == 0) {
            std::basic_string<wchar_t> labelStr(ampmLabel);
            std::basic_string<wchar_t> labelWithSpace = labelStr + L' ';
            std::basic_string<wchar_t> result = labelWithSpace + timeBuf;
            *out = result;
        }
        else {
            std::basic_string<wchar_t> timeStr(timeBuf);
            std::basic_string<wchar_t> timeWithSpace = timeStr + L' ';
            std::basic_string<wchar_t> result = timeWithSpace + ampmLabel;
            *out = result;
        }
    }
}
