cmake_minimum_required(VERSION 3.13.4)
project(auto-bot-mod VERSION 1.0.0) 

# --- BẮT ĐẦU ĐOẠN CODE DÒ ĐƯỜNG DẪN ---
message(WARNING "=== BẮT ĐẦU DÒ ĐƯỜNG DẪN GEODE ===")
message(WARNING "1. Giá trị biến ENV{GEODE_SDK} đang là: '$ENV{GEODE_SDK}'")
message(WARNING "2. Giá trị biến ENV{HOME} đang là: '$ENV{HOME}'")

# Quét tìm file cấu hình trong thư mục Home của máy ảo
file(GLOB_RECURSE FOUND_CONFIG_FILES "$ENV{HOME}/*GeodeConfig.cmake")
message(WARNING "3. Kết quả quét file GeodeConfig.cmake: ${FOUND_CONFIG_FILES}")
message(WARNING "=== KẾT THÚC DÒ ĐƯỜNG DẪN ===")
# --- KẾT THÚC ĐOẠN CODE DÒ ĐƯỜNG DẪN ---

# Phần code cũ (để hệ thống tiếp tục chạy đến khi báo lỗi)
if(DEFINED ENV{GEODE_SDK})
    set(Geode_DIR "$ENV{GEODE_SDK}")
    list(APPEND CMAKE_FIND_ROOT_PATH "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp src/*.cpp)
setup_geode_mod(${PROJECT_NAME} ${SOURCES})
