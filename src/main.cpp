#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;

void add(int todo_length, char** todo, filesystem::path todo_file);
void del(int todo_num, filesystem::path todo_file);
void update(int todo_length, int todo_num, char** updated_todo, filesystem::path todo_file);
void list(filesystem::path todo_file);
void usage();

int main(int argc, char** argv) 
{
	if (argc == 1)
	{
		cout << "Need at least one argument!" << endl;
		return 1;
	}

	string home = getenv("HOME");
	string todo_dir = ".todo";
	string todo_f = "todo";
	filesystem::path work_dir = home;
	// build the path
	work_dir /= todo_dir;
	if (!filesystem::exists(work_dir))
		filesystem::create_directory(work_dir);

	// add file to path
	work_dir /= todo_f;

	// convert first arg to string for compare
	string cmd = argv[1];

	if (cmd == "test")
	{
		cout << "File is " << work_dir << endl;
	}
	else if (cmd == "add")
	{
		add(argc, argv, work_dir);
	}
	else if (cmd == "list") 
	{
		cout << "Todo List" << endl;
		cout << "---------" << endl;
		list(work_dir);
	}
	else if (cmd == "del")
	{
		int todo_num = atoi(argv[2]);
		del(todo_num, work_dir);
	}
	else if (cmd == "update") 
	{
		int todo_num = atoi(argv[2]);
		update(argc, todo_num, argv, work_dir);
	}
	else
	{
		usage();
	}
}


void add(int todo_length, char** todo, filesystem::path todo_file)
{
	ofstream todo_writer;
	todo_writer.open(todo_file, ios::app);

	string full_todo = "";
	for (int i = 2; i < todo_length; i++) 
	{
		full_todo += todo[i];
		full_todo += " ";
	}

	todo_writer << full_todo << "\n";
	todo_writer.close();	

}

void del(int todo_num, filesystem::path todo_file)
{
	vector<string> todos;
	ifstream todo_reader(todo_file, ifstream::in);
	string todo;
	int todo_index = 1;

	while (getline(todo_reader, todo))
	{
		if (todo_index != todo_num)
			todos.push_back(todo);
		todo_index++;
	}
	todo_reader.close();
	
	ofstream todo_writer;
	todo_writer.open(todo_file);
	for (string todo : todos)
	{
		todo_writer << todo << "\n"; 
	}
	todo_writer.close();
}

void update(int todo_length, int todo_num, char** updated_todo, filesystem::path todo_file) 
{
	vector<string> todos;
	ifstream todo_reader(todo_file, ifstream::in);
	int todo_index = 1;
	string todo;
	string full_todo;

	for (int i = 3; i < todo_length; i++) 
	{
		full_todo += updated_todo[i];
		full_todo += " ";
	}

	while (getline(todo_reader, todo)) 
	{
		if (todo_index == todo_num)
			todos.push_back(full_todo);
		else
			todos.push_back(todo);
		todo_index++;
	}

	todo_reader.close();

	ofstream todo_writer;
	todo_writer.open(todo_file);

	for (string todo : todos)
	{
		todo_writer << todo << endl;
	}
	todo_writer.close();
}
void list(filesystem::path todo_file) 
{
	ifstream todo_reader(todo_file, ifstream::in);
	string todo;
	int todo_num = 1;

	while (getline(todo_reader, todo)) 
	{
		cout << todo_num << ". " << todo << endl;
		todo_num++;
	}
	todo_reader.close();
}

void usage()
{
	cout << "usage: todo cmd arg(s)" << endl;
	cout << "cmd: add | del | update | list" << endl;
	cout << "add: todo add <my todo to add>" << endl;
	cout << "del: todo del <todo's number>" << endl;
	cout << "update: todo update <todo's number> <updated todo>" << endl;
	cout << "list: todo list" << endl;
}
