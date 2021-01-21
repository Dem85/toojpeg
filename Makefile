TOOLCHAIN?=
CPP=$(TOOLCHAIN)g++
STRIP = $(TOOLCHAIN)strip

LDFLAGS+=-lrt -DWRTPLATFORM_TYPE=$(WRTPLATFORM)

DEPS=test.cpp toojpeg.cpp

LINKER   = $(CPP) -o

SRCDIR   = ./
OBJDIR   = ./
BINDIR   = ./
INSTALLDIR = release

#SOURCES  := $(wildcard $(SRCDIR)/*.c)
SOURCES  := $(DEPS)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
#OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJECTS  := $(SOURCES:%.cpp=$(OBJDIR)/%.o)
TARGET   := test
rm       = rm -f

CPPFLAGS=-std=c++11

all: $(BINDIR)/$(TARGET) test888 test565

$(BINDIR):
	mkdir $(BINDIR)

$(INSTALLDIR)/$(BINDIR):
	mkdir $(INSTALLDIR)/$(BINDIR)

$(BINDIR)/$(TARGET): $(OBJECTS) $(BINDIR)
	$(CPP) $(OBJECTS) $(LDFLAGS) -o $@
	$(STRIP) $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLUDES)
	$(CPP) $(CPPFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	$(rm) $(OBJECTS)

.PHONEY: remove
remove: clean
	$(rm) $(BINDIR)/$(TARGET)

test888:
	./test 160 120 3 < rgb888.raw > test888.jpeg

test565:
	./test 160 120 2 < rgb565.raw > test565.jpeg

