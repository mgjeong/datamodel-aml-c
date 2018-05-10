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

#include <string.h>
#include <string>

#include "Representation.h"
#include "AMLInterface.h"
#include "AMLException.h"

#include "camlrepresentation.h"
#include "camlinterface.h"
#include "camlerrorcodes.h"
#include "camlutils.h"

using namespace std;
using namespace AML;

CAMLErrorCode CreateRepresentation(const char* filePath, representation_t* repHandle)
{
    VERIFY_PARAM_NON_NULL(filePath);
    VERIFY_PARAM_NON_NULL(repHandle);

    try
    {
        *repHandle = new(std::nothrow) Representation(filePath);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    if (!*repHandle)
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
        if(nullptr == *repId)
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
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode Representation_DataToAml(const representation_t repHandle, const amlObjectHandle_t amlObjHandle, char** amlStr)
{
    VERIFY_PARAM_NON_NULL(repHandle);
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(amlStr);

    Representation* rep = static_cast<Representation*>(repHandle);
    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);

    try
    {
        string amlString = rep->DataToAml(*amlObj);
        *amlStr = ConvertStringToCharStr(amlString);
        if(nullptr == *amlStr)
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

CAMLErrorCode Representation_AmlToData(const representation_t repHandle, const char* amlStr, amlObjectHandle_t* amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(repHandle);
    VERIFY_PARAM_NON_NULL(amlStr);
    VERIFY_PARAM_NON_NULL(amlObjHandle);

    Representation* rep = static_cast<Representation*>(repHandle);
    string amlString(amlStr, strlen(amlStr));

    try
    {
        AMLObject* amlObj = rep->AmlToData(amlString);
        *amlObjHandle = static_cast<amlObjectHandle_t>(amlObj);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode Representation_DataToByte(const representation_t repHandle, const amlObjectHandle_t amlObjHandle, uint8_t** byte, size_t* size)
{
    VERIFY_PARAM_NON_NULL(repHandle);
    VERIFY_PARAM_NON_NULL(amlObjHandle);
    VERIFY_PARAM_NON_NULL(byte);
    VERIFY_PARAM_NON_NULL(size);

    Representation* rep = static_cast<Representation*>(repHandle);
    AMLObject* amlObj = static_cast<AMLObject*>(amlObjHandle);

    try
    {
        string amlString = rep->DataToByte(*amlObj);
        char* temp = ConvertStringToCharStr(amlString);
        if(nullptr == temp)
        {
            return CAML_NO_MEMORY;
        }
        *byte = reinterpret_cast<uint8_t*>(temp);
        *size = amlString.size();
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}

CAMLErrorCode Representation_ByteToData(const representation_t repHandle, const uint8_t* byte, const size_t size, amlObjectHandle_t* amlObjHandle)
{
    VERIFY_PARAM_NON_NULL(repHandle);
    VERIFY_PARAM_NON_NULL(byte);
    VERIFY_PARAM_NON_NULL(size);
    VERIFY_PARAM_NON_NULL(amlObjHandle);

    Representation* rep = static_cast<Representation*>(repHandle);
    string byteString((char*)byte, size);

    try
    {
        AMLObject* amlObj = rep->ByteToData(byteString);
        *amlObjHandle = static_cast<amlObjectHandle_t>(amlObj);
    }
    catch (const AMLException& e)
    {
        return ExceptionCodeToErrorCode(e.code());
    }

    return CAML_OK;
}