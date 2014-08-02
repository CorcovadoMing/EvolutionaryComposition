all:
	@echo "====== Compile phase ====== "
	@echo "Compiling ... "
	@g++ -O2 -std=c++11 ./src/*.cpp -o ./handler/main
	@echo "Compiling ...OK! "
	
	@echo "====== Runing phase====== "
	@echo "Runing ... "
	@echo "Fist Evolution start ..."
	@./handler/main >> report
	@echo "Write to report file ..."
	@echo "Done!"
	
	@echo "Generateing ... "
	@./handler/pypy/bin/pypy -O ./handler/generatewave1.py
	@./handler/pypy/bin/pypy -O ./handler/generatewave2.py
	@./handler/pypy/bin/pypy -O ./handler/generatewave3.py
	@./handler/pypy/bin/pypy -O ./handler/generatewave4.py
	
	@echo "Synthesizing ... "
	@python2 -O ./handler/combine.py
	@echo "OK!"
	
evol:
	@echo "Evolution start ..."
	@./handler/main >> report
	@echo "Write to report file ..."
	@echo "Done!"
	
clean:
	@echo "======= Cleaning ======"
	@rm *.wav ./handler/generatewave* ./handler/main report Music
	@echo "Done!"
