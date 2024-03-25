
CXXFLAGS = -O1

gradeVector : duomenuGeneravimas.o duomenuSkaiciavimai.o gradeVector.cpp
	g++ $(CXXFLAGS) -o gradeVector gradeVector.cpp duomenuGeneravimas.o duomenuSkaiciavimai.o 

duomenuGeneravimas :
	g++ $(CXXFLAGS) -c duomenuGeneravimas.cpp

duomenuSkaiciavimai :
	g++ $(CXXFLAGS) -c duomenuSkaiciavimai.cpp 

clean :
	del *.o gradeVector
