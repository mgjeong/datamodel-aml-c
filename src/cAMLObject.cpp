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

#include "cAMLUtils.h"
#include "cAMLInterface.h"
#include "cAMLErrorcodes.h"

using namespace std;

CAMLErrorCode CreateAMLObject(const char* deviceId, const char* timeStamp, amlObjectHandle_t* amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(deviceId);
    VERIFY_PARAM_NON_NULL(timeStamp);

    *amlObjHandle = new(std::nothrow) AMLObject(deviceId, timeStamp);
    if (!amlObjHandle)
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

    *amlObjHandle = new(std::nothrow) AMLObject(deviceId, timeStamp);
    if (!amlObjHandle)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode DestoryAMLObject(amlObjectHandle_t* amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);

    AMLObject* amlObj = static_cast<AMLObject*>(*amlObjHandle);
    delete amlObj;
    *amlObjHandle = NULL;

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
        return CAML_KEY_ALREADY_EXIST;
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
        AMLData* amlData = static_cast<AMLObject*>(amlObjHandle)->getData(name);
        *amlDataHandle = static_cast<amlDataHandle_t>(amlData);
    }
    catch (const AMLException& e)
    {
        return CAML_KEY_NOT_EXIST;
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
    }
    catch(const AMLException& e)
    {
        return CAML_NO_MEMORY;
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
    
    if(deviceIdStr.empty())
    {
        return CAML_INVALID_DATA;
    }

    try
    {
        *deviceId = ConvertStringToCharStr(deviceIdStr);
    }
    catch(const AMLException& e)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode AMLObject_GetTimeStamp(amlObjectHandle_t amlObjHandle, char** timeStamp)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(timeStamp);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);

    string timeStampStr = amlObj->getTimeStamp();
    if(timeStampStr.empty())
    {
        return CAML_INVALID_DATA;
    }

    try
    {
        *timeStamp = ConvertStringToCharStr(timeStampStr);
    }
    catch(const AMLException& e)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode AMLObject_GetId(amlObjectHandle_t amlObjHandle, char** id)
{
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(id);

    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);

    string idStr = amlObj->getId();
    if(idStr.empty())
    {
        return CAML_INVALID_DATA;
    }

    try
    {
        *id = ConvertStringToCharStr(idStr);
    }
    catch(const AMLException& e)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}