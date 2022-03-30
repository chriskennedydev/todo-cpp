#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

void add(int todo_length, char** todo, std::filesystem::path todo_file);
void del(int todo_num, std::filesystem::path todo_file);
void update(int todo_length, int todo_num, char** updated_todo, std::filesystem::path todo_file);
void todo_list(std::filesystem::path todo_file);
void done(int todo_num, std::filesystem::path todo_file);
void usage();

int main(int argc, char** argv) 
{
    if (argc == 1)
    {
	printf("Need at least one argument!\n");
	return 1;
    }

    std::string home = getenv("HOME");
    std::string todo_dir = ".todo";
    std::string todo_f = "todo";
    std::filesystem::path work_dir = home;
    // build the path
    work_dir /= todo_dir;
    if (!std::filesystem::exists(work_dir))
	std::filesystem::create_directory(work_dir);
    
    // add file to path
    work_dir /= todo_f;

    // convert first arg to string for compare
    std::string cmd = argv[1];

    if (cmd == "add")
    {
	add(argc, argv, work_dir);
    }
    else if (cmd == "list") 
    {
	printf("Todo List\n");
	printf("---------\n");
	todo_list(work_dir);
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
    else if (cmd == "done")
    {
	int todo_num = atoi(argv[2]);
	done(todo_num, work_dir);
	
    }
    else
    {
	usage();
    }
}


void add(int todo_length, char** todo, std::filesystem::path todo_file)
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

void del(int todo_num, std::filesystem::path todo_file)
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

void update(int todo_length, int todo_num, char** updated_todo, std::filesystem::path todo_file) 
{
    std::vector<std::string> todos;
    std::ifstream todo_reader(todo_file, std::ifstream::in);
    int todo_index = 1;
    std::string todo;
    std::string full_todo;

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

    std::ofstream todo_writer;
    todo_writer.open(todo_file);

    for (std::string todo : todos)
    {
	todo_writer << todo << std::endl;
    }
    todo_writer.close();
}

void done(int todo_num, std::filesystem::path todo_file)
{
    std::vector<std::string> todos;
    std::string todo;
    std::ifstream todo_reader(todo_file, std::ifstream::in);
    int todo_index = 1;

    while (getline(todo_reader, todo))
    {
	if (todo_index == todo_num)
	{
	    todo += "✓";
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

void todo_list(std::filesystem::path todo_file) 
{
    std::ifstream todo_reader(todo_file, std::ifstream::in);
    std::string todo;
    int todo_num = 1;

    while (getline(todo_reader, todo)) 
    {
	printf("%d. %s\n", todo_num, todo.c_str());	
	todo_num++;
    }
    todo_reader.close();
}

void usage()
{
    printf("usage: todo cmd arg(s)\n");
    printf("cmd: add | del | update | list\n");
    printf("add: todo add <my todo to add>\n");
    printf("del: todo del <todo's number>\n");
    printf("update: todo update <todo's number> <updated todo>\n");
    printf("list: todo list\n");
}
