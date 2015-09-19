/* 
 * Boost cpp tdd examples. 
 */

#define BOOST_TEST_MODULE Processes
#include <boost/test/included/unit_test.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define PROC_ARRAY_LENGTH 2

int newProcess(int n)
{
    return n;
}
int asize=0;
int aPIDs[2];

void spawnParentChild(int exitcode){
	pid_t pid;
	int rv;
	//int aPIDs[2];
	switch(pid = fork()) {
	case -1:
		perror("fork");  /* something went wrong */
		exit(1);		 /* parent exits */

	case 0:
		printf(" CHILD: This is the child process!\n");
		printf(" CHILD: My PID is %d\n", getpid());
		printf(" CHILD: My parent's PID is %d\n", getppid());
		printf(" CHILD: Enter my exit status (make it small): ");
		//scanf(" %d", &rv);
		printf(" CHILD: I'm outta here!\n");
		exit(exitcode);

	default:
		printf("PARENT: This is the parent process!\n");
		printf("PARENT: My PID is %d\n", getpid());
		printf("PARENT: My child's PID is %d\n", pid);
		printf("PARENT: I'm now waiting for my child to exit()...\n");
		wait(&rv);
		printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(rv));
		printf("PARENT: I'm outta here!\n");
	}
	aPIDs[0]=getpid();
	aPIDs[1]=getppid();
	asize=sizeof(aPIDs)/sizeof(aPIDs[0]);
	//printf("size : %d\n",size);
	//return size;
}

void sigint_handler(int sig)
{
 	write(0, "Ahhh! SIGINT!\n", 14);
}

int getSignal(){
	char s[200];
 	struct sigaction sa;
 	sa.sa_handler = sigint_handler;
 	sa.sa_flags = 0; // or SA_RESTART
 	sigemptyset(&sa.sa_mask);
 	if (sigaction(SIGINT, &sa, NULL) == -1) {
 		perror("sigaction");
 		exit(1);
 	}
 	printf("Enter a string:\n");
 	if (fgets(s, sizeof s, stdin) == NULL)
 		perror("fgets");
 	else 
 		printf("You entered: %s\n", s);
 	return 0;
}



//Unit Tests
BOOST_AUTO_TEST_SUITE(Processes);

BOOST_AUTO_TEST_CASE(TestProcesses)
{
	BOOST_CHECK_EQUAL(newProcess(1), 1);
	spawnParentChild(0);
	BOOST_CHECK_EQUAL(asize,PROC_ARRAY_LENGTH);
	BOOST_CHECK(aPIDs[0] > 1);
	BOOST_CHECK(aPIDs[1] > 1);
	BOOST_CHECK(aPIDs[0] > aPIDs[1]);
	BOOST_CHECK_EQUAL(getSignal(), 1);
}

BOOST_AUTO_TEST_SUITE_END()	


/* check these out
 * http://1code.codeplex.com/wikipage?title=IRPC
 * http://blog.eldruin.com/en/2011/04/inter-process-communication-pipe-fork-and-c-stl-streams/
 */
