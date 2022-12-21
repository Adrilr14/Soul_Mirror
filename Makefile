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


#
APP 		:= soulMirror
CPU 		:= x86_64
ASAN_FLAGS 	:= -fsanitize=address -fno-omit-frame-pointer
CCFLAGS		:= $(ASAN_FLAGS) -Wall -pedantic -O2 -m64 -std=c++17 -ggdb3
CFLAGS 		:= $(CCFLAGS)
CC 		:= g++ -pthread
C 		:= gcc
MKDIR 		:= mkdir -p
SRC 		:= src
OBJ 		:= obj
LIBDIR 		:= lib
IrrlichtHome	:= lib/irrlicht/src
openGLHome 	:= openGL
Core		:= core
Studio		:= studio
FMODHome 	:= lib/apiFMOD
LOWLEVEL_LIB 	:= lib/Linux/apiFMOD/core/lib/${CPU}/libfmod${SUFFIX}.so
STUDIO_LIB 		:= lib/Linux/apiFMOD/studio/lib/${CPU}/libfmodstudio${SUFFIX}.so
IRRLICHT_LIB 	:= lib/Linux/irrlicht/libIrrlicht.so.1.8.4
GL_LIB 			:= lib/Linux/openGL/gl/libGL.so
GLU_LIB 		:= lib/Linux/openGL/libGLU.so
GLFW_LIB 		:= lib/Linux/openGL/glfw/libglfw.so
GLEW_LIB 		:= lib/Linux/openGL/glew/libGLEW.so
SOIL_LIB		:= lib/Linux/openGL/soil/libSOIL.a

BULLET_LIB_1	:= lib/Linux/Bullet/libBulletCollision.so
BULLET_LIB_2	:= lib/Linux/Bullet/libBulletDynamics.so
BULLET_LIB_3	:= lib/Linux/Bullet/libBulletInverseDynamics.so
BULLET_LIB_4	:= lib/Linux/Bullet/libLinearMath.so
BULLET_LIB_5	:= lib/Linux/Bullet/libBullet3Collision.so
BULLET_LIB_6	:= lib/Linux/Bullet/libBullet3Common.so
BULLET_LIB_7	:= lib/Linux/Bullet/libBullet3Dynamics.so
BULLET_LIB_8	:= lib/Linux/Bullet/libBullet3Geometry.so
BULLET_LIB_9	:= lib/Linux/Bullet/libBullet3OpenCL_clew.so
BULLET_LIB_10	:= lib/Linux/Bullet/libBullet2FileLoader.so
BULLET_LIB_11	:= lib/Linux/Bullet/libBulletSoftBody.so

LIBS 		:= -lX11 -lXext -Wl,-rpath=\$$ORIGIN/$(dir ${LOWLEVEL_LIB}),-rpath=\$$ORIGIN/$(dir ${STUDIO_LIB}) ${LOWLEVEL_LIB} ${STUDIO_LIB} -Wl,-rpath=\$$ORIGIN/$(dir ${IRRLICHT_LIB}) ${IRRLICHT_LIB} -Wl,-rpath=\$$ORIGIN/$(dir ${GLFW_LIB}) ${GLFW_LIB} -Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_1}) ${BULLET_LIB_1}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_2}) ${BULLET_LIB_2}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_3}) ${BULLET_LIB_3}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_4}) ${BULLET_LIB_4}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_5}) ${BULLET_LIB_5}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_6}) ${BULLET_LIB_6}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_7}) ${BULLET_LIB_7}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_8}) ${BULLET_LIB_8}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_9}) ${BULLET_LIB_9}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_10}) ${BULLET_LIB_10}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${BULLET_LIB_11}) ${BULLET_LIB_11}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${GLEW_LIB}) 	${GLEW_LIB} 
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${SOIL_LIB}) 	${SOIL_LIB}
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${GL_LIB}) 		${GL_LIB} 
LIBS		+=	-Wl,-rpath=\$$ORIGIN/$(dir ${GLU_LIB}) 		${GLU_LIB} 
INCDIRS		:= -I$(SRC) -I$(LIBDIR) -I./include/irrlicht/include -I./include/fmod/core/inc -I./include/fmod/studio/inc -I./include/openGL/ -I./include/openGL/glfw -I./include/openGL/glm/ -I./include/fmod/core/inc -I./include/JSON/include -I./include/Bullet/ -I./include/openGL/glew/ -I./include/openGL/soil/ -I./include/openGL/OBJ-Loader/ 

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
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS) $(ASAN_FLAGS)


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
