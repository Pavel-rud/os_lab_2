cmake_minimum_required(VERSION 3.10)

project(OS_lab2)



set(APP_SRCS main.cpp)
set(LIB_SRCS background.cpp)


add_library(background SHARED ${LIB_SRCS})


add_executable(main ${APP_SRCS})


target_link_libraries(main background)
