cmake_minimum_required(VERSION 3.13.4)
project(auto-bot-mod VERSION 1.0.0) 

# 1. Tìm chính xác thư mục chứa GeodeConfig.cmake bên trong GEODE_SDK
file(GLOB_RECURSE GEODE_CONFIG_FILES "$ENV{GEODE_SDK}/*GeodeConfig.cmake")
if(GEODE_CONFIG_FILES)
    list(GET GEODE_CONFIG_FILES 0 FIRST_CONFIG)
    get_filename_component(FOUND_GEODE_DIR "${FIRST_CONFIG}" DIRECTORY)
    set(Geode_DIR "${FOUND_GEODE_DIR}" CACHE PATH "Geode SDK Path" FORCE)
endif()

# 2. TẮT HOÀN TOÀN cơ chế chặn đường dẫn của iOS Toolchain
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)

# Tìm và liên kết Geode SDK
find_package(Geode REQUIRED)

# Bật lại cơ chế chặn để đảm bảo an toàn cho các bước biên dịch sau của Apple
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Quét toàn bộ file .cpp ở thư mục gốc và thư mục src
file(GLOB_RECURSE SOURCES *.cpp src/*.cpp)

# Lệnh chuẩn của Geode để thiết lập mod
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
