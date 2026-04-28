cmake_minimum_required(VERSION 3.13.4)
project(auto-bot-mod VERSION 1.0.0) 

# Lấy đường dẫn từ biến môi trường và cấp quyền cho iOS toolchain đọc thư mục này
if(DEFINED ENV{GEODE_SDK})
    set(Geode_DIR "$ENV{GEODE_SDK}")
    list(APPEND CMAKE_FIND_ROOT_PATH "$ENV{GEODE_SDK}")
endif()

# Tìm và liên kết Geode SDK
find_package(Geode REQUIRED)

# Quét toàn bộ file .cpp ở thư mục gốc và thư mục src
file(GLOB_RECURSE SOURCES *.cpp src/*.cpp)

# Lệnh chuẩn của Geode để thiết lập mod
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
