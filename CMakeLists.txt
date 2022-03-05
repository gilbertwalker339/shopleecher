cmake_minimum_required(VERSION 3.16)

project(ShopLeecher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Sql Network Concurrent REQUIRED)

qt_add_executable(appShopLeecher
    main.cpp
    Models/database.h Models/database.cpp
    Models/user.h Models/user.cpp
    Models/leecher.h Models/leecher.cpp
    Controllers/settingsController.h Controllers/settingsController.cpp
    Controllers/userController.h Controllers/userController.cpp
    Controllers/detailsController.h Controllers/detailsController.cpp
    Extensions/network.h Extensions/network.cpp
    Extensions/thegioididong.h Extensions/thegioididong.cpp
    Enums/deviceEnum.h
)

qt_add_qml_module(appShopLeecher
    URI ShopLeecher
    VERSION 1.0
    QML_FILES
        main.qml
        Views/Components/EasyButton.qml
        Views/MainScreen.qml
        Views/SettingsScreen.qml
        Views/LoginScreen.qml
        Views/DetailsScreen.qml
        Views/TestScreen.qml
)

set_target_properties(appShopLeecher PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appShopLeecher
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appShopLeecher
    PRIVATE Qt6::Quick Qt6::Sql Qt6::Network Qt6::Concurrent)
