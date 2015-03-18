#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T03:16:09
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = check_km5
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QMAKE_CXXFLAGS+=-std=c++1y -pedantic
QMAKE_CXX=gcc-4.9

SOURCES += main.cpp
QMAKE_POST_LINK+=\
pushd .;\
cd $$_PRO_FILE_PWD_;\
git add --all -v;\
git commit -m \"Auto commit at `date`\";\
popd\
