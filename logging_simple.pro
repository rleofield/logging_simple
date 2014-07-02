TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=  \
    src/log/tLogImpl.cpp \
    src/log/tLog.cpp \
    src/demo/test_thread.cpp \
    src/demo/test_cat_D.cpp \
    src/demo/test_cat_C.cpp \
    src/demo/test_cat_B.cpp \
    src/demo/test_cat_A.cpp \
    main.cpp

QMAKE_CXXFLAGS += -gdwarf-3

OBJECTS_DIR = .tmp
MOC_DIR = .tmp
UI_DIR = .tmp
RCC_DIR = .tmp


HEADERS += \
    src/log/tLogImpl.h \
    src/log/tLogEnum.h \
    src/log/tLogCategories.h \
    src/log/tLog.h \
    src/log/tLog_Category_rimg.h \
    src/log/tLog_Category_default.h \
    src/log/tLog_Category_D.h \
    src/log/tLog_Category_C.h \
    src/log/tLog_Category_B.h \
    src/log/tLog_Category_A.h \
    src/log/tLfmCL.h \
    src/log/tLfm.h


message("qmake logging_simple")

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/log
INCLUDEPATH += $$PWD/src/demo

QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_DEBUG += -std=c++0x
QMAKE_CXXFLAGS_DEBUG += -Wparentheses
QMAKE_CXXFLAGS_DEBUG += -Wreturn-type
QMAKE_CXXFLAGS_DEBUG += -Wshadow
QMAKE_CXXFLAGS_DEBUG += -Wextra
QMAKE_CXXFLAGS_DEBUG += -Wunused-parameter
QMAKE_CXXFLAGS_DEBUG -= -Wwrite-strings
QMAKE_CXXFLAGS_DEBUG -= -Wunused-variable
QMAKE_CXXFLAGS_DEBUG += -Weffc++

QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS_RELEASE += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -Wparentheses
QMAKE_CXXFLAGS_RELEASE += -Wreturn-type
QMAKE_CXXFLAGS_RELEASE += -Wshadow
QMAKE_CXXFLAGS_RELEASE += -Wextra
QMAKE_CXXFLAGS_RELEASE += -Wunused-parameter
QMAKE_CXXFLAGS_RELEASE -= -Wwrite-strings
QMAKE_CXXFLAGS_RELEASE -= -Wunused-variable
QMAKE_CXXFLAGS_RELEASE += -Weffc++


LIBS= -lboost_thread
LIBS += -lboost_system
LIBS += -lboost_filesystem
