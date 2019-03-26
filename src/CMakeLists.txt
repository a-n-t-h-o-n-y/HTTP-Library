find_package(Boost COMPONENTS system iostreams REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(HTTP_lib STATIC
    status_line.cpp
    request_line.cpp
    headers.cpp
    message_body.cpp
    http_response.cpp
    http_request.cpp
    gzip.cpp
    verify_okay.cpp
    key_value_encode.cpp
    url_encode.cpp
    to_lowercase.cpp
    bearer_token.cpp
    base64_encode.cpp
    json_ptree.cpp
    xml_ptree.cpp
    make_connection.cpp
    make_tls_connection.cpp
    basic_get_request.cpp
    basic_post_request.cpp
    oauth_bearer_token_request.cpp
    oauth_helper.cpp
    account_authorize.cpp
)

target_include_directories(HTTP_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
        ${Boost_INCLUDE_DIRS}
    PRIVATE
        ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(HTTP_lib
    PUBLIC
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
    PRIVATE
        ${OPENSSL_LIBRARIES}
)

target_compile_features(HTTP_lib PRIVATE cxx_std_17)
target_compile_options(HTTP_lib PRIVATE -Wall -Wextra)
