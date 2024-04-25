cmake_minimum_required(VERSION 3.5.0)
project(ComponentTest VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/EHsc")
    set(CMAKE_EXE_LINKER_FLAGS "/MANIFEST:NO")
    add_definitions("-DUNICODE" "-D_UNICODE")
else()
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|AMD64")
        set(CMAKE_CXX_FLAGS "-mcx16")
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "-municode -static")
endif()

set(CPPWINRT_INPUT 
    "../../references/Windows.winmd"
    "../../component/build/component.winmd")
set(CPPWINRT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/cppwinrt")

file(COPY ../../component/build/libmingw-component.dll DESTINATION ${CMAKE_BINARY_DIR})

add_custom_command(
    OUTPUT
        ${CPPWINRT_OUTPUT_DIR}/winrt/base.h
    COMMAND
        cppwinrt.exe -pch . -input ${CPPWINRT_INPUT} -output ${CPPWINRT_OUTPUT_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT
        "Generating C++/WinRT Headers...")

set(SOURCES
    ${CPPWINRT_OUTPUT_DIR}/winrt/base.h
    main.cpp
    app.rc)

add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${CPPWINRT_OUTPUT_DIR})

if(MSVC)
    target_link_libraries(${PROJECT_NAME} windowsapp)
else()
    target_link_libraries(${PROJECT_NAME} ucrtapp windowsapp winstorecompat)
endif()

