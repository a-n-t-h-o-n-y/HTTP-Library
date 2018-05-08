# DEMO
add_executable(demo
    demo.cpp
    )

target_link_libraries(demo HTTP_lib)

# TESTS
add_executable(test_http
    catch_main.cpp
    test_status_line.cpp
    test_headers.cpp
    test_message_body.cpp
    test_http_response.cpp
    test_http_request.cpp
    test_send.cpp
    test_read.cpp
    )

target_link_libraries(test_http HTTP_lib)

add_test(NAME test_http COMMAND test_http)
