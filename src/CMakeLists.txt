add_library(rbjoy
    rbjoy.cpp
    rbjoy.h
)

target_include_directories(rbjoy PUBLIC .)
target_link_libraries(rbjoy dxguid dinput8)

add_executable(rbjoy-test
    rbjoy-test.cpp
)
target_link_libraries(rbjoy-test rbjoy)
