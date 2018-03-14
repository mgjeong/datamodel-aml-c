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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "camlinterface.h"
#include "camlerrorcodes.h"

// helper methods
void freeCharArr(char** str, size_t size);
void printAMLData(amlDataHandle_t amlData, int depth);
void printAMLObject(amlObjectHandle_t amlObj);

// Example Data
/*
    Raw Data1 (name : "Model")
    {
        "ctname": "Model_107.113.97.248",
        "con": "SR-P7-970"
    }

    Raw Data2 (name : "Sample")
    {
        "info": {
            "id": "f437da3b",
            "axis": {
                "x": "20",
                "y": "110"
                "z": "80"
            }
        },
        "appendix": [
            "935",
            "52303",
            "1442"
        ]
    }
*/

int main() {
    // create "Model" data
    amlDataHandle_t model;
    CreateAMLData(&model);

    AMLData_SetValueStr(model, "ctname", "Model_107.113.97.248");
    AMLData_SetValueStr(model, "con", "SR-P7-970");

    // create "Sample" data
    amlDataHandle_t axis;
    CreateAMLData(&axis);
    AMLData_SetValueStr(axis, "x", "20");
    AMLData_SetValueStr(axis, "y", "110");
    AMLData_SetValueStr(axis, "z", "80");

    amlDataHandle_t info;
    CreateAMLData(&info);
    AMLData_SetValueStr(info, "id", "f437da3b");
    AMLData_SetValueAMLData(info, "axis", axis);

    amlDataHandle_t sample;
    CreateAMLData(&sample);
    AMLData_SetValueAMLData(sample, "info", info);
    const char* appendix[3] = {"935", "52303", "1442"};
    AMLData_SetValueStrArr(sample, "appendix", appendix, 3);


    // set datas to object
    amlObjectHandle_t object;
    CreateAMLObject("Robot0001", "123456789", &object);
    AMLObject_AddData(object, "Model", model);
    AMLObject_AddData(object, "Sample", sample);


    // print object
    printAMLObject(object);
}

void freeCharArr(char** str, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        free(str[i]);
    }
    free(str);
}

void printAMLData(amlDataHandle_t amlData, int depth)
{
    char* indent = (char*)malloc(sizeof(char)*100);
    strncpy(indent, "", 1);
    for (int i = 0; i < depth; i++) strcat(indent, "    ");

    printf("%s{\n", indent);

    char** keys = NULL;
    size_t size = 0;
    AMLData_GetKeys(amlData, &keys, &size);

    for (size_t i = 0; i < size; i++)
    {
        printf("%s    \"%s\" : ", indent, keys[i]);

        CAMLValueType valType = AMLVALTYPE_STRING;
        AMLData_GetValueType(amlData, keys[i], &valType);
        if (AMLVALTYPE_STRING == valType)
        {
            char* valStr;
            AMLData_GetValueStr(amlData, keys[i], &valStr);
            printf("%s", valStr);

            free(valStr);
        }
        else if (AMLVALTYPE_STRINGARRAY == valType)
        {
            char** valStrArr;
            size_t arrsize;
            AMLData_GetValueStrArr(amlData, keys[i], &valStrArr, &arrsize);
            printf("[");
            for (size_t j = 0; j < arrsize; j++)
            {
                printf("%s", valStrArr[j]);
                if (j != arrsize - 1) printf(", ");
            }
            printf("]");

            freeCharArr(valStrArr, arrsize);
        }
        else if (AMLVALTYPE_AMLDATA == valType)
        {
            amlDataHandle_t valAMLData;
            AMLData_GetValueAMLData(amlData, keys[i], &valAMLData);
            printf("\n");
            printAMLData(valAMLData, depth + 1);
        }

        if (i != size - 1)  printf(",");
        printf("\n");
    }
    printf("%s}", indent);

    free(indent);
    freeCharArr(keys, size);
}

void printAMLObject(amlObjectHandle_t amlObj)
{
    char* deviceId, *timeStamp, *id;
    AMLObject_GetDeviceId(amlObj, &deviceId);
    AMLObject_GetTimeStamp(amlObj, &timeStamp);
    AMLObject_GetId(amlObj, &id);
    
    printf("{\n");
    printf("    \"device\" : %s,\n", deviceId);
    printf("    \"timeStamp\" : %s,\n", timeStamp);
    printf("    \"id\" : %s,\n", id);

    free(deviceId);
    free(timeStamp);
    free(id);

    char** dataNames;
    size_t size;
    AMLObject_GetDataNames(amlObj, &dataNames, &size);

    for (size_t i = 0; i < size; i++)
    {
        amlDataHandle_t data;
        AMLObject_GetData(amlObj, dataNames[i], &data);

        printf("    \"%s\" : \n", dataNames[i]);
        printAMLData(data, 1);

        if (i != size - 1) printf(",\n");
    }

    printf("\n}\n");
}