QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    graph.h \
    graph.hpp \
    iterator.hpp \
    vertex.hpp \
    edge.hpp \
    graph_algorithm.h \
    Tarjan.hpp \
    Prim.hpp \
    Kruskal.hpp

SOURCES += \
    main.cpp \

OTHER_FILES += \
    input.txt \
    output.txt
