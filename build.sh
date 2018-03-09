###############################################################################
# Copyright 2018 Samsung Electronics All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
###############################################################################

#!/bin/bash

AML_TARGET_ARCH=x86_64


install_dependencies() {

    if [ -d "./dependencies" ] ; then
        echo "dependencies folder exists"
    else
        mkdir dependencies
    fi

    cd ./dependencies

    if [ -d "./datamodel-aml-c" ] ; then
        echo "datamodel-aml-c already exists"
    else
        #clone datamodel-aml-cpp
        git clone git@github.sec.samsung.net:RS7-EdgeComputing/datamodel-aml-c.git
    fi

    cd ./datamodel-aml-c
    git fetch origin
    #git reset --hard origin/master

    # Build datamodel-aml-cpp
    echo -e "${GREEN}Installing datamodel-aml-c library${NO_COLOUR}"
    ./build.sh
    if [ $? -ne 0 ]; then 
        echo -e "\033[31m"Build failed"\033[0m" 
        exit 1 
    fi
    echo -e "${GREEN}Installation of datamodel-aml-c library${NO_COLOUR}"
}

function build(){
    scons TARGET_OS=linux TARGET_ARCH=${AML_TARGET_ARCH}
    if [ $? -ne 0 ]; then 
        echo -e "\033[31m"Build failed"\033[0m" 
        exit 1 
    fi
}

install_dependencies
echo -e "Building AML DataModel library("${AML_TARGET_ARCH}").."
build
echo -e "Done building AML DataModel library("${AML_TARGET_ARCH}")"

exit 0
