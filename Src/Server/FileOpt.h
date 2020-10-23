#pragma once
#include "stdio.h"
#include "string"

#if defined(WIN32)
#define CONFIGDIR "ens"
#else
#define CONFIGDIR ".ens"
#endif

class FileOpt
{
private:
    const std::string m_szConfigPath;
	const std::string m_szFileName;
	std::string m_szFileContent;

	void ReadFile(void);
    bool IsAccessible(std::string _szFileOrFir);   //判断文件是否存在以及是否可访问
    bool CreateCfgFile(std::string _szFilePath,std::string _szFileName,std::string _szDefaultText = "");
    bool CreateDefaultDirectory(std::string _szDirName);
    std::string GetConfigPath(void);
public:
    FileOpt(std::string _szFileName,std::string _szDefaultContent = "");
	~FileOpt();
	
	void ReflashFileContent(void);
	bool IsJsonContent(void);
	bool IsJsonArray(void);
	void ReWrite(std::string _szContent);
    std::string GetFilePath(void);
	std::string GetFileName(void);
	std::string GetFileContent(void);
};

