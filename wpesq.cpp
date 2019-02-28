// wpesq.cpp : 定义控制台应用程序的入口点。
//
#if 1
//#include "stdafx.h"
#include<string.h>

#include <iostream>
//#include <io.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <dirent.h>
using namespace std;

double extern start(int argc, const char *argv []);
#define MAX_PATH_LEN 256
#define MAX_PARA_NUM 20
#define MAX_FILE_NUM 20000

#ifndef _TEST_LINUX_
int get_dir_file_list(char *dirpath,char filepathlist[][MAX_PATH_LEN], int & num)
{
	DIR *dir;
	struct dirent *ptr;
	//int num=0;
	if((dir=opendir(dirpath))==NULL)
	{
		printf("dir path error!\n");
		return -1;
	}
	//printf("first num = %d",num);
	while((ptr=readdir(dir))!=NULL)
	{
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
		{
			continue;
		}		
		else
		{
		//	printf("file name is num %d = %s\n",num,ptr->d_name);
			strcpy(filepathlist[num],ptr->d_name);
			//files.push_back(p.assign(path).append("/").append(fileinfo.name));
			num++;	
		}
	}
	//for(int j = 0; j < num;j ++ )
		//printf("filepathlist = %s\n",filepathlist[j]);
	closedir(dir);
	return 0;
}
#else

void getAllFiles(string path, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;  //很少用的文件信息读取结构
	string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //比较文件类型是否是文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("/").append(fileinfo.name));
					getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}
#endif
int main(int argc, char* argv[])
{
	char tmp[MAX_PARA_NUM][MAX_PATH_LEN]={0};
	const char *pargv[MAX_PARA_NUM]={NULL};
	vector<string> files;

	if(argc < 4)
	{
		printf("para error!,argc=%d\n",argc);
		return -1;
	
	}

	for(int i = 1 ;i< argc ;i ++)
	{
		int len = strlen(argv[i]);
		memcpy(tmp[i],argv[i],len * sizeof(char));
		pargv[i] = tmp[i];
	}
	const char* inPath = pargv[2];
	char filepathlist[MAX_FILE_NUM][MAX_PATH_LEN]={0};
	int num;
	get_dir_file_list((char *)inPath,filepathlist,num);
	string tmp_path  = inPath;
	for(int i = 0;i < num;i++)
	{	
		string strmer = tmp_path;
		string strfile = filepathlist[i];
		string res = strmer + strfile;
		pargv[2] = res.c_str();		

		start(argc,pargv);
	}
	return 0;
}
#endif

