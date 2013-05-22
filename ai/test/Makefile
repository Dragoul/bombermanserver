#------------------------------------------------------------------------------

SOURCE=*.cpp
MYPROGRAM=test
MYINCLUDES=""

MYLIBRARIES=fltk
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) -O2 -std=c++11 -lm -I$(MYINCLUDES) $(SOURCE) -o$(MYPROGRAM) -l$(MYLIBRARIES)

clean:

	rm -f $(MYPROGRAM)