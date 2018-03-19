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

#ifndef C_AML_REPRESENTATION_H_
#define C_AML_REPRESENTATION_H_

#include "camlinterface.h"
#include "camlerrorcodes.h"

#define AML_EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Representation handle
 */
typedef void * representation_t;


AML_EXPORT CAMLErrorCode CreateRepresentation(representation_t* repHandle, const char* filePath);
AML_EXPORT CAMLErrorCode DestroyRepresentation(representation_t repHandle);
AML_EXPORT CAMLErrorCode Representation_GetRepId(representation_t repHandle, char** repId);
AML_EXPORT CAMLErrorCode Representation_GetConfigInfo(representation_t repHandle, amlObjectHandle_t* amlObjHandle);


#ifdef __cplusplus
}
#endif

#endif // C_AML_REPRESENTATION_H_