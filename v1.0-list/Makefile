gradeList : duomenuGeneravimas.o duomenuSkaiciavimai.o gradeList.cpp
	g++ -O3 -o gradeList gradeList.cpp duomenuGeneravimas.o duomenuSkaiciavimai.o -Wall -Wextra -Werror

duomenuGeneravimas :
	g++ -c duomenuGeneravimas.cpp -Wall -Wextra -Werror

duomenuSkaiciavimai :
	g++ -c duomenuSkaiciavimai.cpp -Wall -Wextra -Werror

clean :
	rm -f *.o gradeList