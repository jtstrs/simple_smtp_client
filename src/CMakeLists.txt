set(src main.cpp
        message.cpp
        smtp_protocol/data_init_state.cpp
        smtp_protocol/end_state.cpp
        smtp_protocol/error_state.cpp
        smtp_protocol/fill_data_state.cpp
        smtp_protocol/helo_state.cpp
        smtp_protocol/mail_from_state.cpp
        smtp_protocol/quit_state.cpp
        smtp_protocol/rcpt_to_state.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include_directories(/usr/local/include/)

find_library(POCO_NET PocoNet HINTS /usr/local/lib/PocoNet)
find_library(POCO_FOUNDATION PocoFoundation HINTS /usr/local/lib/PocoFoundation)

add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} ${POCO_FOUNDATION} ${POCO_NET})