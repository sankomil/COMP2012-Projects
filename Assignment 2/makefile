

ifeq (Windows_NT, $(OS))

lib       := ncurses_lib/pdcurses
flag      := -D_WIN_  
suf       := pdcurses.dll
linkflag  := -l$(lib)  -static -L".\\"
ifeq (, $(OSTYPE))
ziptool   := ./zip.exe
else
ziptool   := zip
endif
else
linkflag  := 
lib       := ncurses
flag      := -D_MAC_
ziptool   := zip
suf       := -l$(lib)
endif


TARGET    := pa2.exe
CFLAGS    := -Wall -std=c++11 $(flag) 
OBJDIR    := object
BASE      := Controller View Object Enemy Tower main
TODO      := TodoSimpleTower TodoCatapult TodoDiagonalEnemy TodoLaserTower TodoIceTower TodoRevivingEnemy TodoArena
BASE_OBJ  := $(addsuffix .o, $(addprefix $(OBJDIR)/, $(BASE)))
TODO_OBJ  := $(addsuffix .o, $(addprefix $(OBJDIR)/, $(TODO)))

all: build pa2.zip 

build: create_directory $(TARGET)


create_directory: object 

object:
	@mkdir -p $(OBJDIR) 
		
echo:
	@echo $(GUESS_OS)

pa2.exe: $(TODO_OBJ) $(BASE_OBJ)
	g++ $(CFLAGS) $(linkflag) -o $@ $(TODO_OBJ) $(BASE_OBJ) $(suf)
	
	
object/%.o: %.cpp 
	g++ $(CFLAGS) -c -o $@ $<

pa2.zip: $(addsuffix .cpp, $(TODO)) TodoSimpleTower.h TodoCatapult.h TodoDiagonalEnemy.h TodoLaserTower.h TodoIceTower.h TodoRevivingEnemy.h 
	@echo
	@echo "Preparing your pa2.zip - submit this to Canvas directly"
	@echo
	rm -f pa2.zip
	$(ziptool) pa2.zip Todo*

clean:
	rm -f $(TARGET) $(TODO_OBJ) $(BASE_OBJ)  
	
	
 