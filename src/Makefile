PROJ_NAME=ted

ALUNO=gabrielpietsiaki
LIBS=drawSvg.h geometry.h cmdsFiles.h lista.h entity.h fila.h analyticGeometry.h actions.h path.h geoFile.h qryFile.h
OBJETOS=main.o drawSvg.o geometry.o cmdsFiles.o lista.o entity.o fila.o analyticGeometry.o actions.o path.o geoFile.o qryFile.o

# compilador
CC=gcc

# Flags
CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration
LDFLAGS=-O0

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS)  $(OBJETOS) $(LIBS) -lm

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

#
# COLOCAR DEPENDENCIAS DE CADA MODULO
#

# Exemplo: suponha que o arquivo a.c possua os seguintes includes:
#
#   #include "a.h"
#   #include "b.h"
#   #include "c.h"
# 
# a.o: a.h b.h c.h a.c


#
# EMPACOTAR PARA ENTREGA
#
#   -  se necessario: sudo apt install zip

pack: $(PROJ_NAME)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	cd ..; date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/*.c src/*.h src/Makefile LEIA-ME.txt .entrega
