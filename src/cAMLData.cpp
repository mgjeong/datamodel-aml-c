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
#include <vector>

#include "cAMLErrorcodes.h"
#include "cAMLInterface.h"

#include "AMLInterface.h"
#include "AMLException.h"

using namespace std;

CAMLErrorCode CreateAMLData(amlDataHandle_t* amlDataHandle)
{
    // AMLData* amldata = new(std::nothrow) AMLData();
    // if(!amldata)
    // {
    //     //TODO : throw null check
    // }

    // return static_cast<amlDataHandle_t>(amldata);

    return CAML_OK;
}

CAMLErrorCode DestoryAMLData(amlDataHandle_t* amlDataHandle)
{
    // if(!amlDataHandle)
    // {
    //     //TODO : throw null check
    // }
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    // delete amldata;
    // amlDataHandle = NULL;

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueStr(amlDataHandle_t amlDataHandle, const char* key, const char* value)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    
    // string strKey(key, strlen(key));
    // string strValue(value, strlen(value));
    
    // amldata->setValue(strKey, strValue);

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueStrArr(amlDataHandle_t amlDataHandle, const char* key, const char** value, const size_t valueSize)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    // string strKey(key, strlen(key));

    // vector<string> strvec;
    // for(int i = 0; i< valueSize; i++)
    // {
    //     string strValue(value[i], strlen(value[i]));
    //     strvec.insert(strValue);
    // }
    // amldata->setValue(strKey, strvec);

    return CAML_OK;
}

CAMLErrorCode AMLData_SetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, const amlDataHandle_t value)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    // string strKey(key, strlen(key));
    // AMLData* amlData = static_cast<AMLData*>(value);

    // amldata->setValue(strKey, *amlData);

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueStr(amlDataHandle_t amlDataHandle, const char* key, char** value)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    // string strKey(key, strlen(key));

    // string str = amldta->getValueToStr(strKey);
    // *value = ConvertStringToCharStr(str);

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueStrArr(amlDataHandle_t amlDataHandle, const char* key, char*** value, size_t* valueSize)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    // string strKey(key, strlen(key));

    // vector<string> strvec = amldata->getValueToStrArr(strKey);

    // char** strarr = ConvertStringToCharStrArr(strvec);
    // *valueSize = strvec.size();

    // *value = strarr;
        
    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, amlDataHandle_t* value)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    // string strKey(key, strlen(key));

    // try
    // {
    //     *value = static_cast<amlDataHandle_t>amldata->getValueToAMLData(strKey);
    // }
    // catch(AMLException e)
    // {
    //     return CAML_ERROR;
    // }

    return CAML_OK;
}

CAMLErrorCode AMLData_GetKeys(amlDataHandle_t amlDataHandle, char*** keys, size_t* keysSize)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    // vector<string> strvec = amldata->getKeys();

    // char** strarr = ConvertStringToCharStrArr(strvec);
    // *keySize = strvec.size();

    // *keys = strarr;

    return CAML_OK;
}

CAMLErrorCode AMLData_GetValueType(amlDataHandle_t amlDataHandle, const char* key, AMLValueType_c* type)
{
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);

    // string strKey(key, strlen(key));

    // *type = AMLValueType_c(amldata->getValueType(strKey));

    return CAML_OK;
}
