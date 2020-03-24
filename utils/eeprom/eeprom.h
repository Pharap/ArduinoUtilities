/// @brief
/// A namespace containing eeprom-related utilities.
namespace eeprom {}

#include "readEeprom.h"
#include "writeEeprom.h"
#include "overwriteEeprom.h"

#include "EepromReference.h"
#include "specialisations/EepromReference_const.h"

#include "EepromPointer.h"
#include "specialisations/EepromPointer_const.h"

#include "EepromArray.h"
#include "specialisations/EepromArray_const.h"