#include <stdio.h>
#include <iostream>

#include "EasyNetServiceServer.h"

#ifdef WIN32
#include <crtdbg.h>
#endif

using namespace std;


uint16_t g_uUdpPort = 4657;

void LogErrorHook(std::string _szLog)
{
    throw _szLog;
}

void PrintUsage(void)
{
	cout << "Usage: EasyNetServiceServer [-u (udpport)]" << endl;
	cout << "such as : \"EasyNetServiceClient -u 5678\"" << endl;
	cout << "default udpport is " << g_uUdpPort << endl;
}

int AnalyzeParam(int argc, char* argv[])
{
	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{
			char* pArgv = argv[i];
			if (pArgv[0] == '-')
			{
				switch (pArgv[1])
				{
				case 'u':
					g_uUdpPort = (uint16_t)atoi(argv[++i]);
					break;
				case 'h':
				default:
					PrintUsage();
					return -1;
				}
			}
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
    try
    {
        Log::m_gErrHook = LogErrorHook;
        if(AnalyzeParam(argc, argv) == 0)
		{
			EasyNetServiceServer ecs(g_uUdpPort,DEFAULTCFGFILE);
			printf("Press 'q' and RNTERTo Exit\r\n");
			while(getchar() != 'q')
			{
				DelayMs(100);
			}
		}
    }catch(...)
    { }
#if defined(WIN32) && defined(DEBUG)
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

