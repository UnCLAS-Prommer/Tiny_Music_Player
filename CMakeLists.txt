cmake_minimum_required(VERSION 3.5)

project(Player LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(QT_USE_QTMULTIMEDIA TRUE)
SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)
set(Qt5_DIR "Z:/Qt/Qt5.14.2/5.14.2/mingw73_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets MultimediaWidgets Multimedia LinguistTools REQUIRED)

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

target_link_libraries(Player PRIVATE Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
