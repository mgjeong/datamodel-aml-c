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

#include "cAMLErrorcodes.h"
#include "cAMLInterface.h"
#include "cAMLUtils.h"

#include "AMLInterface.h"
#include "AMLException.h"

using namespace std;

CAMLErrorCode CreateAMLData(amlDataHandle_t* amlDataHandle)
{
    *amlDataHandle = new(std::nothrow) AMLData();
    if(!amlDataHandle)
    {
        return CAML_NO_MEMORY;
    }

    return CAML_OK;
}

CAMLErrorCode DestoryAMLData(amlDataHandle_t* amlDataHandle)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);

    AMLData* amldata = static_cast<AMLData*>(*amlDataHandle);
    delete amldata;
    *amlDataHandle = NULL;

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueStr(amlDataHandle_t amlDataHandle, const char* key, const char* value)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    
    string strKey(key, strlen(key));
    string strValue(value, strlen(value));
    
    try
    {
       amldata->setValue(strKey, strValue);
    }
    catch(const AMLException& e)
    {
        return CAML_KEY_ALREADY_EXIST;
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueStrArr(amlDataHandle_t amlDataHandle, const char* key, const char** value, const size_t valueSize)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    string strKey(key, strlen(key));
    vector<string> strvec;
    for(size_t i = 0; i< valueSize; i++)
    {
        string strValue(value[i], strlen(value[i]));
        strvec.push_back(strValue);
    }

    try
    {
       amldata->setValue(strKey, strvec);
    }
    catch(const AMLException& e)
    {
        return CAML_KEY_ALREADY_EXIST;
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, const amlDataHandle_t value)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);

    string strKey(key, strlen(key));

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    AMLData* amlData = static_cast<AMLData*>(value);

    try
    {
       amldata->setValue(strKey, *amlData);
    }
    catch(const AMLException& e)
    {
        return CAML_KEY_ALREADY_EXIST;
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueStr(amlDataHandle_t amlDataHandle, const char* key, char** value)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);
    
    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    string strKey(key, strlen(key));
    
    try
    {
        string str = amldata->getValueToStr(strKey);
        *value = ConvertStringToCharStr(str);
    }
    catch(const AMLException& e)
    {
        if(!value)
        {
            return CAML_NO_MEMORY;
        }
        return CAML_KEY_NOT_EXIST;
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

    string strKey(key, strlen(key));
    char** strarr = nullptr;
    vector<string> strvec;
    
    try
    {
        strvec = amldata->getValueToStrArr(strKey);
        strarr = ConvertVectorToCharStrArr(strvec);
    }
    catch(const AMLException& e)
    {
        if(!strarr)
        {
            return CAML_NO_MEMORY;
        }

        return CAML_KEY_NOT_EXIST;
    }

    *valueSize = strvec.size();

    *value = strarr;
        
    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, amlDataHandle_t* value)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(value);
    
    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    AMLData* amlData = nullptr;
    string strKey(key, strlen(key));

    try
    {
        *amlData = amldata->getValueToAMLData(strKey);
        *value = static_cast<amlDataHandle_t>(amlData);
    }
    catch(const AMLException e)
    {
        return CAML_KEY_NOT_EXIST;
    }

    return CAML_OK;
}

CAMLErrorCode AMLData_GetKeys(amlDataHandle_t amlDataHandle, char*** keys, size_t* keysSize)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(keys);
    VERIFY_PARAM_NON_NULL(keysSize);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    vector<string> strvec = amldata->getKeys();
    char** strarr = nullptr;

    try
    {
        strarr = ConvertVectorToCharStrArr(strvec);
    }
    catch(const AMLException& e)
    {
        return CAML_NO_MEMORY;
    }

    *keysSize = strvec.size();

    *keys = strarr;

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueType(amlDataHandle_t amlDataHandle, const char* key, AMLValueType_c* type)
{
    VERIFY_PARAM_NON_NULL(amlDataHandle);
    VERIFY_PARAM_NON_NULL(key);
    VERIFY_PARAM_NON_NULL(type);

    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    string strKey(key, strlen(key));

    try
    {
        *type = AMLValueType_c(amldata->getValueType(strKey));
    }
    catch(const AMLException& e)
    {
        return CAML_KEY_NOT_EXIST;
    }

    return CAML_OK;
}
