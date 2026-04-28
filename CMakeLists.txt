cmake_minimum_required(VERSION 3.13.4)
project(auto-bot-mod VERSION 1.0.0) 

# Hack đặc trị: Quét trực tiếp ổ cứng của GitHub Actions để tìm file cấu hình Geode
if(NOT DEFINED Geode_DIR)
    file(GLOB_RECURSE GEODE_CONFIG_FILES 
        "$ENV{GITHUB_WORKSPACE}/*GeodeConfig.cmake"
        "$ENV{HOME}/Library/Application Support/Geode/*GeodeConfig.cmake"
    )
    if(GEODE_CONFIG_FILES)
        list(GET GEODE_CONFIG_FILES 0 FIRST_CONFIG)
        get_filename_component(FOUND_GEODE_DIR "${FIRST_CONFIG}" DIRECTORY)
        set(Geode_DIR "${FOUND_GEODE_DIR}" CACHE PATH "Geode SDK Path" FORCE)
        message(STATUS "🎯 Đã quét và tìm thấy Geode SDK tại: ${Geode_DIR}")
    endif()
endif()

# Mở khóa cơ chế bảo mật của iOS toolchain để CMake được phép đọc file
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

# Tìm và liên kết Geode SDK bằng đường dẫn thực tế vừa tìm được
find_package(Geode REQUIRED)

# Khôi phục lại cơ chế bảo mật
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Quét toàn bộ file .cpp ở thư mục gốc và thư mục src
file(GLOB_RECURSE SOURCES *.cpp src/*.cpp)

# Lệnh chuẩn của Geode để thiết lập mod
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
