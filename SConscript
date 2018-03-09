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

################ AML DataModel build script ##################

import os

Import('env')

c_aml_env = env.Clone()
target_os = c_aml_env.get('TARGET_OS')
target_arch = c_aml_env.get('TARGET_ARCH')

if c_aml_env.get('RELEASE'):
    c_aml_env.AppendUnique(CCFLAGS=['-Os'])
else:
    c_aml_env.AppendUnique(CCFLAGS=['-g'])

c_aml_env.AppendUnique(CPPPATH=[
        './dependencies/protocol-ezmq-cpp/extlibs/pugixml/pugixml-1.8/src',
        './dependencies/protocol-ezmq-cpp/protobuf',
        './dependencies/protocol-ezmq-cpp/include',
        './dependencies/protocol-ezmq-cpp/include/logger'
        './include'
])

if c_aml_env.get('RELEASE'):
    c_aml_env.PrependUnique(LIBS=['ezmq'], LIBPATH=[os.path.join('./dependencies/protocol-ezmq-cpp/out/linux/', target_arch, 'release')])
else:
    c_aml_env.PrependUnique(LIBS=['ezmq'], LIBPATH=[os.path.join('./dependencies/protocol-ezmq-cpp/out/linux/', target_arch, 'debug')])

c_aml_env.PrependUnique(LIBS=['protobuf'])

if target_os not in ['windows']:
    c_aml_env.AppendUnique(
        CXXFLAGS=['-O2', '-g', '-Wall', '-fPIC', '-fmessage-length=0', '-std=c++0x', '-I/usr/local/include'])

if target_os not in ['windows']:
    c_aml_env.AppendUnique(LINKFLAGS=['-Wl,--no-undefined'])

if target_os in ['linux']:
    c_aml_env.AppendUnique(LIBS=['pthread'])

if target_os in ['linux']:
    if not env.get('RELEASE'):
        c_aml_env.PrependUnique(LIBS=['gcov'])
        c_aml_env.AppendUnique(CXXFLAGS=['--coverage'])

AML_DIR = '.'
c_aml_env.AppendUnique(aml_src = [c_aml_env.Glob(os.path.join(AML_DIR, 'src', '*.cpp'))])

amlshared = c_aml_env.SharedLibrary('aml', c_aml_env.get('aml_src'))
amlstatic = c_aml_env.StaticLibrary('aml', c_aml_env.get('aml_src'))

# Go to build AML DataModel sample apps
if target_os == 'linux':
       SConscript('samples/SConscript')

# Go to build AML DataModel unit test cases
if target_os == 'linux':
    if target_arch in ['x86', 'x86_64']:
        SConscript('unittests/SConscript')