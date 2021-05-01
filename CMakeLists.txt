cmake_minimum_required(VERSION 3.10)
project(rboy)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if (MSVC)
    add_compile_options(-W4 -WX /experimental:external /external:anglebrackets /external:W0 /std:c++latest)
else ()
    add_compile_options(-Wall -Werror)
endif ()

#add_subdirectory(ext)
add_subdirectory(src)
#add_subdirectory(tests)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT rbjoy)
