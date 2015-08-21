# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = RandomFwkGUI
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets printsupport sql
SOURCES += dieteste.c rngs/RNGLinearCong.cpp source/BDBinDrawingEngine.cpp source/BDDataPointsDrawingEngine.cpp source/BDIntegralDrawingEngine.cpp source/BDProbabilityBase.cpp source/BinDrawingEngine.cpp source/BinaryRandomWalk.cpp source/BufferedPollarDrawingEngine.cpp source/BufferedPollarRwDp.cpp source/BufferedPollarRwVec.cpp source/BufferedProbabilityBase.cpp source/Cronometro.cpp source/DFA.cpp source/DFAInputGui.cpp source/DataPointsDrawingEngine.cpp source/ExprBinaryRandomWalk.cpp source/ExprParserWidget.cpp source/ExprRNG.cpp source/ExprTextEdit.cpp source/FileInStreamInterface.cpp source/FileOutStreamInterface.cpp source/FileQBRWWidget.cpp source/FileQTreeWidget.cpp source/FileRNG.cpp source/FileRawBuffer.cpp source/FileStreamInterface.cpp source/FittingDrawingEngine.cpp source/FormatString.cpp source/FormattedFileStreamInterface.cpp source/GULineEdit.cpp source/GeneralUsage.cpp source/GraphMagnifier.cpp source/GraphPanner.cpp source/GraphPicker.cpp source/GraphUi.cpp source/IDrawingEngine.cpp source/IInputWidget.cpp source/IPolyfit.cpp source/IPolynom.cpp source/IProbabilityBase.cpp source/IRNG.cpp source/IRWBd.cpp source/IRWBufferedItem.cpp source/IRWIntervalBuilder.cpp source/IRWItem.cpp source/IRWSet.cpp source/IRandomWalk.cpp source/IntegralDrawingEngine.cpp source/LCGBinaryRandomWalk.cpp source/LCGRngWidget.cpp source/LinearFit.cpp source/MatrixGSL.cpp source/MemAllocWidget.cpp source/MemoryRandomWalk.cpp source/Overlay.cpp source/Parser.c source/Parser_Lex.c source/PollarBufferManager.cpp source/PollarDrawingEngine.cpp source/PollarFileInStreamInterface.cpp source/PollarFileOutStreamInterface.cpp source/PollarRwDp.cpp source/PollarRwDpSet.cpp source/PollarSet.cpp source/Polynom.cpp source/ProbabilityBase.cpp source/QPointFSLC.cpp source/QPollarF.cpp source/RWBdManager.cpp source/RWBufferIterator.cpp source/RWBufferManager.cpp source/RWBufferManagerSingleton.cpp source/RWBufferedDp.cpp source/RWBufferedDpIntervalBuilder.cpp source/RWBufferedDpSet.cpp source/RWBufferedVec.cpp source/RWBufferedVecIntervalBuilder.cpp source/RWBufferedVecSet.cpp source/RWDp.cpp source/RWDpIntervalBuilder.cpp source/RWDpSet.cpp source/RWLocPair.cpp source/RWVec.cpp source/RWVecIntervalBuilder.cpp source/RWVecSet.cpp source/RandomNumberGenerator.cpp source/RandomSource.cpp source/SweepLine.cpp source/Token.cpp source/Tokenizer.cpp source/VEdge.cpp source/Walks2DOverlay.cpp source/WeierstrassDrawingEngine.cpp source/WeiestrassInputWidget.cpp source/main.cpp
HEADERS += include/BDBinDrawingEngine.h include/BDDataPointsDrawingEngine.h include/BDIntegralDrawingEngine.h include/BDProbabilityBase.h include/BinDrawingEngine.h include/BinaryRandomWalk.h include/BufferedPollarDrawingEngine.h include/BufferedPollarRwDp.h include/BufferedPollarRwVec.h include/BufferedProbabilityBase.h include/Cronometro.h include/DFA.h include/DFAInputGui.h include/DataPointsDrawingEngine.h include/ExprBinaryRandomWalk.h include/ExprParserWidget.h include/ExprRNG.h include/ExprTextEdit.h include/FileInStreamInterface.h include/FileOutStreamInterface.h include/FileQBRWWidget.h include/FileQTreeWidget.h include/FileRNG.h include/FileRawBuffer.h include/FileStreamInterface.h include/FittingDrawingEngine.h include/FormatString.h include/FormattedFileStreamInterface.h include/GULineEdit.h include/GeneralUsage.h include/GraphMagnifier.h include/GraphPanner.h include/GraphPicker.h include/GraphUi.h include/IDrawingEngine.h include/IInputWidget.h include/IPolyfit.h include/IPolynom.h include/IProbabilityBase.h include/IRNG.h include/IRWBd.h include/IRWBufferedItem.h include/IRWIntervalBuilder.h include/IRWItem.h include/IRWSet.h include/IRandomWalk.h include/IntegralDrawingEngine.h include/LCGBinaryRandomWalk.h include/LCGRngWidget.h include/LinearFit.h include/MatrixGSL.h include/MemAllocWidget.h include/MemoryRandomWalk.h include/Overlay.h include/Parser.h include/PollarBufferManager.h include/PollarBufferedRwDpSet.h include/PollarDrawingEngine.h include/PollarFileInStreamInterface.h include/PollarFileOutStreamInterface.h include/PollarRwDp.h include/PollarRwDpSet.h include/PollarSet.h include/Polynom.h include/ProbabilityBase.h include/QPointFSLC.h include/QPollarF.h include/RWBdManager.h include/RWBufferIterator.h include/RWBufferManager.h include/RWBufferManagerSingleton.h include/RWBufferedDp.h include/RWBufferedDpBase.h include/RWBufferedDpIntervalBuilder.h include/RWBufferedDpSet.h include/RWBufferedVec.h include/RWBufferedVecBase.h include/RWBufferedVecIntervalBuilder.h include/RWBufferedVecSet.h include/RWDp.h include/RWDpBase.h include/RWDpIntervalBuilder.h include/RWDpSet.h include/RWLocPair.h include/RWVBase.h include/RWVec.h include/RWVecIntervalBuilder.h include/RWVecSet.h include/RandomNumberGenerator.h include/RandomSource.h include/SweepLine.h include/Token.h include/Tokenizer.h include/VEdge.h include/Walks2DOverlay.h include/WeierstrassDrawingEngine.h include/WeiestrassInputWidget.h include/dieharder/Dtest.h include/dieharder/Vtest.h include/dieharder/Xtest.h include/dieharder/brg_endian.h include/dieharder/brg_types.h include/dieharder/copyright.h include/dieharder/dab_bytedistrib.h include/dieharder/dab_dct.h include/dieharder/dab_filltree.h include/dieharder/dab_filltree2.h include/dieharder/dab_monobit2.h include/dieharder/diehard_2dsphere.h include/dieharder/diehard_3dsphere.h include/dieharder/diehard_birthdays.h include/dieharder/diehard_bitstream.h include/dieharder/diehard_count_1s_byte.h include/dieharder/diehard_count_1s_stream.h include/dieharder/diehard_craps.h include/dieharder/diehard_dna.h include/dieharder/diehard_operm5.h include/dieharder/diehard_opso.h include/dieharder/diehard_oqso.h include/dieharder/diehard_parking_lot.h include/dieharder/diehard_rank_32x32.h include/dieharder/diehard_rank_6x8.h include/dieharder/diehard_runs.h include/dieharder/diehard_squeeze.h include/dieharder/diehard_sums.h include/dieharder/dieharder.h include/dieharder/dieharder_rng_types.h include/dieharder/dieharder_test_types.h include/dieharder/libdieharder.h include/dieharder/marsaglia_tsang_gcd.h include/dieharder/marsaglia_tsang_gorilla.h include/dieharder/output.h include/dieharder/parse.h include/dieharder/rgb_bitdist.h include/dieharder/rgb_kstest_test.h include/dieharder/rgb_lagged_sums.h include/dieharder/rgb_lmn.h include/dieharder/rgb_minimum_distance.h include/dieharder/rgb_operm.h include/dieharder/rgb_permutations.h include/dieharder/rgb_persist.h include/dieharder/rgb_timing.h include/dieharder/rijndael-alg-fst.h include/dieharder/skein.h include/dieharder/skein_port.h include/dieharder/std_test.h include/dieharder/sts_monobit.h include/dieharder/sts_runs.h include/dieharder/sts_serial.h include/dieharder/teste.tab.h include/dieharder/tests.h include/dieharder/ui_newForm.h include/dieharder/user_template.h include/dieharder/verbose.h include/ui_GraphUi.h rngs/RNGLinearCong.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = moc
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += HAVE_INLINE 
INCLUDEPATH += include/dieharder rngs/ include /usr/local/qwt-6.1.2/include stringfrmt/ 
LIBS += -lgmp -lgmpxx -lgsl -lgslcblas -lfl libdieharder/libdiehardercli.a libdieharder/libdieharder.a -Wl,-rpath,/usr/local/qwt-6.1.2/lib /usr/local/qwt-6.1.2/lib/libqwt.so libformatstrprs.a  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
