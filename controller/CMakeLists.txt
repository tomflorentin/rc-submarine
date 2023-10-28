cmake_minimum_required(VERSION 3.24)
project(surface)

set(CMAKE_CXX_STANDARD 17)
set(SFML_ROOT "C:/SFML-2.5.1")
set(SFML_INCLUDE_DIR "C:/SFML-2.5.1/include")


add_executable(surface main.cpp COM.cpp RemoteControl.cpp RemoteControl.hpp SerialPort.cpp SerialPort.hpp KeyboardHandler.cpp KeyboardHandler.hpp Status.cpp Status.hpp PacketHandler.cpp PacketHandler.hpp)


# Copies all the DLL from ${SFML_ROOT}/bin to the root of the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_ROOT}/bin/"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Copies the font font.ttf from the root of the project to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/font.ttf"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

target_link_libraries(${PROJECT_NAME} Dwmapi.lib)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()


