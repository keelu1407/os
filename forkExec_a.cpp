#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() {
	int pid;
	pid = fork();
	
	if (pid<0) {
		cerr << "Fork failed\n";
		exit(1);
	}
	else {
		cout << "Hello, my pid is " << pid << endl;
		exit(-1);
	}
}
