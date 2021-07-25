TARGET = newton
OBJS = newton.o platform.o entities.o input.o levels.o texship.o texpixel.o texplanet.o texpress.o texgoal.o texmove.o

INCDIR =
CFLAGS = -G0 -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Newton Voyage
PSP_EBOOT_ICON= icon0.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

texship.o: texship.raw
	bin2o -i texship.raw texship.o texship
texplanet.o: texplanet.raw
	bin2o -i texplanet.raw texplanet.o texplanet
texpixel.o: texpixel.raw
	bin2o -i texpixel.raw texpixel.o texpixel
texpress.o: texpress.raw
	bin2o -i texpress.raw texpress.o texpress
texmove.o: texmove.raw
	bin2o -i texmove.raw texmove.o texmove
texgoal.o: texgoal.raw
	bin2o -i texgoal.raw texgoal.o texgoal