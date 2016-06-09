# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = RandomFwkGUI
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += Parser.c Parser_Lex.c rngs/RNGLinearCong.cpp source/BinaryRandomWalk.cpp source/BufferedProbabilityBase.cpp source/Cronometro.cpp source/ExprBinaryRandomWalk.cpp source/ExprParserWidget.cpp source/ExprRNG.cpp source/ExprTextEdit.cpp source/FileInStreamInterface.cpp source/FileOutStreamInterface.cpp source/FileQBRWWidget.cpp source/FileQTreeWidget.cpp source/FileRawBuffer.cpp source/FileStreamInterface.cpp source/GULineEdit.cpp source/GeneralUsage.cpp source/GraphMagnifier.cpp source/GraphPanner.cpp source/GraphPicker.cpp source/GraphUi.cpp source/IInputWidget.cpp source/IProbabilityBase.cpp source/IRNG.cpp source/IRWBufferManager.cpp source/IRWBufferedItem.cpp source/IRWItem.cpp source/IRWSet.cpp source/IRandomWalk.cpp source/LCGBinaryRandomWalk.cpp source/LCGRngWidget.cpp source/Overlay.cpp source/ProbabilityBase.cpp source/QGraphItemAbstract.cpp source/QGraphWidget.cpp source/RWBufferedDp.cpp source/RWBufferedDpSet.cpp source/RWBufferedVec.cpp source/RWDp.cpp source/RWDpSet.cpp source/RWVec.cpp source/RWVecSet.cpp source/RandomNumberGenerator.cpp source/RandomSource.cpp source/Token.cpp source/Tokenizer.cpp source/main.cpp
HEADERS += Parser.h include/BinaryRandomWalk.h include/BufferedProbabilityBase.h include/Cronometro.h include/ExprBinaryRandomWalk.h include/ExprParserWidget.h include/ExprRNG.h include/ExprTextEdit.h include/FileInStreamInterface.h include/FileOutStreamInterface.h include/FileQBRWWidget.h include/FileQTreeWidget.h include/FileRawBuffer.h include/FileStreamInterface.h include/GULineEdit.h include/GeneralUsage.h include/GraphMagnifier.h include/GraphPanner.h include/GraphPicker.h include/GraphUi.h include/IInputWidget.h include/IProbabilityBase.h include/IRNG.h include/IRWBufferManager.h include/IRWBufferedItem.h include/IRWItem.h include/IRWSet.h include/IRandomWalk.h include/LCGBinaryRandomWalk.h include/LCGRngWidget.h include/Overlay.h include/ProbabilityBase.h include/QGraphItemAbstract.h include/QGraphWidget.h include/RWBufferedBase.h include/RWBufferedDp.h include/RWBufferedDpSet.h include/RWBufferedVec.h include/RWDPBase.h include/RWDp.h include/RWDpSet.h include/RWVBase.h include/RWVec.h include/RWVecSet.h include/RandomNumberGenerator.h include/RandomSource.h include/Token.h include/Tokenizer.h include/ui_GraphUi.h rngs/RNGLinearCong.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += rngs include /usr/local/qwt-6.1.0/include 
LIBS += ../RandomFwk/dist/Debug/GNU-Linux-x86/librandomfwk.a -lgmp -lgmpxx -Wl,-rpath,/usr/local/qwt-6.1.0/lib /usr/local/qwt-6.1.0/lib/libqwt.so -lfl -lgsl -lgslcblas  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
QMAKE_CXXFLAGS += -std=c++11 -m64 -pipe
