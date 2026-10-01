cmake_minimum_required(VERSION 3.22.1)
project(nfsu2_android LANGUAGES C CXX)

set(NFSU2_VULKAN ON CACHE BOOL "Android Vulkan" FORCE)
set(ANDROID TRUE)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../../../../. android-native)
