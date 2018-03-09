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
#include "cAMLInterface.h"
#include "AMLException.h"
#include "AMLUtils.h"

using namespace std;

/*
 * "id" is automatically created using "deviceId" and "timeStamp".
 * e.g.) "deviceId" : "Robot", "timeStamp" : "001" -> "id" : "Robot_001"
 */
AMLObject::AMLObject(const std::string& deviceId, const std::string& timeStamp)
 : m_deviceId(deviceId), m_timeStamp(timeStamp), m_id(deviceId + "_" + timeStamp)
{
}

AMLObject::AMLObject(const std::string& deviceId, const std::string& timeStamp, const std::string& id)
 : m_deviceId(deviceId), m_timeStamp(timeStamp), m_id(id)
{
}

AMLObject::~AMLObject(void)
{
}

void AMLObject::addData(const std::string& name, const AMLData& data)
{
    // Try to insert a new element into the map and if the key already exists, throw an exeption.
    if (!m_amlDatas.insert(make_pair(name, data)).second)
    {
        throw AMLException(Exception::OBJECT_KEY_DUP);
    }
}

AMLData AMLObject::getData(const std::string& name) const
{
    map<string, AMLData>::iterator iter = m_amlDatas.find(name);
    if (iter == m_amlDatas.end())
    {
        // The name does not exist.
        throw AMLException(Exception::OBJECT_INVALID_KEY);
    }

    return iter->second;
}

vector<string> AMLObject::getDataNames() const
{
    vector<string> dataNames;
    for (auto const& iter : m_amlDatas)
    {
        dataNames.push_back(iter.first);
    }

    return dataNames;
}

std::string AMLObject::getDeviceId() const
{
    return m_deviceId;
}

std::string AMLObject::getTimeStamp() const
{
    return m_timeStamp;
}

std::string AMLObject::getId() const
{
    return m_id;
}

//for C Wrapping

AML_EXPORT amlObjectHandle_t CreateAMLObject(const char* deviceId, const char* timeStamp)
{
    AMLObject* amlobject = new(std::nothrow) AMLObject(deviceId, timeStamp);
    if(!amlobject)
    {
        //TODO : throw null check
    }
    return amlobject;
}
AML_EXPORT amlObjectHandle_t CreateAMLObjectWithID(const char* deviceId, const char* timeStamp, const char* id)
{
    AMLObject* amlobject = new(std::nothrow) AMLObject(deviceId, timeStamp, id);
    if(!amlobject)
    {
        //TODO : throw null check
    }
    return amlobject;
}
AML_EXPORT AMLResult DestoryAMLObject(amlObjectHandle_t amlObjHandle)
{
    if(!amlObjHandle) 
    {
        //TODO : throw null check
    }
    AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    delete amlobject;
    amlObjHandle = NULL;

    return AML_RESULT_OK;    
}
AML_EXPORT AMLResult AMLObject_AddData(amlObjectHandle_t amlObjHandle, const char* name, const amlDataHandle_t amlDataHandle)
{
    AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    AMLData* amldata = static_cast<AMLData*>(amlDataHandle);
    amlobject->addData(name, *amldata);

    return AML_RESULT_OK;
}
AML_EXPORT AMLResult AMLObject_GetData(amlObjectHandle_t amlObjHandle, const char* name, amlDataHandle_t* amlDataHandle)
{
    AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    AMLData* amldata = static_cast<AMLData*>(*amlDataHandle);

    try
    {
        *amldata = amlobject->getData(name);
    }
    catch(AMLException e) 
    {
        return AML_ERROR;   
    }

    return AML_RESULT_OK;
}
AML_EXPORT AMLResult AMLObject_GetDataNames(amlObjectHandle_t amlObjHandle, char*** names, size_t* namesSize)
{
    AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    vector<string> strvec = amlobject->getDataNames();

    char** strarr = vectorConverter(strvec);
    size_t arrsize = strvec.size();

    names = &strarr;
    namesSize = &arrsize;

    return AML_RESULT_OK;
}
AML_EXPORT AMLResult AMLObject_GetDeviceId(amlObjectHandle_t amlObjHandle, char** deviceId)
{
    AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);
    
    string str = amlobject->getDeviceId();

    *deviceId = stringConverter(str);

    return AML_RESULT_OK;
}
AML_EXPORT AMLResult AMLObject_GetTimeStamp(amlObjectHandle_t amlObjHandle, char** timeStamp)
{
    AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);

    string str = amlobject->getTimeStamp();

    *timeStamp = stringConverter(str);
    
    return AML_RESULT_OK;
}
AML_EXPORT AMLResult AMLObject_GetId(amlObjectHandle_t amlObjHandle, char** id)
{
    AMLObject* amlobject = static_cast<AMLObject*>(amlObjHandle);

    string str = amlobject->getId();

    *id = stringConverter(str);

    return AML_RESULT_OK;
}