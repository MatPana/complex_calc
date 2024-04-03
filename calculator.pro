QT += widgets

HEADERS       = button.h \
                calculator.h \
                complexnumber.h \
                calcmemory.h
SOURCES       = button.cpp \
                calculator.cpp \
                complexnumber.cpp \
                calcmemory.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/calculator
INSTALLS += target

DISTFILES += \
    CMakeLists.txt \
    CMakeLists.txt.user
