cmake_minimum_required(VERSION 3.15)

project(damas
  LANGUAGES C
)

# Compiler flags and properties
add_library(project_flags INTERFACE)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
  src/*.c
)

add_executable(app ${APP_SOURCES})

target_include_directories(app PRIVATE src)

set(DEBUG_FLAGS
  -g
  -DDEBUG
)

set(RELEASE_FLAGS
  -O3
  -DNDEBUG
)

set(RELWITHDEFINFO_FLAGS
  -O3
  -g
  -fno-omit-frame-pointer
  -DNDEBUG
)

if (MSVC)
  target_compile_options(project_flags INTERFACE /W4)
else()
  target_compile_options(project_flags INTERFACE
    $<$<CONFIG:Debug>:${DEBUG_FLAGS}>
    $<$<CONFIG:Release>:${RELEASE_FLAGS}>
    $<$<CONFIG:RelWithDebInfo>:${RELWITHDEBINFO_FLAGS}>
  )

  target_compile_options(project_flags INTERFACE
    -Wall
    -Wextra
    -pedantic
    -Wpedantic
    -Wshadow
    # -Wconversion
    -Wformat=2
    -Werror
  )
endif()

target_compile_features(project_flags INTERFACE c_std_11)

# -----------------------------------------------------------

include(GNUInstallDirs)

# Install the binary
install(TARGETS app
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CPACK_PACKAGE_NAME "Damas")
set(CPACK_PACKAGE_VERSION "1.0.5")

if(WIN32)
    set(CPACK_SYSTEM_NAME "Windows-x64")
    set(CPACK_GENERATOR "ZIP")
elseif(APPLE)
    set(CPACK_SYSTEM_NAME "macOS")
    set(CPACK_GENERATOR "TGZ")
else()
    set(CPACK_SYSTEM_NAME "Linux-x64")
    set(CPACK_GENERATOR "TGZ")
endif()

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")

include(CPack)
