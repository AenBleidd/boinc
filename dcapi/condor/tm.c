/* Local variables: */
/* c-file-style: "linux" */
/* End: */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "dc.h"

#include "tc.h"

DC_Workunit *wu[10];

extern char *_DC_state_name(DC_WUState state);

static void
fail(char *what, int ret)
{
	printf("%s failed: %d\n", what, ret);
	exit(ret);
}

static DC_Workunit *
create_short(void)
{
	DC_Workunit *wu;
	
	printf("Creating short...\n");
	wu= DC_createWU("short", NULL, 0, NULL);
	printf("Created short wu: %p\n", wu);
	if (!wu)
		fail("DC_createWU", 0);
	return(wu);
}

static DC_Workunit *
create_long(int how_long)
{
	DC_Workunit *wu;
	char *argv[]= {
		"15",
		"2",
		"3",
		"2",
		NULL
	};
	char l[100];

	printf("Creating long...\n");
	if (how_long > 0)
	{
		sprintf(l, "%d", how_long);
		argv[0]= l;
	}
	wu= DC_createWU("long", (const char **)argv, 0, NULL);
	printf("Created short wu: %p\n", wu);
	if (!wu)
		fail("DC_createWU", 0);
	return(wu);
}

static void
result_cb(DC_Workunit *wu, DC_Result *result)
{
	printf("\nresult_cb, wustate=%s\n",
	       _DC_state_name(DC_getWUState(wu)));
	printf("exit= %d\n", DC_getResultExit(result));
}

static void
subresult_cb(DC_Workunit *wu,
	     const char *logical_file_name,
	     const char *path)
{
	printf("\nsubresult_cb, wustate=%s\n",
	       _DC_state_name(DC_getWUState(wu)));
	printf("logical= \"%s\"\n", logical_file_name);
	printf("path   = \"%s\"\n", path);
	printf("Content: \"%s\"\n", get_file((char*)path));
	printf("Deleting %s...\n", path);
	unlink(path);
}

static void
message_cb(DC_Workunit *wu, const char *message)
{
	printf("\nmessage_cb, wustate=%s\n",
	       _DC_state_name(DC_getWUState(wu)));
	printf("Message= \"%s\"\n", message);
}


static void
ls_lR(int i)
{
	char cmd[100];
	sprintf(cmd, "./ls_lR.sh %03d", i);
	//system(cmd);
}

int cycle= 0;

static void
process(DC_Workunit *wu, int timeout)
{
	printf("-- %3d %s\n", cycle, _DC_state_name(DC_getWUState(wu)));
	DC_processMasterEvents(timeout);
}

static void
procs(DC_Workunit *wu, DC_WUState state, int timeout)
{
	while (DC_getWUState(wu) != state)
	{
		cycle++;
		process(wu, timeout);
	}
}

static void
proci(DC_Workunit *wu, int nr, int timeout)
{
	int j;
	for (j= 0; j < nr; j++)
	{
		cycle++;
		process(wu, timeout);
	}
}

static void
t(int what)
{
	DC_Workunit *wu;

	switch (what)
	{
	case 1:
	{
		int i= 0;
		printf("test1: running a short wu\n");
		wu= create_short();
		printf("Submitting short...\n");
		if ((i= DC_submitWU(wu)) != 0)
			fail("DC_submitWU", i);
		DC_setMasterCb(result_cb, subresult_cb, message_cb);
		while (DC_getWUState(wu) != DC_WU_FINISHED)
		{
			printf("Processing events for 1 sec...\n");
			DC_processMasterEvents(1);
		}
		printf("Destroying short...\n");
		DC_destroyWU(wu);
		break;
	}
	case 2:
	{
		int i, j;
		printf("test2: running a long wu\n");
		wu= create_long(0);
		printf("Submitting long...\n");
		if ((i= DC_submitWU(wu)) != 0)
			fail("DC_submitWU", i);
		DC_setMasterCb(result_cb, subresult_cb, message_cb);
		while (DC_getWUState(wu) != DC_WU_FINISHED)
		{
			i++;
			printf("Processing events for 1 sec...\n");
			printf("-- %3d\n", i);
			ls_lR(i);
			DC_processMasterEvents(1);
		}
		printf("wu finished, but checking events for more 5 secs...\n");
		for (j= 0; j < 5; j++)
		{
			i++;
			printf("-- %3d\n", i);
			ls_lR(i);
			DC_processMasterEvents(1);
		}
		printf("Destroying long...\n");
		DC_destroyWU(wu);
		break;
	}
	case 3:
	{
		int r;
		printf("test3: suspend/resume\n");
		wu= create_long(20);
		printf("Submitting long...\n");
		if ((r= DC_submitWU(wu)) != 0)
			fail("DC_submitWU", r);
		DC_setMasterCb(result_cb, subresult_cb, message_cb);

		printf("waiting to be running...\n");
		procs(wu, DC_WU_RUNNING, 1);
		
		printf("now running, run a bit...\n");
		proci(wu, 5, 1);

		printf("Suspending wu...\n");
		if ((r= DC_suspendWU(wu)) != 0)
			fail("DC_suspendWU", r);

		printf("waiting to be suspended...\n");
		procs(wu, DC_WU_SUSPENDED, 1);

		printf("now suspended, wait a bit...\n");
		proci(wu, 5, 1);

		printf("Resuming wu...\n");
		if ((r= DC_resumeWU(wu)) != 0)
			fail("DC_resumeWU", r);

		printf("waiting to be running again...\n");
		procs(wu, DC_WU_RUNNING, 1);
		
		printf("waiting to finish...\n");
		procs(wu, DC_WU_FINISHED, 1);
		
		printf("Destroying long...\n");
		DC_destroyWU(wu);
		break;
	}
	}
}


int
main(int argc, char *argv[])
{
	int i;

	if ((i= DC_initMaster("t.conf")) != 0)
		fail("DC_initMaster", i);

	if (argc < 2)
	{
		printf("Calling all tests...\n");
		t(1);
		t(2);
		t(3);
	}

	for (i= 1; i < argc; i++)
	{
		int l;
		l= strtol(argv[i], 0, 0);
		printf("Calling test %d...\n", l);
		t(l);
	}

	return 0;
}
