#define RESET "\033[0m"
#define GREEN "\033[32m"

#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>

void add_todo(int todo_length, char** todo, std::filesystem::path todo_file);
void del_todo(int todo_num, std::filesystem::path todo_file);
void update_todo(int todo_length, int todo_num, char** update_todod_todo, std::filesystem::path todo_file);
void list_todos(std::filesystem::path todo_file);
void complete_todo(int todo_num, std::filesystem::path todo_file);
void usage();

int main(int argc, char** argv) 
{
    if (argc == 1)
    {
		printf("Need at least one argument!\n");
		return 1;
    }

	#if defined(WIN32) || defined(_WIN32)
		std::string home = getenv("USERPROFILE");
	#else
		std::string home = getenv("HOME");
	#endif
    std::string todo_dir = ".todo";
    std::string todo_f = "todo";
    std::filesystem::path work_dir = home;
    // build the path
    work_dir /= todo_dir;
    if (!std::filesystem::exists(work_dir))
		std::filesystem::create_directory(work_dir);
    
    // add_todo file to path
    work_dir /= todo_f;

    // convert first arg to string for compare
    std::string cmd = argv[1];

    if (cmd == "add")
    {
		add_todo(argc, argv, work_dir);
    }
    else if (cmd == "list") 
    {
		printf("Todo List\n");
		printf("---------\n");
		list_todos(work_dir);
    }
    else if (cmd == "del")
    {
		char *int_conversion = argv[2];
		char *end_ptr;
		unsigned int todo_num = strtol(int_conversion, &end_ptr, 0);
		del_todo(todo_num, work_dir);
    }
    else if (cmd == "update") 
    {
		char *int_conversion = argv[2];
		char *end_ptr;
		int todo_num = strtol(int_conversion, &end_ptr, 0);
		update_todo(argc, todo_num, argv, work_dir);
    }
    else if (cmd == "done")
    {
		char *int_conversion = argv[2];
		char *end_ptr;
		int todo_num = strtol(int_conversion, &end_ptr, 0);
		complete_todo(todo_num, work_dir);
	
    }
    else
    {
		usage();
    }
}


void add_todo(int todo_length, char** todo, std::filesystem::path todo_file)
{
    std::ofstream todo_writer;
    todo_writer.open(todo_file, std::ios::app);

    std::string full_todo = "";
    for (int i = 2; i < todo_length; i++) 
    {
		full_todo += todo[i];
		full_todo += " ";
    }

    todo_writer << full_todo << "\n";
    todo_writer.close();	

}

void del_todo(int todo_num, std::filesystem::path todo_file)
{
    std::vector<std::string> todos;
    std::ifstream todo_reader(todo_file, std::ifstream::in);
    std::string todo;
    int todo_index = 1;

    while (getline(todo_reader, todo))
    {
		if (todo_index != todo_num)
			todos.push_back(todo);
		todo_index++;
    }
    todo_reader.close();
	
    std::ofstream todo_writer;
    todo_writer.open(todo_file);
    for (std::string todo : todos)
    {
		todo_writer << todo << "\n"; 
    }
    todo_writer.close();
}

void update_todo(int todo_length, int todo_num, char** update_todod_todo, std::filesystem::path todo_file) 
{
    std::vector<std::string> todos;
    std::ifstream todo_reader(todo_file, std::ifstream::in);
    int todo_index = 1;
    std::string todo;
    std::string full_todo;

    for (int i = 3; i < todo_length; i++) 
    {
		full_todo += update_todod_todo[i];
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

    std::ofstream todo_writer;
    todo_writer.open(todo_file);

    for (std::string todo : todos)
    {
		todo_writer << todo << std::endl;
    }
    todo_writer.close();
}

void complete_todo(int todo_num, std::filesystem::path todo_file)
{
    std::vector<std::string> todos;
    std::string todo;
    std::ifstream todo_reader(todo_file, std::ifstream::in);
    int todo_index = 1;

    while (getline(todo_reader, todo))
    {
		if (todo_index == todo_num)
	{
	    todo += "+";
	    todos.push_back(todo);
	}
		else
		{
			todos.push_back(todo);
		}
		todo_index++;
    }
    todo_reader.close();

    std::ofstream todo_writer;
    todo_writer.open(todo_file);

    for (std::string todo : todos)
    {
		todo_writer << todo << "\n";
    }
    todo_writer.close();
}

void list_todos(std::filesystem::path todo_file) 
{
    std::ifstream todo_reader(todo_file, std::ifstream::in);
    std::string todo;
    int todo_num = 1;

    while (getline(todo_reader, todo)) 
    {
		if (todo.find(" +") != std::string::npos)
		{
			printf(GREEN "%d. %s\n", todo_num, todo.c_str());
			printf(RESET);
		}
	 
		else
		{	    
			printf("%d. %s\n", todo_num, todo.c_str());
		}
		todo_num++;
    }
    todo_reader.close();
}

void usage()
{
    printf("usage: todo cmd arg(s)\n");
    printf("cmd: add | del | update | done | list\n");
    printf("add: todo add <todo>\n");
    printf("del: todo del <todo's number>\n");
	printf("done: todo done <todo's number>\n");
    printf("update: todo update <todo's number> <updated todo>\n");
    printf("list: todo list\n");
}
