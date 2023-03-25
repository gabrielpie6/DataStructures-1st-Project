Tool.exe: main.o drawSvg.o geometry.o cmdsFiles.o lista.o entity.o fila.o
	cc -o Tool.exe main.o drawSvg.o geometry.o cmdsFiles.o lista.o entity.o fila.o

main.o: main.c drawSvg.h geometry.h
	cc -c main.c
drawSvg.o: drawSvg.c drawSvg.h
	cc -c drawSvg.c
geometry.o: geometry.c geometry.h
	cc -c geometry.c
cmdsFiles.o: cmdsFiles.c cmdsFiles.h
	cc -c cmdsFiles.c
lista.o: lista.c lista.h dataTypes.h
	cc -c lista.c
entity.o: entity.c entity.h
	cc -c entity.c
fila.o: fila.c fila.h dataTypes.h
	cc -c fila.c