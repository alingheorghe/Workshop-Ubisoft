#include "MyGL.h"

int main(int argc, char* argv[]){
	std::cout << "Introduceti codul formei geometrice dorite:" << std::endl;
	std::cout << "1.Triunghi" << std::endl;
	std::cout << "2.Patrat" << std::endl;
	std::cout << "3.n'Th-agon" << std::endl;
	std::cout << "4.Doua triunghiuri colorate diferit." << std::endl;
	int optiune = 0;
	int n = 0;
	std::cin >> optiune;

	if(optiune == 3){
		std::cout << "Cati vertecsi sa aiba forma geometrica ? " << std::endl;
		std::cin >> n;
	}
	
	MyGL mygl;
	mygl.initGL();
	mygl.runGL(optiune, n);
	return 1;
}