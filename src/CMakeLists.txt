find_package(Boost COMPONENTS system iostreams REQUIRED)
find_package(Threads REQUIRED)

add_library(HTTP_lib STATIC
    status_line.cpp
    request_line.cpp
    headers.cpp
    message_body.cpp
    http_response.cpp
    http_request.cpp
    gzip.cpp
    key_value_encode.cpp
    url_encode.cpp
    )

target_include_directories(HTTP_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
    ${Boost_INCLUDE_DIRS}
    )

target_link_libraries(HTTP_lib PUBLIC
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    )
