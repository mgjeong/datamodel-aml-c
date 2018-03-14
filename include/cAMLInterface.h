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

#ifndef C_AML_INTERFACE_H_
#define C_AML_INTERFACE_H_

#include "cAMLErrorcodes.h"

#define AML_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * AMLObject handle
 */
typedef void * amlObjectHandle_t;

/**
 * AMLData handle
 */
typedef void * amlDataHandle_t;


typedef enum
{
    AMLVALTYPE_STRING = 0,
    AMLVALTYPE_STRINGARRAY,
    AMLVALTYPE_AMLDATA
} CAMLValueType;


AML_EXPORT CAMLErrorCode CreateAMLObject(const char* deviceId, const char* timeStamp, amlObjectHandle_t* amlObjHandle);
AML_EXPORT CAMLErrorCode CreateAMLObjectWithID(const char* deviceId, const char* timeStamp, const char* id, amlObjectHandle_t* amlObjHandle);
AML_EXPORT CAMLErrorCode DestoryAMLObject(amlObjectHandle_t amlObjHandle);
AML_EXPORT CAMLErrorCode AMLObject_AddData(amlObjectHandle_t amlObjHandle, const char* name, const amlDataHandle_t amlDataHandle);
AML_EXPORT CAMLErrorCode AMLObject_GetData(amlObjectHandle_t amlObjHandle, const char* name, amlDataHandle_t* amlDataHandle);
AML_EXPORT CAMLErrorCode AMLObject_GetDataNames(amlObjectHandle_t amlObjHandle, char*** names, size_t* namesSize);
AML_EXPORT CAMLErrorCode AMLObject_GetDeviceId(amlObjectHandle_t amlObjHandle, char** deviceId);
AML_EXPORT CAMLErrorCode AMLObject_GetTimeStamp(amlObjectHandle_t amlObjHandle, char** timeStamp);
AML_EXPORT CAMLErrorCode AMLObject_GetId(amlObjectHandle_t amlObjHandle, char** id);


AML_EXPORT CAMLErrorCode CreateAMLData(amlDataHandle_t* amlDataHandle);
AML_EXPORT CAMLErrorCode DestoryAMLData(amlDataHandle_t* amlDataHandle);
AML_EXPORT CAMLErrorCode AMLData_SetValueStr(amlDataHandle_t amlDataHandle, const char* key, const char* value);
AML_EXPORT CAMLErrorCode AMLData_SetValueStrArr(amlDataHandle_t amlDataHandle, const char* key, const char** value, const size_t valueSize);
AML_EXPORT CAMLErrorCode AMLData_SetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, const amlDataHandle_t value);
AML_EXPORT CAMLErrorCode AMLData_GetValueStr(amlDataHandle_t amlDataHandle, const char* key, char** value);
AML_EXPORT CAMLErrorCode AMLData_GetValueStrArr(amlDataHandle_t amlDataHandle, const char* key, char*** value, size_t* valueSize);
AML_EXPORT CAMLErrorCode AMLData_GetValueAMLData(amlDataHandle_t amlDataHandle, const char* key, amlDataHandle_t* value);
AML_EXPORT CAMLErrorCode AMLData_GetKeys(amlDataHandle_t amlDataHandle, char*** keys, size_t* keysSize);
AML_EXPORT CAMLErrorCode AMLData_GetValueType(amlDataHandle_t amlDataHandle, const char* key, CAMLValueType* type);


#ifdef __cplusplus
}
#endif

#endif // C_AML_INTERFACE_H_