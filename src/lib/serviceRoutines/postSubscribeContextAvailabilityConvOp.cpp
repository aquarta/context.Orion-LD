/*
*
* Copyright 2015 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "logMsg/logMsg.h"

#include "orionld/common/orionldState.h"             // orionldState

#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "rest/uriParamNames.h"
#include "rest/EntityTypeInfo.h"
#include "serviceRoutines/postSubscribeContextAvailability.h"
#include "serviceRoutines/postSubscribeContextAvailabilityConvOp.h"



/* ****************************************************************************
*
* postSubscribeContextAvailabilityConvOp - 
*
* POST /v1/registry/contextAvailabilitySubscriptions
* POST /ngsi19/contextAvailabilitySubscriptions
*
* Payload In:  SubscribeContextAvailabilityRequest
* Payload Out: SubscribeContextAvailabilityResponse
*
* URI parameters
*   - !exist=entity::type
*   - exist=entity::type
*   x entity::type=TYPE    (NOT TREATED)
*/
std::string postSubscribeContextAvailabilityConvOp
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  std::string     answer;
  EntityTypeInfo  typeInfo       = EntityTypeEmptyOrNotEmpty;


  // 01. Take care of URI params
  if (orionldState.in.entityTypeDoesNotExist == true)
  {
    typeInfo = EntityTypeEmpty;
  }
  else if (orionldState.in.entityTypeExists == true)
  {
    typeInfo = EntityTypeNotEmpty;
  }


  // 02. Fill in SubscribeContextAvailabilityRequest (actually, modify it)
  parseDataP->scar.res.fill(typeInfo);


  // 03. Call standard operation
  answer = postSubscribeContextAvailability(ciP, components, compV, parseDataP);


  // 04. Cleanup and return result
  parseDataP->scar.res.release();

  return answer;
}
