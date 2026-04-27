cmake_minimum_required(VERSION 3.13.4)
# Tên project không quan trọng lắm nhưng nên viết liền không dấu
project(auto-bot-mod VERSION 1.0.0) 

# Tìm và liên kết Geode SDK
find_package(Geode REQUIRED)

# Quét toàn bộ file .cpp trong thư mục src
file(GLOB_RECURSE SOURCES src/*.cpp)

# Lệnh chuẩn của Geode để thiết lập mod
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
