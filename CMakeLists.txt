cmake_minimum_required(VERSION 3.15)

project(damas
  VERSION 1.0.6
  LANGUAGES C
)

# Compiler flags and properties
add_library(project_flags INTERFACE)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
  src/*.c
)

add_executable(app ${APP_SOURCES})

target_include_directories(app PRIVATE src)

target_compile_definitions(project_flags INTERFACE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
  $<$<C_COMPILER_ID:MSVC>:
    _CRT_SECURE_NO_WARNINGS
  >
)

target_compile_options(project_flags INTERFACE
  $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wformat=2
    -Werror
    $<$<CONFIG:RelWithDebInfo>:-O3;-g;-fno-omit-frame-pointer>
  >

  $<$<C_COMPILER_ID:MSVC>:
    /W4
    /WX
  >
)

target_compile_features(project_flags INTERFACE c_std_11)
target_link_libraries(app PRIVATE project_flags)

# -----------------------------------------------------------

install(TARGETS app
  RUNTIME DESTINATION bin
)

set(CPACK_PACKAGE_NAME                "damas")
set(CPACK_PACKAGE_VERSION             "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Jogo de Damas")
set(CPACK_PACKAGE_INSTALL_DIRECTORY   "damas")
set(CPACK_STRIP_FILES                 TRUE)

# Windows – NSIS installer
set(CPACK_NSIS_DISPLAY_NAME    "Damas")
set(CPACK_NSIS_MODIFY_PATH     OFF)

# macOS – drag-and-drop bundle
set(CPACK_DMG_VOLUME_NAME      "Damas")

# Linux – plain tar.gz  (AppImage is built separately in CI)
set(CPACK_GENERATOR            "TGZ")

include(CPack)
