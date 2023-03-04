.PHONY: clean
build:
	gcc -o walsh walsh.c
	gcc -o statistics statistics.c
	gcc -o prinel prinel.c -lm
	gcc -o crypto crypto.c
	

run-p1:      # nume necesar
	./walsh	
run-p2:      # nume necesar
	./statistics
run-p3:      # nume necesar
	./prinel
run-p4:      # nume necesar
	./crypto
clean:		 # nume necesar
	rm -f walsh
	rm -f statistics
	rm -f prinel
	rm -f crypto	
