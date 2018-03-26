# DataModel AML library (c)




datamodel-aml-c is a wrapper library which is written on the top of datamodel-aml-cpp, that provides the way to present raw data(key/value based) to AutomationML(AML) standard format.
 - Transform raw data to AML data(XML).
 - Serialization / Deserialization AML data using protobuf.


## Prerequisites ##
- SCons
  - Version : 2.3.0 or above
  - [How to install](http://scons.org/doc/2.3.0/HTML/scons-user/c95.html)

- datamodel-aml-cpp
    [Prerequisites](https://github.sec.samsung.net/RS7-EdgeComputing/datamodel-aml-cpp)

## How to build ##
1. Goto: ~/datamodel-aml-c/
2. Run the script:

   ```
   ./build.sh <options>       : Native build for x86_64
   ./build_arm.sh <options>   : Native build for armhf [Raspberry pi board])
   ```
**Notes** </br>
For getting help about script option: **$ ./build.sh --help** </br>


## How to run ##

### Prerequisites ###
 Built datamodel-aml-c library

### Sample ###
1. Goto: ~/datamodel-aml-c/out/linux/{ARCH}/{MODE}/samples/
2. export LD_LIBRARY_PATH=../
3. Run the sample:
    ```
     ./sample
    ```

## Usage guide for datamodel-aml-c library (for microservices)

1. The microservice which wants to use aml APIs has to link following libraries:</br></br>
   **(A) If microservice wants to link aml dynamically following are the libraries it needs to link:**</br>
        - aml.so</br>
        - caml.so</br>
   **(B) If microservice wants to link aml statically following are the libraries it needs to link:**</br>
        - aml.a</br>
        - caml.a</br>
2. Reference ezmq library APIs : [docs/docs/html/index.html](docs/docs/html/index.html)


</br></br>