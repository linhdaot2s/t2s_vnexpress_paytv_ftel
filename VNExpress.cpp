#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <directfb.h>
#include "CVNEApp.h"

int main(int argc, char *argv[])
{	
	CVNEApp *pCVNEApp = new CVNEApp();
	pCVNEApp->Onload();
	sleep(9000);
	return 1;
}