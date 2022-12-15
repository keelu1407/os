#include <iostream>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

int main() {
	int pid;
	pid = fork();
	if (pid < 0) {
		cerr << "Fork failed";
		exit(-1);
	}
	else if (pid > 0) {
		cout << "Helllo my pid is " << pid << endl;
	}
	else {
		cout << "Hi, my pid is" << pid << endl;
	}
	exit(0);
}
