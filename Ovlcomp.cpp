	/*
	#---------------------------------------------------------------------------------------#
	#                                 My Klein Computer                                     #
	#                                      V0.0.7                                           # 
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
	#v0.0.5                                         //加入gdir指令进入文件夹
	#v0.0.6                                         //修复了clear不能用，加入了help指令和del指令
	#v0.0.7                                         //加入了更真实的文件存储功能（基于真实电脑）
	#v0.0.8                                         //加入了文件读取，使得登录更加真实
	#---------------------------------------------------------------------------------------#
	#qq群     981225898
	#website  kleintr.ml
	*/
	//定义启动服务所需的头文件
	#include <iostream>
	#include <unistd.h>
	#include <stdlib.h>
	#include <ctime>
	#include <ios>
	#include <cstring>
	#include <string>
	#include <set>
	#include <bitset>
	#include <map>
	#include <list>
	#include <deque>
	#include<cctype>
	#include<cerrno>
	#include <cfloat>
	#include <ciso646>
	#include <climits>
	#include <clocale>
	#include <cmath>
	#include <csetjmp>
	#include <csignal>
	#include <cstdarg>
	#include <cstddef>
	#include <cstdio>
	#include <cstdlib>
	#include <cstring>
	#include <ctime>
	#include <ccomplex>
	#include <cfenv>
	#include <cinttypes>
	#include <cstdalign>
	#include <cstdbool>
	#include <cstdint>
	#include <ctgmath>
	#include <cwchar>
	#include <cwctype>
	#include <algorithm>
	#include <bitset>
	#include <complex>
	#include <deque>
	#include <exception>
	#include <fstream>
	#include <functional>
	#include <iomanip>
	#include <ios>
	#include <iosfwd>
	#include <iostream>
	#include <istream>
	#include <iterator>
	#include <limits>
	#include <list>
	#include <locale>
	#include <map>
	#include <memory>
	#include <new>
	#include <numeric>
	#include <ostream>
	#include <queue>
	#include <set>
	#include <sstream>
	#include <stack>
	#include <stdexcept>
	#include <streambuf>
	#include <string>
	#include <typeinfo>
	#include <utility>
	#include <valarray>
	#include <vector>
	#include <array>
	#include <atomic>
	#include <chrono>
	#include <condition_variable>
	#include <forward_list>
	#include <future>
	#include <initializer_list>
	#include <mutex>
	#include <random>
	#include <ratio>
	#include <regex>
	#include <scoped_allocator>
	#include <system_error>
	#include <thread>
	#include <tuple>
	#include <typeindex>
	#include <type_traits>
	#include <unordered_map>
	#include <unordered_set>
	#include <direct.h>
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
	#define cls() system("cls")
	//后面在做延时时用到了waittime函数，利用这个宏做的一个内置函数
	#define uwait(x) usleep(x)  //毫秒级别延时
	//内部数据定义,得注意一件事情，后期要建设虚拟以太网，那么ip数就会很大，通过这里定义肯定是不够的，我们就得建一个服务器，那也不造是何时的事
	string Mycomputerip ="64.102.29.18";//我们自己的电脑ip
	string comp = "192.168.0.1";


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
	//工作目录读取函数，来自csdn
	string work_cd()
	{
	    char buff[250];
	    _getcwd(buff, 250); 
	    string work_cd(buff);
	    return work_cd;
	}
	void login(string name,string password)
	{
		string cd_work = work_cd();
		string data_ovl = cd_work + "\\ovl_system";
		if(0 != access(data_ovl.c_str(), 0))
		{
			mkdir(data_ovl.c_str());
		}
		ofstream ofile;
		string login_txt = data_ovl + "\\sys_data.txt";
		ofile.open(login_txt.c_str());
		ofile<<name<<"\n"<<password;
		ofile.close();
		return;
	}
	void login_if(string name,string password)
	{
		string cd_work = work_cd();
		string data_ovl = cd_work + "\\ovl_system";
		string mytxt = data_ovl + "\\sys_data.txt";
		ifstream ifile(mytxt.c_str());
		if(ifile)
		{
			string n,p;
			ifile>>n>>p;
			if((n==name)&&(p==password))
			{
				cout<<"你输入的密码和用户与上一次的信息吻合，成功登入";
				return;
			}
			else
			{
				cout<<"您上一次已经创建了用户，但现在输入的密码或用户错误,程序即将自动退出";
				wait(3);
				exit(0);
			}
		}
		login(name,password);
		
	}
	/*请无视以下代码
	    string cd_w = work_cd();

    string folderPath = cd_w + "\\ovl_system"; 
	cout<<cd_w;
    if (0 != access(folderPath.c_str(), 0))
    {
        mkdir(folderPath.c_str());  
    }
    ofstream ofile;
    string mytxt = folderPath + "\\data.txt";
    ofile.open(mytxt.c_str());
    string name,password;
    getline(cin,name);
    getline(cin,password);
    ofile<<name<<"\n"<<password;
    ofile.close();
    ifstream ifile;
    ifile.open(mytxt.c_str());
    string a,b;
    ifile>>a>>b;
    cout<<a<<b;
    ifile.close();
    system("pause");
    */
//类的定义以及函数的声明


	//声明一个文件类，存储文件
	class file;
	//声明一个电脑类，有系统消息
	class Computer;
	//声明一个文件夹类
	class dir;
	//声明处理输入的类
	class Process;
	//界面样式
	class Style;
	//声明一个新类，用来存储网络（你可以理解为我在这里放了一个以太网）
    string finder_if(string code_str);//寻找错误代码的函数
    string finder_cmd(string code_str);//寻找cmd的函数

	typedef int (*adr_exe)(int agrc,vector<string> c);//有啥用？我也不造




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
		dir* turn_file_ps_into_dir_ps(string fp);
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
		int gdir(int agrc,vector<string> c);
		int help(int agrc,vector<string> c);
		int del(int agrc,vector<string> c);
	};
	int cmd_shutdown(int agrc,vector<string> c);
	int cmd_cl(int agrc,vector<string> c);
	int cmd_finder(int agrc,vector<string> c);
	int cmd_error(int agrc,vector<string> c);
	int cmd_flst(int agrc,vector<string> c);
	int cmd_gdir(int agrc,vector<string> c);
	int cmd_help(int agrc,vector<string> c);
	int cmd_del(int agrc,vector<string> c);
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
    	else if(name == "gdir")
    	{
    		return &cmd_gdir;
    	}
    	else if(name == "help")
    	{
    		return &cmd_help;
    	}
    	else if(name == "del")
    	{
    		return &cmd_del;
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
    dir* dir::turn_file_ps_into_dir_ps(string fp)
    {
    	string	command = fp;
    	vector<string>	listed_cmd;
    	string	pattern = "/";
    	listed_cmd = split(command,pattern);
    	int size = 0;
    	for(auto iter = listed_cmd.begin(); iter != listed_cmd.end(); iter++ )
    	{
    		size++;
    	}
    	auto itor = listed_cmd.begin();
    	dir	*to = this;
    	if ( size == 0 )
    	{
    		return(NULL);
    	}
    	if ( size == 1 )
    	{
    		return(this);
    	}
    	for ( int i = 1; i < size; i++ )
    	{
    		int ps = to->search_dir( *itor );
    		if ( ps == -1 )
    		{
    			return(NULL);
    		}
    		to = to->dir_content[ps];
    	}
    	return(to);
    }
    //----------------------------------------------------------电脑类的实现---------------------------------------------------//
    int Computer::shutdown(int agrc,vector<string> c){
    	if(agrc > 1)
    	{
    		cout<<"[ERROE CODE : ##002],正确用法: shutdown <ENTER>"<<endl;
    		return 0;
    	}
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
    	system("cls");
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
            cout<<"[ERROR CODE : ##002],正确用法: flst <ENTER>"<<endl;
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
	        for (int i=0;strlen(str.c_str())<=49&&i<(50-strlen(str.c_str()));i++ )
	        {
	        	cout<<" ";
	        }
	        cout<<"<FILE>\n";
	        cout<<endl;
	    }
	    return 0;
    }
    int Computer::gdir(int agrc,vector<string> c){
    	if(agrc < 2)
    	{
    		cout<<"[ERROR CODE : ##002],正确用法: gdir [目标文件夹名]";
    		cout<<endl;
    		return 0;
    	}
    	if(agrc > 2)
    	{
    		cout<<"[ERROR CODE : ##002],正确用法: gdir [目标文件夹名]";
    		cout<<endl;
    		return 0;
    	}
    	string t = c[1];
	   	if (strcmp(t.c_str(),"..")==0 or strcmp(t.c_str(),".")==0)
	    {
	        if (current_dir==0)
	        {
	            cout<<"您已经位于根目录！\n";
	            return 0;
	        }
	        current_dir--;
	        return 0;
	    }
	    for (int i=0; i<main_dir_tree[current_dir]->dir_num; i++)
	    {
	        if (strcmp(main_dir_tree[current_dir]->dir_content[i]->name.c_str(),t.c_str())==0)
	        {
	            main_dir_tree[current_dir+1]=main_dir_tree[current_dir]->dir_content[i];
	            current_dir++;
	            return 0;
	        }
	    }
	    cout<<"目录不存在！\n";
	    return 0;
    }
    int Computer::help(int agrc,vector<string> c){
    	if(agrc > 2)
    	{
    		cout<<"[ERROR CODE : ##002],正确用法: \"help\" or help [查询的命令名] ";
    		cout<<endl;
    		return 0;
    	}
    	if(agrc == 1)
    	{
    		cout<<"#############################################################"<<endl;
    		cout<<"shutdown\t"<<"关机|退出程序"<<endl;
    		cout<<"finder\t"<<"查找某个错误代码"<<endl;
    		cout<<"cl\t"<<"清空屏幕"<<endl;
    		cout<<"flst\t"<<"查看当前目录下的所有目录和文件"<<endl;
    		cout<<"gdir\t"<<"进入某个目录"<<endl;
    		cout<<"help\t"<<"查看帮助|指令列表"<<endl;
    		cout<<"#############################################################"<<endl;
    		cout<<"输入help [指令名]以查询某个特定指令的详细用法"<<endl;
    		return 0;
    	}
    	string fcmd = c[1];
    	string fenter;
    	fenter = finder_cmd(fcmd);
    	cout<<fenter<<endl;
    	return 0;
    }
    int Computer::del(int agrc,vector<string> c){
    	if(agrc > 2)
    	{
    		cout<<"[ERROR CODE : ##002]:正确用法: del [文件名] or [文件夹名]"<<endl;
    		return 0;
    	}
    	if(agrc < 2)
    	{
    		cout<<"[ERROR CODE : ##002]:正确用法: del [文件名] or [文件夹名]"<<endl;
    		return 0;
    	}
    	if (!(main_dir_tree[current_dir]->del_file(c[1])||main_dir_tree[current_dir]->del_dir(c[1])))
	    {
	        class dir *fath=main_dir_tree[current_dir]->turn_file_ps_into_dir_ps(c[1]);
	        file *f=main_dir_tree[current_dir]->locate_file(c[1]);
	        //cout<<fath<<endl;
	        //cout<<f<<endl;
	        if (fath&&f)
	        {
	            fath->del_file(f->name);
	        }
	        else
	        {
	            cout<<"文件或文件夹不存在!\n";
	        }
	    }
    }

    string user="此指令的单独用法为:";
    string shutdown_user="输入 shutdown 直接使用";
    string finder_user="输入 finder [错误代码] 以使用";
    string cl_user="输入 cl 直接使用";
    string flst_user="输入 flst 直接使用";
    string gdir_user="输入 gdir [文件夹] 以使用";
    string help_user="输入help [指令名]以查询某个特定指令的详细用法";
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
    string finder_cmd(string code_str)
    {
    	string result;
    	if(code_str == "shutdown")
    	{
    		result = user + shutdown_user;
    	}
    	else if(code_str == "finder")
    	{
    		result = user + finder_user;
    	}
    	else if(code_str == "cl")
    	{
    		result = user + cl_user;
    	}
    	else if(code_str == "flst")
    	{
    		result = user + flst_user;
    	}
    	else if(code_str == "gdir")
    	{
    		result = user + gdir_user;
    	}
    	else if(code_str == "help")
    	{
    		result = user + help_user;
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
		cout<<sty.cout_password;
		cin>>computer[0].password;
		computer[0].ip = Mycomputerip;
		login_if(computer[0].username,computer[0].password);
		cout<<endl;
		computer[0].main_dir_tree[0] = new dir("/");
		computer[0].main_dir_tree[0]->add_dir("system32");
		computer[0].main_dir_tree[0]->add_dir("data");
        computer[0].main_dir_tree[0]->add_dir("program");
        computer[0].main_dir_tree[0]->add_dir("SystemProgram");
        vector<string> content;
		content.push_back("系统文件勿动");
		vector<string> mail_content;
		mail_content.push_back("最近，Vital的著名黑客Nic Wision编写了一套ddos工具，在著名的hark论坛hark.ml上发布，据悉该工具可以发起接近1T的流量攻击！");
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_txt("system.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_txt("KleinNet.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_dir("SystemProgram");
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x3b.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x4a.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x4f.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x5e.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x5d.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x5f.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("SystemProgram")->add_txt("0x6a.sys",content);
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_txt("connect.exe",content);
		computer[0].main_dir_tree[0]->locate_dir("system32")->add_txt("gitfile.exe",content);
		computer[0].main_dir_tree[0]->locate_dir("data")->add_txt("mail.exe",mail_content);
		return;
    }




    //---------------------------------------------输入的实现-------------------------------------------------//
    int main()
    {
    	init();
        Process *pro;
    	string cmd_cin;
		Style elemplt;
    	string cot = elemplt.cout_before_ip + Mycomputerip + elemplt.cout_after_ip;
    	while(true){
        cout<<cot;
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
	int cmd_gdir(int agrc,vector<string> c){
		computer[0].gdir(agrc,c);
		return 0;
	}
	int cmd_help(int agrc,vector<string> c){
		computer[0].help(agrc,c);
		return 0;
	}
	int cmd_del(int agrc,vector<string> c)
	{
		computer[0].del(agrc,c);
		return 0;
	}
