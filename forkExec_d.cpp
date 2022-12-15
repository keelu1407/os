#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() {
	int pid;
	pid = fork();
	if (pid<0) {
		cout << "Fork failed";
		exit(-1);
	}
	else if(pid==0) {
		cout << "Child id is: " << pid << endl;
	}
	else {
		wait(NULL);
		cout << "Parent id is: " << pid << endl;
		exit(0);
	}
}
