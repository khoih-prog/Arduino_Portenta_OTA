/*
   This file is part of ArduinoIoTCloud.

   Copyright 2019 ARDUINO SA (http://www.arduino.cc/)

   This software is released under the GNU General Public License version 3,
   which covers the main part of arduino-cli.
   The terms of this license can be found at:
   https://www.gnu.org/licenses/gpl-3.0.en.html

   You can be released from the requirements of the above licenses by purchasing
   a commercial license. Buying such a license is mandatory if you want to modify or
   otherwise use the software for commercial activities involving the Arduino
   software without disclosing the source code of your own applications. To purchase
   a commercial license, send an email to license@arduino.cc.
*/

/******************************************************************************
 * INCLUDE
 ******************************************************************************/

#include "Arduino_Portenta_OTA.h"

/******************************************************************************
   CTOR/DTOR
 ******************************************************************************/

Arduino_Portenta_OTA::Arduino_Portenta_OTA(StorageTypePortenta const storage_type, uint32_t const data_offset)
: _storage_type{storage_type}
, _data_offset{data_offset}
, _program_length{0}
{

}

Arduino_Portenta_OTA::~Arduino_Portenta_OTA()
{

}

/******************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 ******************************************************************************/

Arduino_Portenta_OTA::Error Arduino_Portenta_OTA::begin()
{
  Serial1.begin(115200);
  return (init() == false) ? Error::OtaStorageInit : Error::None;
}

void Arduino_Portenta_OTA::setUpdateLen(uint32_t const program_length)
{
  _program_length = program_length;
}

Arduino_Portenta_OTA::Error Arduino_Portenta_OTA::update()
{
  if(!open())
    return Error::OtaStorageOpen;

  if(!write())
    return Error::OtaStorageWrite;

  return Error::None;
}

void Arduino_Portenta_OTA::reset()
{
  NVIC_SystemReset();
}