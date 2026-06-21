#ifndef RESPIROROLE_H
#define RESPIROROLE_H

#include "enumutilities.h"

DECLARE_ENUM(RespiroRole,
    // Start from Qt::UserRole = 0x0100 = 256
    channel=256,
    channelID,
    sampleID,
    hsVolMl,
    co2MaxPpm,
    o2MinPerc,
    o2MaxPerc,
    ch4MaxPpm,
    leakPass,
    pressPass,
    volPass,
    measureStable,
    isActive,
    inExperiment,
    cycle,
    startTime,
    completeCycle,
    statusText,
    statusColor
)

#endif
