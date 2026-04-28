cmake_minimum_required(VERSION 3.13.4)
project(auto-bot-mod VERSION 1.0.0) 

# 1. Gọi trực tiếp Geode CLI để lấy đường dẫn SDK chính xác tuyệt đối
execute_process(
    COMMAND geode sdk path
    OUTPUT_VARIABLE GEODE_SDK_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(Geode_DIR "${GEODE_SDK_PATH}")

# 2. Tạm thời mở khóa cơ chế bảo mật của iOS toolchain để CMake được phép quét thư mục máy chủ
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

# Tìm và liên kết Geode SDK
find_package(Geode REQUIRED)

# Khôi phục lại cơ chế bảo mật (tùy chọn để đảm bảo an toàn cho các tác vụ sau)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Quét toàn bộ file .cpp ở thư mục gốc và thư mục src
file(GLOB_RECURSE SOURCES *.cpp src/*.cpp)

# Lệnh chuẩn của Geode để thiết lập mod
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
