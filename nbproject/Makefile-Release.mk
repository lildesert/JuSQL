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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/UI/Attribut.o \
	${OBJECTDIR}/UI/Relation.o \
	${OBJECTDIR}/UI/common.o \
	${OBJECTDIR}/UI/content_manager.o \
	${OBJECTDIR}/UI/files.o \
	${OBJECTDIR}/UI/interface.o \
	${OBJECTDIR}/UI/main.o \
	${OBJECTDIR}/UI/pages_manager.o \
	${OBJECTDIR}/UI/schema.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jusql

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jusql: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jusql ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/UI/Attribut.o: UI/Attribut.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Attribut.o UI/Attribut.cpp

${OBJECTDIR}/UI/Relation.o: UI/Relation.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Relation.o UI/Relation.cpp

${OBJECTDIR}/UI/common.o: UI/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/common.o UI/common.cpp

${OBJECTDIR}/UI/content_manager.o: UI/content_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/content_manager.o UI/content_manager.cpp

${OBJECTDIR}/UI/files.o: UI/files.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/files.o UI/files.cpp

${OBJECTDIR}/UI/interface.o: UI/interface.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/interface.o UI/interface.cpp

${OBJECTDIR}/UI/main.o: UI/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/main.o UI/main.cpp

${OBJECTDIR}/UI/pages_manager.o: UI/pages_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/pages_manager.o UI/pages_manager.cpp

${OBJECTDIR}/UI/schema.o: UI/schema.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/schema.o UI/schema.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jusql

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
