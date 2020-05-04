#define __STDC_LIMIT_MACROS
#include "ir_RCA.h"
#include <stdint.h>
#include <algorithm>
#include "IRrecv.h"
#include "IRsend.h"
#include "IRutils.h"

#if (SEND_RCA)
// Send a RCA formatted message.
//
// Args:
//   data:   The message to be sent.
//   nbits:  The number of bits of the message to be sent. Typically kRCABits.
//   repeat: The number of times the command is to be repeated.
//
// Status: STABLE / Known working.
//
// Ref:
//  http://www.sbprojects.com/knowledge/ir/rca.php
void IRsend::sendRCA(uint64_t data, uint16_t nbits, uint16_t repeat) {
  sendGeneric(kRcaHdrMark, kRcaHdrSpace, kRcaBitMark, kRcaOneSpace, kRcaBitMark,
              kRcaZeroSpace, kRcaBitMark, kRcaMinGap, kRcaMinCommandLength,
              data, nbits, 56, true, repeat,
              33);
}

// Calculate the raw RCA data based on address and command.
// Args:
//   address: A 4-bit address value.
//   command: A 8-bit command value.
// Returns:
//   A raw 24-bit RCA message.
//
// Status: STABLE / Expected to work.
//
// Ref:
//  http://www.sbprojects.com/knowledge/ir/rca.php
uint32_t IRsend::encodeRCA(uint16_t address, uint16_t command) {
  return (address << 20) + (command << 12) + ((address ^ 0xF) << 8) + (command ^ 0xFF);
}
#endif  // (SEND_RCA)

#if (DECODE_RCA)
// Decode the supplied RCA message.
//
// Args:
//   results: Ptr to the data to decode and where to store the decode result.
//   offset:  The starting index to use when attempting to decode the raw data.
//            Typically/Defaults to kStartOffset.
//   nbits:   The number of data bits to expect. Typically kRCABits.
//   strict:  Flag indicating if we should perform strict matching.
// Returns:
//   boolean: True if it can decode it, false if it can't.
//
// Status: STABLE / Known good.
//
// Notes:
//     a 4 bit address & a 8 bit command in 24 bit data form.
//     i.e. address + command + inverted(address) + inverted(command)
//
// Ref:
//   http://www.sbprojects.com/knowledge/ir/rca.php
bool IRrecv::decodeRCA(decode_results *results, uint16_t offset,
                       const uint16_t nbits, const bool strict) {
  if (results->rawlen < kRcaRptLength + offset - 1)
    return false;  // Can't possibly be a valid RCA message.
  if (strict && nbits != kRCABits)
    return false;  // Not strictly an RCA message.

  uint64_t data = 0;

  // Header - All RCA messages have this Header Mark.
  if (!matchMark(results->rawbuf[offset++], kRcaHdrMark)) return false;

  // Match Header (cont.) + Data + Footer
  if (!matchGeneric(results->rawbuf + offset, &data,
                    results->rawlen - offset, nbits,
                    0, kRcaHdrSpace,
                    kRcaBitMark, kRcaOneSpace,
                    kRcaBitMark, kRcaZeroSpace,
                    kRcaBitMark, kRcaMinGap, true)) return false;
  // Compliance
  // Calculate command and optionally enforce integrity checking.
  uint8_t command = (data & 0xFF0) >> 12;
  // Command is sent twice, once as plain and then inverted.
  if ((command ^ 0xFF) != (data & 0xFF)) {
    if (strict) return false;  // Command integrity failed.
    command = 0;  // The command value isn't valid, so default to zero.
  }
  // Calculate address and optionally enforce integrity checking.
  uint8_t address = (data & 0xF00000) >> 20;
  // Address is sent twice, once as plain and then inverted.
  if ((address ^ 0xF) != ((data & 0xF00) >> 8)) {
    if (strict) return false;  // Address integrity failed.
    address = 0;  // The address value isn't valid, so default to zero.
  }

  // Success
  results->bits = nbits;
  results->value = data;
  results->decode_type = RCA;
  results->command = command;
  results->address = address;
  return true;
}
#endif  // DECODE_RCA
