
class TextEditor {
	Files::ProjectList projectList;
	int uniqueProjectCount = 0;
	std::string creater;
	//const Project* projectList=nullptr;
public:
	TextEditor(std::string user) {
		creater = user;
		std::fstream binObject(user + ".bin", std::ios::in | std::ios::binary);
		if (!binObject.is_open())
		{
			std::cout << "project *.binfile not found creating a new file" << std::endl;
		}
		else if (!(projectList.ParseFromIstream(&binObject)))
		{
			std::cout << "error while prasing *.bin file" << std::endl;
		}
		uniqueProjectCount = projectList.count();
		selectorCycle();

	}
	//TextEditor(const Project& projectlist) { projectList = &projectlist; }
	void selectorCycle()
	{	
		while (1) {
			int i = 0;
			std::cout << "1 => new 2 => existing 3 => exit: ";
			std::cin >> i;
			if (i == 1) { createNew(); }
			if (i == 2) { existingFile(); }
			if (i == 3) { break; }
		}

	}
	void createNew()
	{
		Files::Project* newfile = projectList.add_projectnamelist();
		projectList.set_count(projectList.count() + 1);
		std::cout << "[File Name]: ";
		std::string filename;
		std::cin >> filename;
		newfile->set_filename(filename);
		newfile->set_projectid(projectList.count());
		newfile->set_currentverion(1);
		newfile->set_creater(creater);
		uniqueProjectCount += 1;
		projectList.set_count(projectList.count() + 1);
		auto edit = Editor(projectList.mutable_projectnamelist(uniqueProjectCount-1));
		//auto edit = Editor(newfile);
		//proced to next()
	}
	void existingFile()
	{
		for (int projectindex = 0; projectindex < projectList.count(); projectindex++)
		{
			std::cout << projectindex << ". " << projectList.projectnamelist(projectindex).filename() << std::endl;
		}
		int fileindex = -1;
		std::cout << "enter The index of the file: " << std::endl;
		std::cin >> fileindex;
		if (fileindex >= 0 && fileindex < projectList.count())
		{
			//proced the file name+version()
			//auto edit = Editor(projectList.projectnamelist(fileindex));
			auto edit = Editor(projectList.mutable_projectnamelist(fileindex));
		}
		else std::cout << "Not a file index: " << fileindex << std::endl;
	}

	~TextEditor()
	{
		projectList.set_count(projectList.projectnamelist_size());
		std::fstream boutObject(creater + ".bin", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!boutObject.is_open()) { std::cout << "unable to open project *.bin file" << std::endl; }
		else if (!projectList.SerializePartialToOstream(&boutObject)) { std::cout << "unable to write data !data lost" << std::endl; }
	}

};