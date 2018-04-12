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

#include <iostream>
#include <string>
#include <fstream>

#include "camlinterface.h"
#include "camlerrorcodes.h"
#include "gtest/gtest.h"

using namespace std;

namespace camlinterfacetest
{
	bool isEqual(const char* str1, const char* str2)
    {
        return !strcmp(str1, str2);
    }

	bool isEqualArr(const char** strArr1, size_t size1, const char** strArr2, size_t size2)
    {
        if (size1 != size2)	return false;
        
        for(size_t i = 0; i < size2; i++)
        {
        	if(true == strcmp(strArr1[i], strArr2[i])) return false;
        }

        return true;
    }

    bool isEqualAMLData(amlDataHandle_t data1, amlDataHandle_t data2)
    {
        char** keys1 = NULL;
        char** keys2 = NULL;
        size_t size1, size2;

        AMLData_GetKeys(data1, &keys1, &size1);
        AMLData_GetKeys(data2, &keys2, &size2);

        if (false == isEqualArr((const char**)keys1, size1, (const char**)keys2, size2)) return false;

        for (size_t i = 0; i < size1; i++)
        {
        	char* key = keys1[i];

        	CAMLValueType type1, type2;
        	AMLData_GetValueType(data1, key, &type1);
        	AMLData_GetValueType(data2, key, &type2);

            if (type1 != type2)     return false;

            if (AMLVALTYPE_STRING == type1)
            {
            	char* ret1 = NULL;
            	char* ret2 = NULL;
                AMLData_GetValueStr(data1, key, &ret1);
                AMLData_GetValueStr(data2, key, &ret2);
                
                if (false == isEqual(ret1, ret2)) return false;
            }
            else if (AMLVALTYPE_STRINGARRAY == type1)
            {
            	char** ret1 = NULL;
            	char** ret2 = NULL;
            	size_t ret_size1, ret_size2;
                AMLData_GetValueStrArr(data1, key, &ret1, &ret_size1);
                AMLData_GetValueStrArr(data2, key, &ret2, &ret_size2);

                if (false == isEqualArr((const char**)ret1, ret_size1, (const char**)ret2, ret_size2)) return false;
            }
            else if (AMLVALTYPE_AMLDATA == type1)
            {
            	amlDataHandle_t ret1, ret2;
                AMLData_GetValueAMLData(data1, key, &ret1);
                AMLData_GetValueAMLData(data2, key, &ret2);
                
                if (false == isEqualAMLData(ret1, ret2)) return false;
            }
        }
        return true;
    }

	// Test
	TEST(AMLData_CreateTest, Valid)
	{
		amlDataHandle_t amlData;

		EXPECT_EQ(CreateAMLData(&amlData), CAML_OK);
	}

	TEST(AMLData_SetValueStrTest, Valid)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value = "value";
		
		EXPECT_EQ(AMLData_SetValueStr(amlData, key, value), CAML_OK);
	}

	TEST(AMLData_SetValueStrTest, Invalid_DuplicatedKey)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value = "value";
		
		EXPECT_EQ(AMLData_SetValueStr(amlData, key, value), CAML_OK);
        EXPECT_EQ(AMLData_SetValueStr(amlData, key, value), CAML_KEY_ALREADY_EXIST);
	}

	TEST(AMLData_SetValueStrArrTest, Valid)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value[2] = {"value1", "value2"};
	    
		EXPECT_EQ(AMLData_SetValueStrArr(amlData, key, value, 2), CAML_OK);
	}

	TEST(AMLData_SetValueStrArrTest, Invalid_DuplicatedKey)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value[2] = {"value1", "value2"};
	    
		EXPECT_EQ(AMLData_SetValueStrArr(amlData, key, value, 2), CAML_OK);
        EXPECT_EQ(AMLData_SetValueStrArr(amlData, key, value, 2), CAML_KEY_ALREADY_EXIST);	
	}

	TEST(AMLData_SetValueAMLDataTest, Valid)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		amlDataHandle_t value;
		CreateAMLData(&value);
		
		EXPECT_EQ(AMLData_SetValueAMLData(amlData, key, value), CAML_OK);
	}

	TEST(AMLData_SetValueAMLDataTest, Invalid_DuplicatedKey)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		amlDataHandle_t value;
		CreateAMLData(&value);
		
		EXPECT_EQ(AMLData_SetValueAMLData(amlData, key, value), CAML_OK);
        EXPECT_EQ(AMLData_SetValueAMLData(amlData, key, value), CAML_KEY_ALREADY_EXIST);
	}

	TEST(AMLData_GetValueStrTest, Valid)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value = "value";
		
		EXPECT_EQ(AMLData_SetValueStr(amlData, key, value), CAML_OK);

		char* ret;
		EXPECT_EQ(AMLData_GetValueStr(amlData, key, &ret), CAML_OK);
		EXPECT_TRUE(isEqual(value, ret));
	}

	TEST(AMLData_GetValueStrTest, InvalidGetterType)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value[2] = {"value1", "value2"};
		
		EXPECT_EQ(AMLData_SetValueStrArr(amlData, key, value, 2), CAML_OK);

		char* ret;
		EXPECT_EQ(AMLData_GetValueStr(amlData, key, &ret), CAML_WRONG_GETTER_TYPE);
	}

	TEST(AMLData_GetValueStrArrTest, Valid)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value[2] = {"value1", "value2"};
	    
	    EXPECT_EQ(AMLData_SetValueStrArr(amlData, key, value, 2), CAML_OK);

		char** ret;
		size_t size;
		EXPECT_EQ(AMLData_GetValueStrArr(amlData, key, &ret, &size), CAML_OK);
		EXPECT_TRUE(isEqualArr(value, 2, (const char**)ret, size));
	}
	
	TEST(AMLData_GetValueStrArrTest, InvalidGetterType)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value = "value";
	    
	    EXPECT_EQ(AMLData_SetValueStr(amlData, key, value), CAML_OK);

		char** ret;
		size_t size;
		EXPECT_EQ(AMLData_GetValueStrArr(amlData, key, &ret, &size), CAML_WRONG_GETTER_TYPE);
	}

	TEST(AMLData_GetValueAMLDataTest, Valid)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		amlDataHandle_t value;
		CreateAMLData(&value);
		
		EXPECT_EQ(AMLData_SetValueAMLData(amlData, key, value), CAML_OK);

		amlDataHandle_t ret;
		EXPECT_EQ(AMLData_GetValueAMLData(amlData, key, &ret), CAML_OK);
		EXPECT_TRUE(isEqualAMLData(value, ret));
	}

	TEST(AMLData_GetValueAMLDataTest, InvalidGetterType)
	{
		amlDataHandle_t amlData;
		CreateAMLData(&amlData);

		const char* key = "key";
		const char* value = "value";
		
		EXPECT_EQ(AMLData_SetValueStr(amlData, key, value), CAML_OK);

		amlDataHandle_t ret;
		EXPECT_EQ(AMLData_GetValueAMLData(amlData, key, &ret), CAML_WRONG_GETTER_TYPE);
	}

}