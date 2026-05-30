cmake_minimum_required(VERSION 3.5)

project(Player LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_DIR "C:/Qt/6.8.3/mingw_64/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS Widgets MultimediaWidgets Multimedia LinguistTools REQUIRED)

set(TS_FILES untitled_zh_CN.ts)

add_executable(Player
    Main.cpp
    Main.h
    HMain.cpp
    HAudio.cpp
    Audio.h
    QtMainGUI.h
    main.ui
    ${TS_FILES}
  )

target_link_libraries(Player PRIVATE Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)

# ---------- 自动部署 Qt6 DLL 到 build 目录 ----------
# 从 Qt6_DIR 反推 windeployqt.exe 路径
get_filename_component(QT6_BIN_DIR "${Qt6_DIR}/../../../bin" ABSOLUTE)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT6_BIN_DIR}" REQUIRED)

add_custom_command(TARGET Player POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Deploying Qt6 DLLs..."
    COMMAND ${WINDEPLOYQT_EXECUTABLE}
        --no-translations          # 已有自己的翻译文件
        --no-system-d3d-compiler   # 不需要 D3D 编译器
        --no-opengl-sw             # 不需要 OpenGL 软件渲染
        "$<TARGET_FILE:Player>"
    COMMENT "Running windeployqt..."
)

qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
