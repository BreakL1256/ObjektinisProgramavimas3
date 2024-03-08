gradeVector : duomenuGeneravimas.o duomenuSkaiciavimai.o
	g++ -o gradeVector -g -Wall -Werror gradeVector.cpp duomenuGeneravimas.o duomenuSkaiciavimai.o

duomenuGeneravimas :
	g++ -c duomenuGeneravimas.cpp

duomenuSkaiciavimai :
	g++ -c duomenuSkaiciavimai.cpp

clean :
	rm -f *.o gradeVector