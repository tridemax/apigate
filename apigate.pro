
CONFIG(debug, debug|release) {
	message("apigate_debug")

	TARGET = apigate_debug

	DESTDIR = $$_PRO_FILE_PWD_/../.dist
	OBJECTS_DIR = $$_PRO_FILE_PWD_/../.int/apigate_debug

} else {
	message("apigate_release")

	TARGET = apigate

	DESTDIR = $$_PRO_FILE_PWD_/../.dist
	OBJECTS_DIR = $$_PRO_FILE_PWD_/../.int/apigate_release
}

TEMPLATE = app
CONFIG += console precompile_header c++14
CONFIG -= qt
MAKEFILE = $$_PRO_FILE_PWD_/apigate.makefile

#-------------------------------------------------------------------------------------------------
# warnings
#-------------------------------------------------------------------------------------------------
QMAKE_CXXFLAGS_WARN_ON += \
	-Wno-parentheses \
	-Wno-unused-variable \
	-Wno-unused-parameter \
	-Wno-unused-local-typedefs \
	-Wno-attributes \
	-Wno-unused-but-set-variable \
	-Wno-unused-result \
	-Wno-switch

#-------------------------------------------------------------------------------------------------
# compiler flags
#-------------------------------------------------------------------------------------------------
QMAKE_CXXFLAGS += \
	-m64 \
	-msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -mf16c \
	-g \
	-fpic \
	-fdata-sections \
	-ffunction-sections \
	-fno-strict-aliasing \
	-I$$_PRO_FILE_PWD_/../auxiliary \
	-I$$_PRO_FILE_PWD_/platform/linux

PRECOMPILED_HEADER = $$_PRO_FILE_PWD_/platform/linux/platform.h

CONFIG(debug, debug|release) {
	DEFINES += _DEBUG DEBUG

} else {
	DEFINES += NDEBUG

	QMAKE_CFLAGS_RELEASE -= -O0 -O1 -O2
	QMAKE_CFLAGS_RELEASE *= -O3

	QMAKE_CXXFLAGS_RELEASE -= -O0 -O1 -O2
	QMAKE_CXXFLAGS_RELEASE *= -O3
}

#-------------------------------------------------------------------------------------------------
# linker flags
#-------------------------------------------------------------------------------------------------
LIBS += \
	-L$$DESTDIR \
	-Wl,--unresolved-symbols=report-all \
	-Wl,--gc-sections \
	-Wl,-rpath,./

LIBS += \
	-l:libboost_system.a \
	-l:libboost_filesystem.a \
	-l:libproxygenhttpserver.a \
	-l:libproxygenlib.a \
	-l:libwangle.a \
	-l:libfolly.a \
	-lglog \
	-lgflags \
	-lpthread \
	-lz \
	-ldouble-conversion \
	-lssl \
	-lcrypto \
	-l:libevent-2.0.so.5.1.9

CONFIG(debug, debug|release) {
	LIBS += \
		-lauxiliary_debug

} else {
	LIBS += \
		-lauxiliary \
		-O3
}

QMAKE_LFLAGS_RELEASE -= -Wl,-O0 -Wl,-O1 -Wl,-O2
QMAKE_LFLAGS_RELEASE *= -Wl,-O3

#-------------------------------------------------------------------------------------------------
# dependencies
#-------------------------------------------------------------------------------------------------

postprocess.commands = objcopy $$DESTDIR/apigate $$DESTDIR/apigate_dist --strip-debug --strip-unneeded --target elf64-x86-64
#copydata.commands = cp -f -v \
#	/usr/lib/libevent-2.0.so.5 \
#	$$_PRO_FILE_PWD_/../tbb/lib/intel64/gcc4.4/libtbb.so.2 \
#	$$DESTDIR

first.depends = $(first) postprocess
export(first.depends)
export(postprocess.commands)

QMAKE_EXTRA_TARGETS += first postprocess

#------------------------------------------------------------------------------------------------
# files
#-------------------------------------------------------------------------------------------------
SOURCES += \
	platform/linux/main.cpp \
    source/Proxygen/ProxygenServer.cpp \
    source/Endpoint/ProxygenEndpoint.cpp

HEADERS += \
	platform/linux/platform.h \
    source/Proxygen/ProxygenServer.h \
    source/Endpoint/ProxygenEndpoint.h
