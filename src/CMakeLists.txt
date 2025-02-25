# 核心数据模块
add_library(ScoreItems STATIC
    event.c
    school.c
    result.c
    prehead.c
)

# 打印功能模块
add_library(Print STATIC
    print.c
)

# 界面功能模块
add_library(Menu STATIC
    menu.c
)
# 文件保存读取模块
add_library(Store STATIC
    store.c
)
# 所有库都需要包含项目头文件目录
target_include_directories(ScoreItems PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Print PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Menu PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Store PUBLIC ${PROJECT_SOURCE_DIR}/include)

# 为 Menu 模块添加依赖
target_link_libraries(Menu PUBLIC Store)
target_link_libraries(Menu PUBLIC Print)
target_link_libraries(Menu PUBLIC ScoreItems)


# 为 Store 模块添加依赖
target_link_libraries(Store PUBLIC ScoreItems)