/*
*
* Copyright 2022 FIWARE Foundation e.V.
*
* This file is part of Orion-LD Context Broker.
*
* Orion-LD Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion-LD Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion-LD Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* orionld at fiware dot org
*
* Author: Ken Zangelin
*/



// -----------------------------------------------------------------------------
//
// urlDecode -
//
void urlDecode(char* str)
{
  int   fromIx = 0;
  int   toIx;

  //
  // Just forward until reaching the first '%'
  //
  while (str[fromIx] != 0)
  {
    if (str[fromIx] == '%')
      break;
    ++fromIx;
  }
  toIx = fromIx;

  while (str[fromIx] != 0)
  {
    if (str[fromIx] == '%')
    {
      if ((str[fromIx+1] == '2') && (str[fromIx+2] == '2'))
      {
        str[toIx] = 0x22;  // Single quote;
        fromIx += 2;
      }
    }
    else
      str[toIx] = str[fromIx];
    ++fromIx;
    ++toIx;
  }
  str[toIx] = 0;
}
