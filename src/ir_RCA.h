#ifndef IR_RCA_H_
#define IR_RCA_H_

#include <stdint.h>
#include "IRremoteESP8266.h"

// Supports:
//   Brand: Microsoft,  Model: Xbox DVD Movie Playback Kit Receiver

// Constants
// Ref:
//  http://www.sbprojects.com/knowledge/ir/rca.php
const uint16_t kRcaTick = 500;
const uint16_t kRcaHdrMarkTicks = 8;
const uint16_t kRcaHdrMark = kRcaHdrMarkTicks * kRcaTick;
const uint16_t kRcaHdrSpaceTicks = 8;
const uint16_t kRcaHdrSpace = kRcaHdrSpaceTicks * kRcaTick;
const uint16_t kRcaBitMarkTicks = 1;
const uint16_t kRcaBitMark = kRcaBitMarkTicks * kRcaTick;
const uint16_t kRcaOneSpaceTicks = 4;
const uint16_t kRcaOneSpace = kRcaOneSpaceTicks * kRcaTick;
const uint16_t kRcaZeroSpaceTicks = 1;
const uint16_t kRcaZeroSpace = kRcaZeroSpaceTicks * kRcaTick;
const uint16_t kRcaRptSpaceTicks = 2;
const uint16_t kRcaRptSpace = kRcaRptSpaceTicks * kRcaTick;
// cpd
const uint16_t kRcaRptLength = 4;
const uint16_t kRcaMinCommandLengthTicks = 193;
// cpd
const uint32_t kRcaMinCommandLength = kRcaMinCommandLengthTicks * kRcaTick;
const uint32_t kRcaMinGap =
    kRcaMinCommandLength -
    (kRcaHdrMark + kRcaHdrSpace + kRCABits * (kRcaBitMark + kRcaOneSpace) +
     kRcaBitMark);
const uint16_t kRcaMinGapTicks =
    kRcaMinCommandLengthTicks -
    (kRcaHdrMarkTicks + kRcaHdrSpaceTicks +
     kRCABits * (kRcaBitMarkTicks + kRcaOneSpaceTicks) + kRcaBitMarkTicks);

// IR address and commands for Xbox DVD Movie Playback Kit transmitter
const uint32_t kXboxAddress =       5;

const uint32_t kXboxDisplay =       0;  // cpd
const uint32_t kXboxReverse =      29;
const uint32_t kXboxPlay =         21;
const uint32_t kXboxForward =      28;
const uint32_t kXboxSkipMinus =    34;
const uint32_t kXboxStop =         31;
const uint32_t kXboxPause =        25;
const uint32_t kXboxSkipPlus =     32;
const uint32_t kXboxTitle =         0;  // cpd
const uint32_t kXboxInfo =         60;
const uint32_t kXboxUp =           89;
const uint32_t kXboxLeft =         86;
const uint32_t kXboxSelect =      244;
const uint32_t kXboxRight =        87;
const uint32_t kXboxDown =         88;
const uint32_t kXboxMenu =          8;
const uint32_t kXboxBack =         39;
const uint32_t kXbox1 =            49;
const uint32_t kXbox2 =            50;
const uint32_t kXbox3 =            51;
const uint32_t kXbox4 =            52;
const uint32_t kXbox5 =            53;
const uint32_t kXbox6 =            54;
const uint32_t kXbox7 =            55;
const uint32_t kXbox8 =            56;
const uint32_t kXbox9 =            57;
const uint32_t kXbox0 =            48;
#endif  // IR_RCA_H_
