set(src main.cpp
        message.cpp
        smtp_client.cpp
        smtp_client_application.cpp
        validators/file_exists_validator.cpp
        validators/port_option_validator.cpp
        smtp_protocol/data_init_state.cpp
        smtp_protocol/end_state.cpp
        smtp_protocol/error_state.cpp
        smtp_protocol/fill_data_state.cpp
        smtp_protocol/helo_state.cpp
        smtp_protocol/mail_from_state.cpp
        smtp_protocol/quit_state.cpp
        smtp_protocol/rcpt_to_state.cpp
        smtp_protocol/connection_state.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(Poco REQUIRED COMPONENTS Net Foundation Util)

include_directories(Poco::Net Poco::Foundation Poco::Util)

add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} Poco::Net Poco::Foundation Poco::Util)