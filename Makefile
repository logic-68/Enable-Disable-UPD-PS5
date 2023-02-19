CC       := gcc
AS       := gcc
ODIR     := build
SDIR     := source
LIBPS4   := include/libPS4/source
LIBPS5   := include/libPS5/source
ORBISDIR := include/orbis/source
IDIRS    := -I. -Iinclude
LDIRS    := -L. -Llib
CFLAGS   := $(IDIRS) -fno-builtin -nostdlib -Wall -m64 -fPIC -mcmodel=small
SFLAGS   := -fno-builtin -nostartfiles -nostdlib -fPIC -mcmodel=small
LFLAGS   := $(LDIRS) -Xlinker -T linker.x -Wl,--build-id=none
CFILES   := $(wildcard $(SDIR)/*.c) $(wildcard $(LIBPS4)/*.c) $(wildcard $(LIBPS5)/*.c) $(wildcard $(ORBISDIR)/*.c)
SFILES   := $(wildcard $(SDIR)/*.s) $(wildcard $(LIBPS4)/*.s) $(wildcard $(LIBPS5)/*.s) $(wildcard $(ORBISDIR)/*.s)
OBJS     := $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SFILES)) $(patsubst $(LIBPS4)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(LIBPS4)/%.s, $(ODIR)/%.o, $(SFILES)) $(patsubst $(LIBPS5)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(LIBPS5)/%.s, $(ODIR)/%.o, $(SFILES)) $(patsubst $(ORBISDIR)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(ORBISDIR)/%.s, $(ODIR)/%.o, $(SFILES))

LIBS :=

TARGET = Enable-Desable-UPD-PS5.elf

$(TARGET): $(ODIR) $(OBJS)
	$(CC) crt0.s $(ODIR)/*.o -o $(TARGET) $(CFLAGS) $(LFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.s
	$(AS) -c -o $@ $< $(SFLAGS)

$(ODIR)/%.o: $(LIBPS4)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(LIBPS4)/%.s
	$(AS) -c -o $@ $< $(SFLAGS)

$(ODIR)/%.o: $(LIBPS5)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(LIBPS5)/%.s
	$(AS) -c -o $@ $< $(SFLAGS)	

$(ODIR)/%.o: $(ORBISDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(ORBISDIR)/%.s
	$(AS) -c -o $@ $< $(SFLAGS)

$(ODIR):
	@mkdir $@

.PHONY: clean

clean:
	rm -f $(shell basename $(CURDIR)).elf $(TARGET) $(ODIR)/*.o