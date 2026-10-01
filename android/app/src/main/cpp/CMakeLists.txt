cmake_minimum_required(VERSION 3.22.1)
project(nfsu2_android LANGUAGES C CXX)

set(ANDROID TRUE CACHE BOOL "Android build" FORCE)
set(NFSU2_VULKAN ON CACHE BOOL "Android Vulkan" FORCE)
set(XBOXRECOMP_VULKAN ON CACHE BOOL "Android Vulkan renderer" FORCE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

get_filename_component(NFSU2_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../../../../" ABSOLUTE)

add_subdirectory("${NFSU2_ROOT}" "nfsu2-native")

if(TARGET nfsu2_recomp)
    target_compile_definitions(nfsu2_recomp PRIVATE ANDROID=1 NFSU2_VULKAN=1)
endif()

if(TARGET nfsu2_recomp)
    target_link_libraries(nfsu2_recomp PRIVATE android log vulkan)
endif()
