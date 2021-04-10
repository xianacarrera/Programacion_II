#opciones de compilación, mostrando todos los warnings (-Wall)
CC = gcc -Wall

#carpeta de la cabecera
HEADER_FILES_DIR = .
#opciones de compilación, indicando el directorio del archivo .h
INCLUDES = -I $(HEADER_FILES_DIR)

#nombre del archivo de salida (ejecutable)
OUTPUT = div_ven

#fichero .h
LIB_HEADERS = $(HEADER_FILES_DIR)/matrizdinamica.h

#fuentes: main.c y matrizdinamica.c
SRCS = main.c $(LIB_HEADERS:.h=.c)

#ficheros .o: todos los .o con un análogo .c en SRCS
OBJS = $(SRCS:.c=.o)

#regla 1 (dependencia de los .o)
#esta regla crea el ejecutable con el programa
#sus dependencias son los archivos .o
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS)

#regla 2 
#con esta regla generamos los archivos .o a partir de sus correspondientes .c
#cuando un archivo .c cambie solo se volverá a recompilar ese .c, en lugar de todos ellos
#depende de los archivos .c y del archivo de cabecera .h
%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

#regla 3, que borra el ejecutable y ejecuta clean
cleanall: clean
	rm -f $(OUTPUT)

#regla 4, que borra los ficheros .o y los de backup (terminan en ~)
clean:
	rm -f *.o *~