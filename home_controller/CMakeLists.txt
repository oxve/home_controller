cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS $ENV{ESP_COMPONENTS_DIR}/components)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(home_controller)

target_add_binary_data(home_controller.elf "resources/mqtt_eclipseprojects_io.pem" TEXT)
