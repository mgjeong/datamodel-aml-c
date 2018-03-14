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

#ifndef C_AML_ERRORCODES_H_
#define C_AML_ERRORCODES_H_

#define VERIFY_PARAM_NON_NULL(PARAM)        if (!PARAM){ return CAML_INVALID_PARAM; }

typedef enum
{
    CAML_OK = 0,                    /**< Success */

    CAML_INVALID_PARAM,             /**< Invalid Parameter */
    CAML_INVALID_DATA,
    CAML_INVALID_FILE_PATH,         /**< .. */
    CAML_INVALID_AML_SCHEMA,        /**< .. */
    CAML_INVALID_XML_STRING,        /**< .. */
    CAML_NO_MEMORY,                 /**< .. */
    CAML_KEY_NOT_EXIST,             /**< .. */
    CAML_KEY_ALREADY_EXIST,         /**< .. */
    CAML_INVALID_DATA_TYPE,         /**< .. */
} CAMLErrorCode;

#endif // C_AML_ERRORCODES_H_