/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#include <string>

#include "Representation.h"
#include "AMLInterface.h"
#include "AMLException.h"

#include "camlrepresentation.h"
#include "camlinterface.h"
#include "camlerrorcodes.h"
#include "camlutils.h"

using namespace std;

CAMLErrorCode CreateRepresentation(representation_t* repHandle, const char* filePath)
{
    VERIFY_PARAM_NON_NULL(repHandle);
    VERIFY_PARAM_NON_NULL(filePath);

    *repHandle = new(std::nothrow) Representation(filePath);
    if (!repHandle)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode DestroyRepresentation(representation_t repHandle)
{
    VERIFY_PARAM_NON_NULL(repHandle);

    Representation* rep = static_cast<Representation*>(repHandle);
    delete rep;

    return CAML_OK;
}

CAMLErrorCode Representation_GetRepId(representation_t repHandle, char** repId)
{
    VERIFY_PARAM_NON_NULL(repHandle);
    VERIFY_PARAM_NON_NULL(repId);

    Representation* rep = static_cast<Representation*>(repHandle);
    string repIdStr = rep->getRepresentationId();

    try
    {
        *repId = ConvertStringToCharStr(repIdStr);
    }
    catch (const AMLException& e)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode Representation_GetConfigInfo(representation_t repHandle, amlObjectHandle_t* amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(repHandle);
    VERIFY_PARAM_NON_NULL(amlObjHandle);

    try
    {
        //@TODO: should be this after Representaiton cpp API is modified.
        //const AMLObject& amlObj = static_cast<Representation*>(repHandle)->getConfigInfo();
        //*amlObjHandle = static_cast<amlObjectHandle_t>(const_cast<AMLObject*>(&amlObj));

        AMLObject* amlObj = static_cast<Representation*>(repHandle)->getConfigInfo();
        *amlObjHandle = static_cast<amlObjectHandle_t>(amlObj);
    }
    catch (const AMLException& e)
    {
        return CAML_INVALID_AML_SCHEMA;
    }

    return CAML_OK;
}
