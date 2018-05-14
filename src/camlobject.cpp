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
#include <map>
#include <vector>
#include <cstring>

#include "AMLInterface.h"
#include "AMLException.h"

#include "camlinterface.h"
#include "camlerrorcodes.h"
#include "camlutils.h"

using namespace std;
using namespace AML;

CAMLErrorCode CreateAMLObject(const char* deviceId, const char* timeStamp, amlObjectHandle_t* amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(deviceId);
    VERIFY_PARAM_NON_NULL(timeStamp);
    VERIFY_PARAM_NON_NULL(amlObjHandle);

    try
    {
        *amlObjHandle = new(std::nothrow) AMLObject(deviceId, timeStamp);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    if (!*amlObjHandle)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode CreateAMLObjectWithID(const char* deviceId, const char* timeStamp, const char* id, amlObjectHandle_t* amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(deviceId);
    VERIFY_PARAM_NON_NULL(timeStamp);
    VERIFY_PARAM_NON_NULL(id);
    VERIFY_PARAM_NON_NULL(amlObjHandle);

    try
    {
        *amlObjHandle = new(std::nothrow) AMLObject(deviceId, timeStamp, id);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    if (!*amlObjHandle)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode DestroyAMLObject(amlObjectHandle_t amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);
    delete amlObj;

    return CAML_OK;
}

CAMLErrorCode CloneAMLObject(amlObjectHandle_t origin, amlObjectHandle_t* clone)
{
    VERIFY_PARAM_NON_NULL(origin);
    VERIFY_PARAM_NON_NULL(clone);

    AMLObject* amlOrigin = static_cast<AMLObject*>(origin);

    try
    {
        *clone = new(std::nothrow) AMLObject(*amlOrigin);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    if (!*clone)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode AMLObject_AddData(amlObjectHandle_t amlObjHandle, const char* name, const amlDataHandle_t amlDataHandle)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(name);
    VERIFY_PARAM_NON_NULL(amlDataHandle);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);
    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    try
    {
        amlObj->addData(name, *amldata);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLObject_GetData(amlObjectHandle_t amlObjHandle, const char* name, amlDataHandle_t* amlDataHandle)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(name);
    VERIFY_PARAM_NON_NULL(amlDataHandle);

    try
    {
        const AMLData& amlData = static_cast<AMLObject*>(amlObjHandle)->getData(name);
        *amlDataHandle = static_cast<amlDataHandle_t>(const_cast<AMLData*>(&amlData));
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLObject_GetDataNames(amlObjectHandle_t amlObjHandle, char*** names, size_t* namesSize)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(names);
    VERIFY_PARAM_NON_NULL(namesSize);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);
    vector<string> strvec = amlObj->getDataNames();
    char** strarr = nullptr;

    try
    {
        strarr = ConvertVectorToCharStrArr(strvec);
        if (nullptr == strarr)
        {
            return CAML_NO_MEMORY;;
        }
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    *names = strarr;
    *namesSize = strvec.size();

    return CAML_OK;
}

CAMLErrorCode AMLObject_GetDeviceId(amlObjectHandle_t amlObjHandle, char** deviceId)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(deviceId);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);

    string deviceIdStr = amlObj->getDeviceId();

    try
    {
        *deviceId = ConvertStringToCharStr(deviceIdStr);
        if (nullptr == *deviceId)
        {
            return CAML_NO_MEMORY;
        }
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLObject_GetTimeStamp(amlObjectHandle_t amlObjHandle, char** timeStamp)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(timeStamp);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);

    string timeStampStr = amlObj->getTimeStamp();

    try
    {
        *timeStamp = ConvertStringToCharStr(timeStampStr);
        if (nullptr == *timeStamp)
        {
            return CAML_NO_MEMORY;
        }
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLObject_GetId(amlObjectHandle_t amlObjHandle, char** id)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(id);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);

    string idStr = amlObj->getId();

    try
    {
        *id = ConvertStringToCharStr(idStr);
        if (nullptr == *id)
        {
            return CAML_NO_MEMORY;
        }
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}