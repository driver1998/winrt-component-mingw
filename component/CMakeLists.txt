cmake_minimum_required(VERSION 3.5.0)
project(mingw-component VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|AMD64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcx16")
endif()

set(CMAKE_SHARED_LINKER_FLAGS "-municode -static")
set(COMPONENT_NAMESPACE MinGWComponent)

set(CSWINMD_PATH "../cswinmd/CsWinMD.exe")
set(CPPWINRT_INPUT "../references/Windows.winmd")
set(CPPWINRT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/cppwinrt")

add_custom_command(
    OUTPUT
        component.winmd
    COMMAND
        ${CSWINMD_PATH} -i component.cs -a ${COMPONENT_NAMESPACE} -o ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS
        component.cs
    COMMENT
        "Generating Metadata...")

add_custom_command(
    OUTPUT
        ${CPPWINRT_OUTPUT_DIR}/winrt/base.h
    COMMAND
        cppwinrt.exe -pch . -input ${CPPWINRT_INPUT} -output ${CPPWINRT_OUTPUT_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT
        "Generating C++/WinRT Headers...")

add_custom_command(
    OUTPUT
        ${CPPWINRT_OUTPUT_DIR}/module.g.cpp
    COMMAND
        cppwinrt.exe -pch . -input ${CMAKE_BINARY_DIR}/component.winmd -reference ${CPPWINRT_INPUT} -component stub -output ${CPPWINRT_OUTPUT_DIR}
    COMMAND
        cppwinrt.exe -pch . -input ${CMAKE_BINARY_DIR}/component.winmd -reference ${CPPWINRT_INPUT} -output ${CPPWINRT_OUTPUT_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS
        ${CMAKE_BINARY_DIR}/component.winmd
    COMMENT
        "Generating Component implementation stub...")

set(SOURCES
    ${CPPWINRT_OUTPUT_DIR}/module.g.cpp
    ${CPPWINRT_OUTPUT_DIR}/winrt/base.h
    MinGWComponent.ComponentClass.cpp
    MinGWComponent.ComponentClass.h
    component.def)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ucrtapp windowsapp winstorecompat)

include_directories(${CPPWINRT_OUTPUT_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

