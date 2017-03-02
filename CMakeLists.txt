cmake_minimum_required(VERSION 3.6)
project(amqCTest)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES_C consumer.c)
set(SOURCE_FILES_P producer.c)

include_directories(/usr/local/include/activemq-c-1.1.0/ /usr/include/apr-1/)


add_executable(amqCTestConsumer ${SOURCE_FILES_C})
add_executable(amqCTestProducer ${SOURCE_FILES_P})

target_link_libraries(amqCTestConsumer /usr/local/lib/libactivemq-c.2.dylib)
target_link_libraries(amqCTestProducer /usr/local/lib/libactivemq-c.2.dylib)
