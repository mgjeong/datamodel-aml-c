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
#include <map>

#include "cAMLErrorcodes.h"
//#include "AMLInterface.h"
#include "cAMLInterface.h"
//#include "AMLException.h"

AML_EXPORT amlDataHandle_t CreateAMLData()
{
    return NULL;
}

AML_EXPORT CAMLErrorCode DestoryAMLData(amlDataHandle_t amlObjHandle)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_SetValueStr(amlDataHandle_t amlObjHandle, const char* key, const char* value)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_SetValueStrArr(amlDataHandle_t amlObjHandle, const char* key, const char** value, const size_t valueSize)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_SetValueAMLData(amlDataHandle_t amlObjHandle, const char* key, const amlDataHandle_t value)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_GetValueStr(amlDataHandle_t amlObjHandle, const char* key, char** value)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_GetValueStrArr(amlDataHandle_t amlObjHandle, const char* key, char*** value, size_t* valueSize)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_GetValueAMLData(amlDataHandle_t amlObjHandle, const char* key, amlDataHandle_t* value)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_GetKeys(amlDataHandle_t amlObjHandle, char*** keys, size_t* keysSize)
{
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLData_GetValueType(amlDataHandle_t amlObjHandle, const char* key, AMLValueType_c* type)
{
    return CAML_OK;
}
