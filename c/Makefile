CC = /usr/bin/gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O3 
JDIR ::= /home/sabrinamanickam/jasmin/compiler
BASE_SOURCES ::= randombytes.c shake256.c poly.s poly.c $(JDIR)/syscall/jasmin_syscall.c 
BASE_HEADERS ::= params.h poly.h randombytes.h shake256.h
CMD_COMPILE ::= $(CC) $(CFLAGS) $(BASE_SOURCES) -I $(JDIR)/syscall 
COMPILE = $(CMD_COMPILE) -o $@
JASMINC ::= $(JDIR)/jasminc -lazy-regalloc 

CMD_COMPILED ::= $(CC) $(CFLAGS) -g $(BASE_SOURCES) -I $(JDIR)/syscall 
COMPILED = $(CMD_COMPILED) -o $@

#------------------------------------------
JPP ::= /home/sabrinamanickam/scripts/jpp
PREPROCESSOR ::= /home/sabrinamanickam/scripts/preprocessor 

$(JPP_FILES):
.PRECIOUS: bin/jazz_poly_getnoise.jpp
bin/jazz_poly_getnoise.jpp: | bin/
	cp jazz_poly_getnoise.jazz $@
	$(JPP) -I -in $@ -out $@
	$(PREPROCESSOR) --input_file $@ --output_file $@ 


$(TESTS):
bin/jazz_poly_getnoise: bin/jazz_poly_getnoise.s | bin/
	$(CC) $(CFLAGS) -o $@ -DOUTLEN=$(GET_OUTLEN) -DINLEN=$(GET_INLEN) -I../common -I../../ \
test_poly_getnoise.c $< ../
	
bin/:
	mkdir -p bin/
#------------------------------------------
all: test/test_poly_uniform \
     test/test_poly_add \
     test/test_poly_getnoise \
     test/test_poly_sub \
     test/test_poly_mul \
     test/test_poly_fromtobytes \
     test/test_poly_fromtomsg \
     test/test_pke \

poly.s: poly.jazz
	$(JASMINC) -o poly.s poly.jazz

test/test_poly_uniform: $(BASE_SOURCES) $(BASE_HEADERS) test/test_poly_uniform.c
	$(COMPILE) test/test_poly_uniform.c
	
test/test_poly_add: $(BASE_SOURCES) $(BASE_HEADERS) test/test_poly_add.c
	$(COMPILE) test/test_poly_add.c

test/test_poly_sub: $(BASE_SOURCES) $(BASE_HEADERS) test/test_poly_sub.c
	$(COMPILE) test/test_poly_sub.c
	
test/test_poly_mul: $(BASE_SOURCES) $(BASE_HEADERS) test/test_poly_mul.c
	$(COMPILE) test/test_poly_mul.c

test/test_poly_getnoise: $(BASE_SOURCES) $(BASE_HEADERS) test/test_poly_getnoise.c
	$(COMPILED) test/test_poly_getnoise.c

test/test_poly_fromtobytes: $(BASE_SOURCES) $(BASE_HEADERS) test/test_poly_fromtobytes.c
	$(COMPILE) test/test_poly_fromtobytes.c

test/test_poly_fromtomsg: $(BASE_SOURCES) $(BASE_HEADERS) test/test_poly_fromtomsg.c
	$(COMPILE) test/test_poly_fromtomsg.c
	
test/test_pke: $(BASE_SOURCES) $(BASE_HEADERS) test/test_pke.c
	$(COMPILE) test/test_pke.c
	
.PHONY: clean test

test: all
	bash test/test.sh

clean:
	rm -f test/test_pke \
	test/test_poly_uniform \
	test/test_poly_getnoise \
	test/test_poly_add \
	test/test_poly_sub \
	test/test_poly_mul \
	test/test_poly_fromtobytes \
	test/test_poly_fromtomsg \
	poly.s \
