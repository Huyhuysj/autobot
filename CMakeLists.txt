cmake_minimum_required(VERSION 3.13.4)
project(auto-bot-mod VERSION 1.0.0) 

# Gán cứng trực tiếp đường dẫn SDK từ biến môi trường
set(Geode_DIR "$ENV{GEODE_SDK}" CACHE PATH "Geode SDK Path" FORCE)

# Tắt hoàn toàn cơ chế chặn đường dẫn của iOS Toolchain
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)

# Tìm và liên kết Geode SDK
find_package(Geode REQUIRED)

# Khôi phục lại cơ chế chặn để đảm bảo an toàn cho các bước sau
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Quét toàn bộ file .cpp ở thư mục gốc và thư mục src
file(GLOB_RECURSE SOURCES *.cpp src/*.cpp)

# Lệnh chuẩn của Geode để thiết lập mod
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
