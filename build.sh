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

PROJECT_ROOT=$(pwd)
AML_TARGET_ARCH="$(uname -m)"


install_dependencies() {

    if [ -d "./dependencies" ] ; then
        echo "dependencies folder exists"
    else
        mkdir dependencies
    fi

    cd ./dependencies

    if [ -d "./datamodel-aml-cpp" ] ; then
        echo "datamodel-aml-cpp already exists"
    else
        #clone datamodel-aml-cpp
        git clone git@github.sec.samsung.net:RS7-EdgeComputing/datamodel-aml-cpp.git
    fi

    cd ./datamodel-aml-cpp
    git fetch origin
#git checkout alpha_noboost
    #git reset --hard origin/master

    # Build datamodel-aml-cpp
    echo -e "Installing datamodel-aml-cpp library"
    ./build.sh
    if [ $? -ne 0 ]; then 
        echo -e "\033[31m"Build failed"\033[0m" 
        exit 1 
    fi
    echo -e "Installation of datamodel-aml-cpp library"
}

function build(){
    cd ${PROJECT_ROOT}
    scons TARGET_OS=linux TARGET_ARCH=${AML_TARGET_ARCH}
    if [ $? -ne 0 ]; then 
        echo -e "\033[31m"Build failed"\033[0m" 
        exit 1 
    fi
}

install_dependencies
echo -e "Building C AML DataModel library("${AML_TARGET_ARCH}").."
build
echo -e "Done building C AML DataModel library("${AML_TARGET_ARCH}")"

exit 0
