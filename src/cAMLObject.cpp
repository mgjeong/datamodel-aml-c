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


AML_EXPORT amlObjectHandle_t CreateAMLObject(const char* deviceId, const char* timeStamp)
{
    AMLObject* amlobject = new(std::nothrow) AMLObject(deviceId, timeStamp);
    if(!amlobject)
    {
        //TODO : throw null check
    }
    return static_cast<amlObjectHandle_t>(amlobject); 
}

AML_EXPORT amlObjectHandle_t CreateAMLObjectWithID(const char* deviceId, const char* timeStamp, const char* id)
{
    // AMLObject* amlobject = new(std::nothrow) AMLObject(deviceId, timeStamp, id);
    // if(!amlobject)
    // {
    //     //TODO : throw null check
    // }
    // return amlobject;

    return NULL;
}

AML_EXPORT CAMLErrorCode DestoryAMLObject(amlObjectHandle_t amlObjHandle)
{
    // if(!amlObjHandle) 
    // {
    //     //TODO : throw null check
    // }
    // AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    // delete amlobject;
    // amlObjHandle = NULL;

    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLObject_AddData(amlObjectHandle_t amlObjHandle, const char* name, const amlDataHandle_t amlDataHandle)
{
    // AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    // AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    // amlobject->addData(name, *amldata);

    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLObject_GetData(amlObjectHandle_t amlObjHandle, const char* name, amlDataHandle_t* amlDataHandle)
{
    // AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);

    // try
    // {
    //     *amldata = static_cast<amlDataHandle_t>amlobject->getData(name);
    // }
    // catch(AMLException e) 
    // {
    //     return CAML_ERROR;   
    // }

    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLObject_GetDataNames(amlObjectHandle_t amlObjHandle, char*** names, size_t* namesSize)
{
    // AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    // vector<string> strvec = amlobject->getDataNames();

    // char** strarr = ConvertVectorToCharStrArr(strvec);
    // *namesSize = strvec.size();

    // *names = strarr;

    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLObject_GetDeviceId(amlObjectHandle_t amlObjHandle, char** deviceId)
{
    // AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    
    // string str = amlobject->getDeviceId();

    // *deviceId = ConvertStringToCharStr(str);

    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLObject_GetTimeStamp(amlObjectHandle_t amlObjHandle, char** timeStamp)
{
    // AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);

    // string str = amlobject->getTimeStamp();

    // *timeStamp = ConvertStringToCharStr(str);
    
    return CAML_OK;
}

AML_EXPORT CAMLErrorCode AMLObject_GetId(amlObjectHandle_t amlObjHandle, char** id)
{
    // AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);

    // string str = amlobject->getId();

    // *id = ConvertStringToCharStr(str);

    return CAML_OK;
}