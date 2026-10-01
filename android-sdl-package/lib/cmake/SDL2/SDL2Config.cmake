set(SDL2_FOUND TRUE)
set(SDL2_VERSION "2.32.10")

if(NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 SHARED IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION "/data/data/com.termux/files/home/nfsu2-sw/android-sdl-package/lib/libSDL2.so"
        INTERFACE_INCLUDE_DIRECTORIES "/data/data/com.termux/files/home/nfsu2-sw/android-sdl-package/include"
    )
endif()
