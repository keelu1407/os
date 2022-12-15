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
	else if (pid == 0) {
		execlp("/bin/ls", "ls", NULL);
	}
	else {
		cout << "CHILD COMPLETE\n";
		exit(0);
	}
}
