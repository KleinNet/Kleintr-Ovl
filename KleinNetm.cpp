	/*
	#---------------------------------------------------------------------------------------#
	#                                 My Klein Computer                                     #
	#                                      V0.0.2                                           # 
	#                                      Inc.SHO                                          #
	#                                 C++ code-Provide                                      #
	#                                                                                       #
	#---------------------------------------------------------------------------------------#
	#language:Chinese
			  English
	#---------------------------------------------------------------------------------------#
	#更新:                                          
	#v0.0.2                                         //基本命令和开机界面的实现
	#v0.0.3                                         //文件系统上线，解决了文件系统bug
	#v0.0.4                                         //加入了对文件的操作指令flst
	#---------------------------------------------------------------------------------------#
	#qq群     981225898
	*/
	//定义启动服务所需的头文件
	#include <iostream>             //标准头文件
	#include <unistd.h>             //延时用
	#include <stdlib.h>             //随机数要用到,还有system要用到
	#include <math.h>               //一些数学运算要用
	#include <algorithm>　　　      //通用算法
	#include <bitset>　　　　　     //位集容器
	#include <cctype>              //别问我不想说
	#include <cerrno>              //懒得说
	#include <clocale>             //懒得说 
	#include <cmath>               //数学运算
	#include <complex>　　　　      //复数类
	#include <cstdio>              //
	#include <cstdlib>             //c中的
	#include <cstring>             //c中的字符串处理
	#include <ctime>               //时间处理
	#include <deque>　　　　　      //双端队列容器
	#include <exception>　　　      //异常处理类
	#include <fstream>             //
	#include <functional> 　　     //定义运算函数（代替运算符）
	#include <limits>              //
	#include <list>　　　　  　　   //线性列表容器
	#include <map>　　　　　　      //映射容器 
	#include <iomanip>             //
	#include <ios>　　　　　　      //基本输入／输出支持
	#include <iosfwd>　　　　      //输入／输出系统使用的前置声明
	#include <istream>　　　　     //基本输入流
	#include <ostream>　　　　     //基本输出流
	#include <queue>　　　　　     //队列容器
	#include <set>　　　　　　     //集合容器
	#include <sstream>　　　　     //基于字符串的流
	#include <stack>　　　　　     //堆栈容器　　　　
	#include <stdexcept>　　　     //标准异常类
	#include <streambuf>　　　     //底层输入／输出支持
	#include <string>　　　　　    //字符串类
	#include <utility>　　　　     //通用模板类
	#include <vector>　　　　      //动态数组容器
	#include <cwchar>             //
	#include <cwctype>            //
	//定义宏模组(关键字重定义)
	#define red "\033[31m"        //红色（下面的不解释了，英语学了）
	#define blue "\033[34m"
	#define small_blue "\033[36m"
	#define green "\033[32m"
	#define orange "\033[33m"
	#define purple "\033[35m"
	//带有BG标识的为背景颜色
	#define BG_red "\033[41m"
	#define BG_blue "\033[44m"
	#define BG_green "\033[42m"
	#define BG_orange "\033[43m"
	#define BG_white "\033[0m"
	//快捷函数关键字定义
	#define wait(x) sleep(x)   //真，延时用
	#define cls() system("clean")
	//后面在做延时时用到了waittime函数，利用这个宏做的一个内置函数
	#define uwait(x) usleep(x)  //毫秒级别延时
	//内部数据定义
	#define Mycomputerip "64.102.29.18"//我们自己的电脑ip
	#define Niccomputerip "109.66.102.68"//黑客Nic的电脑ip
	#define Tomcomputerip "183.102.34.98"//傻子Tom的电脑ip
	#define Harkcomputerip "123.10.109.5"//harkmonster组织首领的main电脑ip
	#define Mywebsite "klein.ml"//我们的网站
	#define MyDNSip "192.186.77.103"//我们网站域名服务器的ip（单ip服务器，小网站而已）
	//以下是待更新区域


	//其实下面这一部分代码有很多是从GHG得到的，我做了简化，把我的程序中不必要的组件删了

	using namespace std;
	//split函数，用于分割字符串，来自csdn
	vector<string> split(string str,string pattern)
	{
    	string::size_type pos;
    	vector<string> result;
    	str += pattern;//扩展字符串以方便操作
    	int size = str.size();
    	for (int i = 0; i < size; i++)
    	{
        	pos = str.find(pattern, i);
        	if (pos < size)
        	{
            	string s = str.substr(i, pos - i);
            	result.push_back(s);
            	i = pos + pattern.size() - 1;
        	}
    	}
    	return result;
	}

//类的定义以及函数的声明


	//定义一个文件类，存储文件
	class file;
	//定义一个电脑类，有系统消息
	class Computer;
	//定义一个文件夹类
	class dir;
	//一个处理输入的类
	class Process;
	//界面样式
	class Style;
    string finder_if(string code_str);

	typedef int (*adr_exe)(int agrc,vector<string> c);




//类的定义
	class file{
	public:
		string name;//文件名
		vector<string> content;//文件内容
		size_t size;//文件大小
		string* data;//文件地址
		file(string n,vector<string> c);//地址通过文件名地址获得
		~file();

		bool write(string c);//写入内容
		
	};

	class dir{//这个类的大部分代码来自GHG黑客游戏，作者Nictheboy
	public:
		string name;//文件夹名
		dir *father;//父文件夹
		vector<file*> file_content;//包含文件名
		vector<dir*> dir_content;//包含文件夹
		int file_num;//文件数量
		int dir_num;//文件夹数量
		dir(string n);//根据名字创建文件
		~dir();

		bool create_new_file (file* f);//创建新的文件
		bool create_new_dir (dir* d);//创建文件夹
		bool add_dir(string n);//在原有基础上加入文件夹
		bool add_txt(string n,vector<string> c);//在原有基础上加入文件
		bool del_file (string filename);//删除文件
		bool del_dir (string dirname);//删除文件夹
		int search_file(string filename)const;
		int search_dir(string dirname)const;
		dir* locate_dir(string s)const;//定位文件夹，可以对其操作
		file* locate_file(string s)const;
	};
	class Computer{
	public:
		string username;
		string password;
		string ip;
		dir* main_dir_tree[50];
		int current_dir=0;

		int shutdown(int agrc,vector<string> c);
		int cl(int agrc,vector<string> c);
		int finder(int agrc,vector<string> c);
		int error(int agrc,vector<string> c);
		int flst(int agrc,vector<string> c);
	};
	int cmd_shutdown(int agrc,vector<string> c);
	int cmd_cl(int agrc,vector<string> c);
	int cmd_finder(int agrc,vector<string> c);
	int cmd_error(int agrc,vector<string> c);
	int cmd_flst(int agrc,vector<string> c);

	class Process{
	public:
		void add_exe(string name,adr_exe adr);
  		void run_exe(string name,int i,vector<string> c);
	};




	//系统组件
	Computer computer[10];
	int (*get_cmd(string name))(int i,vector<string> c){
    	if(name == "shutdown")
    	{
        	return &cmd_shutdown;
    	}
    	else if(name == "cl")
    	{
        	return &cmd_cl;
    	}
    	else if(name == "finder")
    	{
    		return &cmd_finder;
    	}
    	else if(name == "flst")
    	{
    	    return &cmd_flst;
    	}
    	else
    	{
    	    return &cmd_error;
    	}
	}
	void Process::run_exe(string name,int i,vector<string> c){
    	get_cmd(name)(i,c);
	}

	class Style{
	public:
		string cout_login;
		string cout_password;
		string cout_password_wrong;
		string cout_password_right;
		string cout_before_ip;
		string cout_after_ip;
		Style()
		{
			cout_login = "请输入用户名 : ";
			cout_password = "请输入密码 : ";
			cout_password_right = "已登录";
			cout_password_wrong = "密码错误!";
			cout_before_ip = "[";
			cout_after_ip = "->" + computer[0].username + "]~$";
		}
	};
	//[ip->name]~$
	void print_logo(){
		cout<<"#---------------------------------------------------------------------------------------#"<<endl;
		cout<<"#                                 My Klein Computer                                     #"<<endl;
		cout<<"#                                      V0.0.2                                           #"<<endl;
		cout<<"#                                      Inc.SHO                                          #"<<endl;
		cout<<"#                                 C++ code-Provide                                      #"<<endl;
		cout<<"#                                                                                       #"<<endl; 
		cout<<"#---------------------------------------------------------------------------------------#"<<endl;
	}





//类的实现
	//------------------------------------------------------------文件类的实现----------------------------------------------------------//
	bool file::write(string c){
		content.push_back(c);
	}

	file::file(string n,vector<string> c){
		name = n;
		content = c;
		size = c.size();
		data = &n;
	}


	file::~file(){
		data = 0;
	}

	//------------------------------------------------------------文件夹类的实现-------------------------------------------------------//
	dir::dir(string n){
		name = n;
		file_num = 0;
		dir_num = 0;
	}


	bool dir::create_new_file (file* f){
		//判断文件
		if (f==NULL)
        {
        	cout<<"内部错误：文件为NULL";
        	return false;
        }
        for(int i = 0;i < file_num;i++)
        {
        	if(file_content[i]->name == f->name)
        	{
        		cout<<"文件已存在"<<endl;
        		return false;
        	}
        }
        file_num++;
        file_content.push_back(f);
        return true;
	}

	bool dir::create_new_dir(dir* d){
    	if (d==NULL)
    	{
        cout<<"内部错误：文件夹为NULL";
        return false;
        }
        for(int i = 0;i< dir_num;i++)
        {
        	if(dir_content[i]->name == d->name)
        	{
        		cout<<"文件夹已存在"<<endl;
        		return false;
        	}
        }
        dir_num++;
        dir_content.push_back(d);
        return true;
	}
	bool dir::del_file(string filename){
	    int where;
        where=search_file(filename);
        if (where==-1)
        {
            return false;
        }
        for (int i=where; i<file_num-1; i++)
        {
            file_content[i]=file_content[i+1];
        }
        file_num--;
        return true;
    }
    bool dir::del_dir(string dirname){
    	int where;
    	where=search_dir(dirname);
    	if(where==-1)
    	{
    		return false;
    	}
    	for (int i = where;i<dir_num;i++)
    	{
    		dir_content[i]=dir_content[i+1];
    	}
    	dir_num--;
    	return true;
    }
    int dir::search_file(string filename)const
    {
        int where=-1;
        for (int i=0; i<file_num; i++)
        {
            if (file_content[i]->name==filename)
            {
                where=i;
                break;
            }
        }
        return where;
    }
    int dir::search_dir(string dirname)const
    {
        int where=-1;
        for (int i=0; i<dir_num; i++)
        {
            if (dir_content[i]->name==dirname)
            {
                where=i;
                break;
            }
        }
        return where;
    }
    bool dir::add_dir(string n)
    {
    	dir *d;
    	d = new dir(n);
    	create_new_dir(d);
    	return true;
    }
    bool dir::add_txt(string n,vector<string> c)
    {
    	file* f;
    	f = new file(n,c);
    	create_new_file(f);
    	return true;
    }
    dir* dir::locate_dir(string s)const
    {
        string command=s;
        list<string> listed_cmd;
        string pattern="/";
        char * strc = new char[strlen(command.c_str())+1];
        strcpy(strc, command.c_str());
        char* tmpStr = strtok(strc, pattern.c_str());
        while (tmpStr != NULL)
        {
            listed_cmd.push_back(string(tmpStr));
            tmpStr = strtok(NULL, pattern.c_str());
        }
        delete[] strc;
            
        int size=0;
        for(list<string>::iterator iter = listed_cmd.begin();iter != listed_cmd.end();iter++)  
        {  
            size++;  
        } 
            
        if (size==0)
        {
            return NULL;
        }
        list<string>::iterator itor;
        itor=listed_cmd.begin();
        if (size==1)
        {
            int ps=search_dir(*itor);
            if (ps==-1)
            {
                return NULL;
            }
            return dir_content[ps];
        }
        const dir *to=this;

        for (int i=1; i<size; i++)
        {
            int ps=to->search_dir(*itor);
            if (ps==-1)
            {
                return NULL;
            }
            to=to->dir_content[ps];
        }
        itor++;
        int ps=to->search_dir(*itor);
        if (ps==-1)
        {
            return NULL;
        }
        return to->dir_content[ps];
    }
    file* dir::locate_file(string s)const
    {
        string command=s;
        list<string> listed_cmd;
        string pattern="/";
        char * strc = new char[strlen(command.c_str())+1];
        strcpy(strc, command.c_str());
        char* tmpStr = strtok(strc, pattern.c_str());
        while (tmpStr != NULL)
        {
            listed_cmd.push_back(string(tmpStr));
            tmpStr = strtok(NULL, pattern.c_str());
        }
        delete[] strc;
        int size=0;
        for(list<string>::iterator iter = listed_cmd.begin();iter != listed_cmd.end();iter++)  
        {  
            size++; 
        }  
            
            
        const dir *to=this;
        list<string>::iterator itor;
        itor=listed_cmd.begin();
        if (size==0)
        {
            return NULL;
        }
        if (size==1)
        {
            int ps=search_file(*itor);
            if (ps==-1)
            {
                return NULL;
            }
            return file_content[ps];
        }

        for (int i=1; i<size; i++)
        {
            int ps=to->search_dir(*itor);
            if (ps==-1)
            {
                return NULL;
            }
            to=to->dir_content[ps];
        }
        itor++;
        int ps=to->search_file(*itor);
        if (ps==-1)
        {
            return NULL;
        }
        return to->file_content[ps];
    }
    //----------------------------------------------------------电脑类的实现---------------------------------------------------//
    int Computer::shutdown(int agrc,vector<string> c){
    	cout<<"您确定要注销所有登录信息并立刻结束进程吗？(y/n)"<<endl;
    	string cind;
    	getline(cin,cind);
    	if(cind == "y")
    	{
    		exit(0);
    	}
    	else if(cind == "n")
    	{
    		return 0;
    	}
    	else
    	{
    		cout<<"[ERROR CODE : ##001]"<<endl;
    		exit(3);
    	}
    }

    int Computer::cl(int agrc,vector<string> c){
    	system("clean");
    }

    int Computer::finder(int agrc,vector<string> c){
    	if(agrc < 2)
    	{
    		cout<<"参数缺少，正确用法 finder [错误代码]"<<endl;
    		return 0;
    	}
    	if(agrc > 2)
    	{
    		cout<<"多余的参数，正确用法 finder [错误代码]"<<endl;
    		return 0;
    	}
    	//判断容器第二个元素内容
    	string fc = c[1];
    	string re = finder_if(fc);
    	cout<<re<<endl;
    	return 0;
    }
    int Computer::error(int agrc,vector<string> c){
        cout<<"输入的指令有错误！"<<endl;
        return 0;
    }
    int Computer::flst(int agrc,vector<string> c){
        if(agrc > 1)
        {
            cout<<"[ERROR CODE : ##002]"<<endl;
            return 0;
        }
    	string str;
    	for(agrc =0;agrc<main_dir_tree[current_dir]->dir_num;agrc++)
    	{
    		str=main_dir_tree[current_dir]->dir_content[agrc]->name;
    		cout<<str;
    		for (int i=0;strlen(str.c_str())<=49&&i<(50-strlen(str.c_str())); i++)
	        {
	            cout<<" ";
	        }
        cout<<"<DIR>\n";
    	}
	    for (agrc=0; agrc<main_dir_tree[current_dir]->file_num; agrc++)
	    {
	        str=main_dir_tree[current_dir]->file_content[agrc]->name;
	        cout<<str;
	        cout<<endl;
	    }
	    return 0;
    }
    //------------------------------------------额余函数的实现----------------------------------------------//
    string finder_if(string code_str)
    {
    	string result;
    	if(code_str == "##001")
    	{
    		result = "此错误为：输入错误的信息，不在所提供的信息内";
    	}
    	else if(code_str == "##002")
    	{
    		result = "此错误为：输入错误的参数，或参数的表达有误";
    	}
    	else
    	{
    		result = "[ERROR CODE : ##002]";
    	}
    	return result;
    }

    void init()
    {
    	print_logo();
    	wait(1);
		cls();
		Style sty;
		cout<<sty.cout_login;
		cin>>computer[0].username;
		cout<<endl;
		cout<<sty.cout_password;
		cin>>computer[0].password;
		cout<<endl;
		computer[0].ip = Mycomputerip;
		cout<<sty.cout_password_right;
		cout<<endl;
		computer[0].main_dir_tree[0] = new dir("/");
		computer[0].main_dir_tree[0]->add_dir("system32");
		computer[0].main_dir_tree[0]->add_dir("data");
        computer[0].main_dir_tree[0]->add_dir("program");
        computer[0].main_dir_tree[0]->add_dir("SystemProgram");
        vector<string> content;
		content.push_back("系统文件勿动");
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_txt("system.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_txt("KleinNet.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_dir("SystemProgram");
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x3b",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x4a",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x4f",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x5e",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x5d",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x5f",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x6a",content);
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_txt("telnet.exe",content);
		return;
    }




    //---------------------------------------------输入的实现-------------------------------------------------//
    int main()
    {
    	init();
        Process *pro;
    	string cmd_cin;
		Style ele;
    	string co = ele.cout_before_ip + Mycomputerip + ele.cout_after_ip;
    	while(true){
        cout<<co;
   		getline(cin,cmd_cin);
    	vector<string> content = split(cmd_cin," ");
    	int i=content.size();
    	pro->run_exe(content[0],i,content);
    	}
    }



    int cmd_shutdown(int agrc,vector<string> c){
    	computer[0].shutdown(agrc,c);
    	return 0;
    }
	int cmd_cl(int agrc,vector<string> c){
		computer[0].cl(agrc,c);
		return 0;
	}
	int cmd_finder(int agrc,vector<string> c){
		computer[0].finder(agrc,c);
		return 0;
	}
	int cmd_error(int agrc,vector<string> c){
	    computer[0].error(agrc,c);
	    return 0;
	}
	int cmd_flst(int agrc,vector<string> c){
	    computer[0].flst(agrc,c);
	    return 0;
	}
