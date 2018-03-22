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


/**
 * @brief       Create an instance of Representation.
 * @param       filePath        [in] path of an AML file that contains data model information.
 * @param       repHandle       [out] handle of created Representation.
 * @retval      #CAML_OK                Successful.
 * @retval      #CAML_INVALID_PARAM     Invalid parameter.
 * @retval      #CAML_NO_MEMORY         Failed to alloc memory.
 * @note        Representation instance will be allocated, so it should be deleted after use.
 *              To destroy an instance, use DestroyRepresentation().
 */
AML_EXPORT CAMLErrorCode CreateRepresentation(const char* filePath,
                                              representation_t* repHandle);

/**
 * @brief       Destroy an instance of Representation.
 * @param       repHandle       [in] handle of Representation that will be destroyed.
 * @retval      #CAML_OK                Successful.
 * @retval      #CAML_INVALID_PARAM     Invalid parameter.
 */
AML_EXPORT CAMLErrorCode DestroyRepresentation(representation_t repHandle);

/**
 * @brief       This function returns AutomationML SystemUnitClassLib's unique ID.
 * @param       repHandle       [in] handle of Representation.
 * @param       repId           [out] ID of Representation.
 * @retval      #CAML_OK                Successful.
 * @retval      #CAML_INVALID_PARAM     Invalid parameter.
 * @retval      #CAML_NO_MEMORY         Failed to alloc memory.
 * @note        Characters will be allocated to 'repId', so it should be freed after use. (See the below example)
 *              ex) free(repId);
 */
AML_EXPORT CAMLErrorCode Representation_GetRepId(representation_t repHandle,
                                                 char** repId);

/**
 * @brief       This function returns AMLObject that contains configuration data which is present in RoleClassLib.
 * @param       repHandle       [in] handle of Representation.
 * @param       amlObjHandle    [out] handle of AMLObject.
 * @retval      #CAML_OK                 Successful.
 * @retval      #CAML_INVALID_PARAM      Invalid parameter.
 * @retval      #CAML_INVALID_AML_SCHEMA The AML, which is set by CreateRepresentation, has a invalid schema.
 * @note        AMLObject instance will be allocated, so it should be deleted after use.
 *              To destroy an instance, use DestroyAMLObject().
 * @see         DestroyAMLObject
 */
AML_EXPORT CAMLErrorCode Representation_GetConfigInfo(representation_t repHandle,
                                                      amlObjectHandle_t* amlObjHandle);


#ifdef __cplusplus
}
#endif

#endif // C_AML_REPRESENTATION_H_