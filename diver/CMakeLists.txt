# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("embarque" C CXX)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Z_DUMMY_TARGET ${SRC_LIST} src/PinReader/DigitalPinReader.hpp src/PinReader/DigitalPinWriter.hpp src/PinReader/PinManager.hpp src/PinReader/AnalogPinReader.cpp src/PinReader/AnalogPinReader.hpp src/PinReader/AnalogPinWriter.cpp src/PinReader/AnalogPinWriter.hpp src/Controllers/L298Controller.cpp src/Controllers/L298Controller.hpp src/Controllers/LedController.cpp src/Controllers/LedController.hpp src/Controllers/BallastController.cpp src/Controllers/BallastController.hpp src/Sensors/UltrasonicSensor.cpp src/Sensors/UltrasonicSensor.hpp src/Controllers/ValveController.cpp src/Controllers/ValveController.hpp src/Interfaces/ISetupable.hpp src/Controllers/EngineController.cpp src/Controllers/EngineController.hpp src/RemoteControl/protocol.hpp src/RemoteControl/RemoteControl.cpp src/RemoteControl/RemoteControl.hpp src/Controllers/DepthController.cpp src/Controllers/DepthController.hpp src/Sensors/DepthSensor.cpp src/Sensors/DepthSensor.hpp src/Security/WaterSecurity.cpp src/Security/WaterSecurity.hpp src/Security/Security.cpp src/Security/Security.hpp src/Sensors/BatteryLevelSensor.cpp src/Sensors/BatteryLevelSensor.hpp src/Security/BatterySecurity.cpp src/Security/BatterySecurity.hpp src/Security/DepthSecurity.cpp src/Security/DepthSecurity.hpp src/Security/SecurityMonitor.cpp src/Security/SecurityMonitor.hpp src/RemoteControl/ControlProtocol.cpp src/RemoteControl/ControlProtocol.hpp src/Sensors/SensorMonitor.cpp src/Sensors/SensorMonitor.hpp src/Sensors/DHT.cpp src/Sensors/DHT.hpp src/Logger.cpp src/func.hpp src/Controllers/CameraController.cpp src/Controllers/CameraController.hpp src/lib/Servo.cpp src/lib/Servo.hpp src/lib/ServoTimers.hpp src/Sensors/TemperatureSensor.cpp src/Sensors/TemperatureSensor.hpp src/lib/OneWire.hpp src/lib/OneWire.cpp src/lib/OneWire_direct_gpio.hpp src/lib/OneWire_direct_regtype.hpp src/lib/DallasTemperature.cpp src/lib/DallasTemperature.hpp src/Interfaces/IBridgeController.hpp src/Controllers/BTS7960Controller.hpp src/Controllers/BTS7960Controller.cpp src/Interfaces/IBridgeController.cpp src/PowerManager.cpp src/PowerManager.hpp src/Interfaces/IPowerMonitorable.cpp src/Interfaces/IPowerMonitorable.hpp)
