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
#include <string.h>
#include <vector>

#include "AMLInterface.h"
#include "AMLException.h"

#include "camlinterface.h"
#include "camlerrorcodes.h"
#include "camlutils.h"

using namespace std;
using namespace AML;

CAMLErrorCode CreateAMLData(amlDataHandle_t* amlDataHandle)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);

    *amlDataHandle = new(std::nothrow) AMLData();
    if (!*amlDataHandle)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode DestroyAMLData(amlDataHandle_t amlDataHandle)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    delete amldata;

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueStr(amlDataHandle_t amlDataHandle, const char* key, const char* value)
{   
    VERIFY_PARAM_NON_NULL(amlDataHandle);

    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    string keyStr(key, strlen(key));
    string valueStr(value, strlen(value));

    try
    {
       amldata->setValue(keyStr, valueStr);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueStrArr(amlDataHandle_t amlDataHandle, const char* key, const char** value, const size_t valueSize)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    string keyStr(key, strlen(key));
    vector<string> valueStrArr;

    for (size_t i = 0; i< valueSize; i++)
    {
        string valueStr(value[i], strlen(value[i]));
        valueStrArr.push_back(valueStr);
    }

    try
    {
       amldata->setValue(keyStr, valueStrArr);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, const amlDataHandle_t value)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    string keyStr(key, strlen(key));
    AMLData* amlData = static_cast<AMLData*>(value);

    try
    {
        amldata->setValue(keyStr, *amlData);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueStr(amlDataHandle_t amlDataHandle, const char* key, char** value)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    string keyStr(key, strlen(key));

    try
    {
        string str = amldata->getValueToStr(keyStr);
        *value = ConvertStringToCharStr(str);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueStrArr(amlDataHandle_t amlDataHandle, const char* key, char*** value, size_t* valueSize)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);
    VERIFY_PARAM_NON_NULL(valueSize);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    string keyStr(key, strlen(key));
    char** strarr = nullptr;
    vector<string> valueStrArr;

    try
    {
        valueStrArr = amldata->getValueToStrArr(keyStr);
        strarr = ConvertVectorToCharStrArr(valueStrArr);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    *valueSize = valueStrArr.size();
    *value = strarr;

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, amlDataHandle_t* value)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    string keyStr(key, strlen(key));

    try
    {
        const AMLData& amlData = amldata->getValueToAMLData(keyStr);
        *value = static_cast<amlDataHandle_t>(const_cast<AMLData*>(&amlData));
    }
    catch (const AMLException e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_GetKeys(amlDataHandle_t amlDataHandle, char*** keys, size_t* keysSize)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(keys);
    VERIFY_PARAM_NON_NULL(keysSize);

    AMLData* amlData = static_cast<AMLData*>(amlDataHandle);
    vector<string> keysVec = amlData->getKeys();
    char** strarr = NULL;

    try
    {
        strarr = ConvertVectorToCharStrArr(keysVec);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    *keysSize = keysVec.size();
    *keys = strarr;

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueType(amlDataHandle_t amlDataHandle, const char* key, CAMLValueType* type)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(type);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    string keyStr(key, strlen(key));
    AMLValueType cpptype;

    try
    {
        cpptype = amldata->getValueType(keyStr);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    switch (cpptype)
    {
        case AMLValueType::String :
            *type = AMLVALTYPE_STRING;
            break;
        case AMLValueType::StringArray :
            *type = AMLVALTYPE_STRINGARRAY;
            break;
        case AMLValueType::AMLData :
            *type = AMLVALTYPE_AMLDATA;
            break;
        default:
            break;
    }

    return CAML_OK;
}
