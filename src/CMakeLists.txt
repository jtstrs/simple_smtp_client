set(src main.cpp)

include_directories(/usr/local/include/)

find_library(POCO_NET PocoNet HINTS /usr/local/lib/PocoNet)
find_library(POCO_FOUNDATION PocoFoundation HINTS /usr/local/lib/PocoFoundation)

add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} ${POCO_FOUNDATION} ${POCO_NET})