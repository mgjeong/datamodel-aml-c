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
#include <cstring>
#include <vector>

#include "camlutils.h"

using namespace std;

char* ConvertStringToCharStr(std::string str)
{
    char* cstr = new char[str.size() + 1];
    strncpy(cstr, str.c_str(), str.size());
    cstr[str.size()] = '\0';

    return cstr;
}

char** ConvertVectorToCharStrArr(std::vector<std::string>& list)
{
    unsigned long size = list.size();
    char ** cstr = new char*[size];

    for(unsigned long i = 0; i < size; i++)
    {
        cstr[i] = ConvertStringToCharStr(list[i]);
    }

    return cstr;
}

CAMLErrorCode ExceptionCodeToErrorCode(AMLResult result)
{
    switch (result)
    {
        case AML_INVALID_PARAM :
            return CAML_INVALID_PARAM;
        case AML_INVALID_FILE_PATH :
            return CAML_INVALID_FILE_PATH;
        case AML_INVALID_SCHEMA :
            return CAML_INVALID_AML_SCHEMA;
        case AML_INVALID_XML_STR :
            return CAML_INVALID_XML_STRING;
        case AML_NO_MEMORY :
            return CAML_NO_MEMORY;
        case AML_KEY_NOT_EXIST :
            return CAML_KEY_NOT_EXIST;
        case AML_KEY_ALREADY_EXIST :
            return CAML_KEY_ALREADY_EXIST;
        case AML_INVALID_DATA_TYPE :
            return CAML_INVALID_DATA_TYPE;

        case AML_INVALID_AMLDATA_NAME : //@TODO
        case AML_NOT_IMPL :
        case AML_KEY_VALUE_NOT_MATCH :
        case AML_ERROR :

        default : // AML_RESULT_OK
            return CAML_OK;
    }
}