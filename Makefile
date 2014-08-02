CXX=g++
OFLAGS=-O3 -std=c++11
WD=src
INC=-I/$(WD)
OD=handler
PYPY=$(OD)/pypy/bin/pypy

all:
	@echo "====== Compile phase ====== "
	@echo "Compiling ... "
	$(CXX) $(INC) $(OFLAGS) $(WD)/*.cpp -o $(OD)/main
	@echo "Compiling ...OK! "
	
	@echo "====== Runing phase====== "
	@echo "Runing ... "
	@echo "Fist Evolution start ..."
	@./$(OD)/main >> report
	@echo "Write to report file ..."
	@echo "Done!"
	
	@echo "Generateing ... "
	@$(PYPY) -O $(OD)/generatewave1.py
	@$(PYPY) -O $(OD)/generatewave2.py
	@$(PYPY) -O $(OD)/generatewave3.py
	@$(PYPY) -O $(OD)/generatewave4.py
	
	@echo "Synthesizing ... "
	@python -O $(OD)/combine.py
	@echo "OK!"
	
evol:
	@echo "Evolution start ..."
	@./$(OD)/main >> report
	@echo "Write to report file ..."
	@echo "Done!"
	
clean:
	@echo "======= Cleaning ======"
	@rm *.wav $(OD)/generatewave* $(OD)/main report Music
	@echo "Done!"
