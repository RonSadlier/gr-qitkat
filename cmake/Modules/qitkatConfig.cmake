INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_QITKAT qitkat)

FIND_PATH(
    QITKAT_INCLUDE_DIRS
    NAMES qitkat/api.h
    HINTS $ENV{QITKAT_DIR}/include
        ${PC_QITKAT_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREEFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    QITKAT_LIBRARIES
    NAMES gnuradio-qitkat
    HINTS $ENV{QITKAT_DIR}/lib
        ${PC_QITKAT_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QITKAT DEFAULT_MSG QITKAT_LIBRARIES QITKAT_INCLUDE_DIRS)
MARK_AS_ADVANCED(QITKAT_LIBRARIES QITKAT_INCLUDE_DIRS)

