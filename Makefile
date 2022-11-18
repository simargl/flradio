CC = g++
CFLAGS = -g -I./include
LDFLAGS = `fltk-config --ldstaticflags --use-images` `fltk-config --cxxflags --use-images` -lbass64 -L./lib
PROG = build/linux/flradio.bin
OBJS = build/linux/play.o build/linux/stations.o build/linux/gui.o
WINFLAGS = -I./include -DWIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -L./lib -mwindows -lfltk_images -lpng -lz -ljpeg -lfltk -lole32 -luuid -lcomctl32 -lbass

all: flradio.bin

flradio.bin: gui.o play.o stations.o
	${CC} $(OBJS) -o $(PROG) ${CFLAGS} ${LDFLAGS}
	cp lib/libbass64.so data/flradio.png data/flradio build/linux/
	rm build/linux/*.o
	chmod 755 build/linux/flradio

gui.o:
	${CC} ${CFLAGS} -c src/gui.cxx -o build/linux/gui.o

play.o:
	${CC} ${CFLAGS} -c src/play.cxx -o build/linux/play.o

stations.o:
	${CC} ${CFLAGS} -c src/stations.cxx -o build/linux/stations.o

clean: 
	rm -f build/linux/*

win: 
	${CC} -o 'build/windows/flradio.exe' 'src/gui.cxx' 'src/play.cxx' 'src/stations.cxx' ${WINFLAGS} 
	cp lib/*.dll build/windows/

bundle:
	make install DESTDIR=/tmp/1
	mksquashfs /tmp/1 flradio.sb -noappend
	make clean
	rm -r /tmp/1

zip: all
	zip -r flradio.zip build/linux/ -j 2

install: all
	install -Dm755 data/flradio $(DESTDIR)/usr/local/bin/flradio
	install -Dm644 data/flradio.desktop $(DESTDIR)/usr/share/applications/flradio.desktop
	install -Dm755 build/linux/flradio.bin $(DESTDIR)/usr/local/share/flradio/flradio.bin
	install -Dm644 build/linux/flradio.png $(DESTDIR)/usr/local/share/flradio/flradio.png
	install -Dm644 build/linux/libbass64.so $(DESTDIR)/usr/local/share/flradio/libbass64.so
	install -d $(DESTDIR)/usr/share/icons/hicolor/64x64/apps
	ln -sf ../../../../../local/share/flradio/flradio.png $(DESTDIR)/usr/share/icons/hicolor/64x64/apps/flradio.png 

uninstall:
	rm $(DESTDIR)/usr/local/bin/flradio
	rm $(DESTDIR)/usr/share/applications/flradio.desktop
	rm -r $(DESTDIR)/usr/local/share/flradio
	rm $(DESTDIR)/usr/share/icons/hicolor/64x64/apps/flradio.png 

