gradeDeque : duomenuGeneravimas.o duomenuSkaiciavimai.o gradeDeque.cpp
	g++ -O3 -o gradeDeque gradeDeque.cpp duomenuGeneravimas.o duomenuSkaiciavimai.o -Wall -Wextra -Werror

duomenuGeneravimas :
	g++ -c duomenuGeneravimas.cpp -Wall -Wextra -Werror

duomenuSkaiciavimai :
	g++ -c duomenuSkaiciavimai.cpp -Wall -Wextra -Werror

clean :
	rm -f *.o gradeDeque