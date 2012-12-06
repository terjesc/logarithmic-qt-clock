HEADERS       = logclock.h
SOURCES       = logclock.cpp \
                main.cpp

# install
target.path = .
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS logclock.pro
sources.path = .
INSTALLS += target sources

symbian {
    TARGET.UID3 = 0xA000A64F
    include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
}

