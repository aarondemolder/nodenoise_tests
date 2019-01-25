TARGET=TerrainTests

QT+=gui opengl core

SOURCES += main.cpp

LIBS += -lgtest
LIBS += -L/home/ademolder/lib -lnoise -lnoiseutils

INCLUDEPATH+= ../../nodenoise/include \
              ../../nodenoise/nodes \
              ../../nodenoise/models

DEFINES+=NODE_EDITOR_STATIC
