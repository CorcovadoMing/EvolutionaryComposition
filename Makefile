OD=handler
PY=python -O

all:
	@echo "====== Compile phase ====== "
	@echo "Compiling ... "
	@cd $(OD); cmake ../src; make
	@echo "Compiling ...OK! "
	
	@echo "====== Runing phase====== "
	@echo "Runing ... "
	@echo "Fist Evolution start ..."
	@./$(OD)/main >> report
	@echo "Write to report file ..."
	@echo "Done!"
	
	@echo "Generateing ... "
	@$(PY) $(OD)/generatewave1.py
	@$(PY) $(OD)/generatewave2.py
	@$(PY) $(OD)/generatewave3.py
	@$(PY) $(OD)/generatewave4.py
	
	@echo "Synthesizing ... "
	@$(PY) $(OD)/combine.py
	@echo "OK!"

evol:
	@echo "Evolution start ..."
	@./$(OD)/main >> report
	@echo "Write to report file ..."
	@echo "Done!"
	
clean:
	@echo "======= Cleaning ======"
	@cd $(OD); make clean;
	@rm *.wav report Music
	@cd $(OD); rm -r generatewave* cmake* CMake* Makefile
	@echo "Done!"
