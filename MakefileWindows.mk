
##############################################
####	MACROS
##############################################

define COMPILER
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef



define C20
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.h,$(patsubst %.cpp,%.hpp,$(1))))
endef

ifeq (${CONFIG}, Debug)
    FLAGS += -g
    SUFFIX = L
else
    override CONFIG = Release
    FLAGS += -O2
    SUFFIX =
endif



APP 			:= Soul_Mirror.exe
CPU 			:= x86_64
CCFLAGS			:= -Wall -Wno-unknown-pragmas -std=gnu++1z -static-libgcc -static-libstdc++
CFLAGS 			:= $(CCFLAGS)
CC 				:= g++#x86_64-w64-mingw32-g++
C 				:= gcc
MKDIR 			:= mkdir -p
SRC 			:= src
OBJ 			:= obj
LIBDIR 			:= lib
IrrlichtHome	:= lib/irrlicht/src
openGLHome 		:= openGL
Core			:= core
Studio			:= studio
FMODHome 		:= lib/Windows/apiFMOD
FMOD_LIB 		:= -L./$(FMODHome) -lfmod -lfmodL -lfmodstudio -lfmodstudioL -Wl,-rpath=$(FMODHome)
IRRLICHT_DIR 	:= lib/Windows/irrlicht
IRRLICHT_LIB 	:= -L./$(IRRLICHT_DIR) -lIrrlicht -Wl,-rpath=$(IRRLICHT_DIR)
LIBS 			:=  $(IRRLICHT_LIB) $(FMOD_LIB)
INCDIRS			:= -I$(SRC) -I$(LIBDIR) -I./include/irrlicht/include -I./include/fmod/core/inc -I./include/fmod/studio/inc -I./include/openGL/include -I./include/fmod/core/inc -I./include/JSON/include 

#$(IrrlichtHome)/include -L$(IrrlichtHome)/lib/$(SYSTEM) -I$(FMODHome)/$(Core)/inc -I$(FMODHome)/$(Studio)/inc -I$(FMODHome)/$(Core)/inc -Ilib/openGL/include

ifdef DEBUG
	CCFLAGS += -g
else 
	CCFLAGS += -O3
endif


ALLCPPS 	:= $(shell find $(SRC)/ -type f -iname *.cpp)

ALLCS 		:= $(shell find $(SRC)/ -type f -iname *.c)

SUBDIRS 	:= $(shell find $(SRC)/ -type d)
OBJSUBDIRS 	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
ALLOBJ 		:= $(foreach F,$(ALLCPPS) $(ALLCS),$(call C20,$(F)))



.PHONY: info

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS)


$(foreach F,$(ALLCPPS),$(eval $(call COMPILER,$(CC),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILER,$(C),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))

#$(OBJ)/%.o : $(SRC)/%.c
#	$(C) -o $(patsubst $(SRC)%, $(OBJ)%,$@) -c $^ $(CFLAGS)

#$(OBJ)/%.o : $(SRC)/%.cpp
#	$(CC) -o $(patsubst $(SRC)%, $(OBJ)%,$@) -c $^ $(CCFLAGS)

info : 
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))

$(OBJSUBDIRS) : 
	$(MKDIR) $(OBJSUBDIRS)

clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"
