cmake_minimum_required(VERSION 3.10)
project(Scorecalculation VERSION 1.2 LANGUAGES C)
# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_C_STANDARD 11)
# 调试模式配置
if(DEFINED _DEBUG)
        unset(_DEBUG CACHE)
endif()
option(_DEBUG "Debug" OFF)

# 生成配置文件
configure_file(config.h.in config.h)
# 创建主可执行文件
add_executable(${PROJECT_NAME} main.c)

# 添加包含目录（包含构建目录以获取生成的config.h）
include_directories(
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

# 添加子目录（包含源文件库）
add_subdirectory(src)

# 链接所有子目录生成的库
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ScoreItems
    Print
    Menu
    Store
    )