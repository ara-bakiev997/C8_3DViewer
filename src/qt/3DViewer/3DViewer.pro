QT       += core gui opengl openglwidgets

#LIBS += -lopengl32 -lglu32
#LIBS += -glut
LIBS += -framework GLUT

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../parser_2.0.c \
    QtGifImage-master/src/3rdParty/giflib/dgif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/egif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/gif_err.c \
    QtGifImage-master/src/3rdParty/giflib/gif_font.c \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.c \
    QtGifImage-master/src/3rdParty/giflib/gifalloc.c \
    QtGifImage-master/src/3rdParty/giflib/quantize.c \
    QtGifImage-master/src/gifimage/qgifimage.cpp \
    colorpalette.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../parser.h \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib_private.h \
    QtGifImage-master/src/gifimage/qgifglobal.h \
    QtGifImage-master/src/gifimage/qgifimage.h \
    QtGifImage-master/src/gifimage/qgifimage_p.h \
    colorpalette.h \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    QtGifImage-master/src/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    QtGifImage-master/src/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    QtGifImage-master/src/gifimage/gifimage.pro \
    QtGifImage-master/src/gifimage/gifimage.pro \
    QtGifImage-master/src/gifimage/gifimage.pro \
    QtGifImage-master/src/src.pro \
    QtGifImage-master/src/src.pro

DISTFILES += \
    QtGifImage-master/src/3rdParty/giflib.pri \
    QtGifImage-master/src/3rdParty/giflib/AUTHORS \
    QtGifImage-master/src/3rdParty/giflib/COPYING \
    QtGifImage-master/src/3rdParty/giflib/README \
    QtGifImage-master/src/gifimage/doc/qtgifimage.qdocconf \
    QtGifImage-master/src/gifimage/doc/src/examples.qdoc \
    QtGifImage-master/src/gifimage/doc/src/index.qdoc \
    QtGifImage-master/src/gifimage/doc/src/qtgifimage.qdoc \
    QtGifImage-master/src/gifimage/doc/src/usage.qdoc \
    QtGifImage-master/src/gifimage/qdoc_wrapper.sh \
    QtGifImage-master/src/gifimage/qtgifimage.pri
