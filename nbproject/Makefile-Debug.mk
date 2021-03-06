#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/app_client.o \
	${OBJECTDIR}/app_server.o \
	${OBJECTDIR}/app_settings.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/ocr_parser.o \
	${OBJECTDIR}/ocr_region.o \
	${OBJECTDIR}/ocr_region_process.o \
	${OBJECTDIR}/ocr_regionoperation.o \
	${OBJECTDIR}/ocr_regionvalidator.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`Magick++-config --cppflags --cxxflags --ldflags --libs ; pkg-config --cflags --libs libxml++-2.6` -fopenmp 
CXXFLAGS=`Magick++-config --cppflags --cxxflags --ldflags --libs ; pkg-config --cflags --libs libxml++-2.6` -fopenmp 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-ltesseract -llept

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/psnocr

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/psnocr: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/psnocr ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/app_client.o: app_client.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/app_client.o app_client.cpp

${OBJECTDIR}/app_server.o: app_server.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/app_server.o app_server.cpp

${OBJECTDIR}/app_settings.o: app_settings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/app_settings.o app_settings.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/ocr_parser.o: ocr_parser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ocr_parser.o ocr_parser.cpp

${OBJECTDIR}/ocr_region.o: ocr_region.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ocr_region.o ocr_region.cpp

${OBJECTDIR}/ocr_region_process.o: ocr_region_process.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ocr_region_process.o ocr_region_process.cpp

${OBJECTDIR}/ocr_regionoperation.o: ocr_regionoperation.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ocr_regionoperation.o ocr_regionoperation.cpp

${OBJECTDIR}/ocr_regionvalidator.o: ocr_regionvalidator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/ImageMagick-6 -I/usr/include/libxml++-2.6 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ocr_regionvalidator.o ocr_regionvalidator.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/psnocr

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
