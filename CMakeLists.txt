cmake_minimum_required(VERSION 3.18)
project(FileManager)

set(SKIA_INCLUDE_PATH "D:\\sdk\\skia" CACHE PATH "Skia include path,default:D:/sdk/skia" FORCE)
set(SKIA_LIB_PATH "D:\\sdk\\skia\\out" CACHE PATH "Skia lib path,default:D:/sdk/skia/out" FORCE)
set(EVERYTHING_INCLUDE_PATH "D:\\sdk\\Everything-SDK" CACHE PATH "Everything include path,default:D:/sdk/Everything-SDK" FORCE)
set(EVERYTHING_LIB_PATH "D:\\sdk\\Everything-SDK\\lib" CACHE PATH "Everything lib path,default:D:/sdk/Everything-SDK/lib" FORCE)

if(NOT IS_DIRECTORY "${SKIA_INCLUDE_PATH}")
    message(FATAL_ERROR "The path ${SKIA_INCLUDE_PATH} does not exist.")
endif()

if(NOT IS_DIRECTORY "${SKIA_LIB_PATH}")
    message(FATAL_ERROR "The path ${SKIA_LIB_PATH} does not exist.")
endif()

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

link_directories("${SKIA_LIB_PATH}")
include_directories("${SKIA_INCLUDE_PATH}")
add_executable(FileManager)
add_subdirectory(res)
add_subdirectory(src)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    set_property(TARGET FileManager PROPERTY VS_DPI_AWARE "PerMonitor")
    target_compile_definitions(FileManager PRIVATE $<$<CONFIG:Debug>:UNICODE _UNICODE DEBUG NOMINMAX _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS SK_DEBUG WIN32 _WINDOWS>)
    target_compile_definitions(FileManager PRIVATE $<$<CONFIG:Release>:UNICODE _UNICODE NDEBUG NOMINMAX _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS SK_RELEASE WIN32 _WINDOWS>)
    TARGET_LINK_LIBRARIES(FileManager skia Everything64 Dwmapi winmm kernel32 user32 shell32 imm32)
elseif(APPLE)
endif()