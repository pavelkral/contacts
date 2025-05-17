QT += sql widgets

HEADERS = mainwindow.h \
          conect.h \
          customermodel.h \
          adddialog.h \
          groupmodel.h \

SOURCES = mainwindow.cpp \
          main.cpp \
          customermodel.cpp \
          adddialog.cpp \
          groupmodel.cpp \

FORMS = mainwindow.ui \
        adddialog.ui \

TEMPLATE = app

RESOURCES +=    \
	condat.qrc

RC_FILE = contacts.rc

DISTFILES += \
      README.md
