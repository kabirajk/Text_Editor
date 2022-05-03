
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
	
	void selectorCycle()
	{	
		while (1) {
			int i = 0;
			std::cout << "1 => new 2 => existing 3 => Delete 4 => exit: ";
			std::cin >> i;
			if (i == 1) { createNew(); }
			if (i == 2) { existingFile(); }
			if (i == 3) { deleteFile(); }
			if (i==4) { break; }
		}

	}
	void createNew()
	{
		Files::Project* newfile = projectList.add_projectnamelist();
		projectList.set_count(projectList.count() + 1);
		std::cout << "[File Name]: ";
		std::string filename;
		//std::cin >> filename;
		getline(std::cin, filename);
		newfile->set_filename(filename);
		newfile->set_projectid(projectList.count());
		const time_t Time = time(0);
		char createdtime[26];
		ctime_s(createdtime, 26, &Time);
		createdtime[24] ='\0';
		newfile->set_createdtime(std::string(createdtime));
		newfile->set_currentversion(1);
		newfile->set_creater(creater);
		uniqueProjectCount += 1;
		projectList.set_count(projectList.count() + 1);
		auto edit = Editor(projectList.mutable_projectnamelist(uniqueProjectCount-1));
		//proced to next()
	}
	void existingFile()
	{
		if (projectList.projectnamelist_size() == 0)
		{
			std::cout << "[Empty Projects]" << std::endl;
		}
		else
		{
			for (int projectindex = 0; projectindex < projectList.projectnamelist_size(); projectindex++)
			{
				std::cout << projectindex << ". " << projectList.projectnamelist(projectindex).filename()
					<< "       " << projectList.projectnamelist(projectindex).createdtime()
					<< "     " << projectList.projectnamelist(projectindex).currentversion()
					<< std::endl;
			}
			int fileindex = -1;
			std::cout << "enter The index of the file: " << std::endl;
			std::cin >> fileindex;

			if ((fileindex >= 0 && fileindex < projectList.projectnamelist_size()) && projectList.projectnamelist_size() != 0)
			{
				auto edit = Editor(projectList.mutable_projectnamelist(fileindex));
			}
			else std::cout << "Not a file index: " << fileindex << std::endl;

		}
	}
	void deleteFile()
	{
		for (int projectindex = 0; projectindex < projectList.projectnamelist_size(); projectindex++)
		{
			std::cout << projectindex << ". " << projectList.projectnamelist(projectindex).filename() << std::endl;
		}
		std::cout << "[Delte][Index to File]: " << std::endl;
		int id;
		std::cin >> id;
		if (id >= 0 && id < projectList.projectnamelist_size())
		{
			id = projectList.projectnamelist(id).projectid();
			for (auto iter = projectList.mutable_projectnamelist()->begin(); iter != projectList.mutable_projectnamelist()->end(); iter++)
			{
				if (iter->projectid() == id)
				{
					std::cout << "[Deletetd]" << iter->filename() << std::endl;
					(&projectList)->mutable_projectnamelist()->erase(iter);
					break;
				}
			}
		}
		else std::cout << "[File][index] not Matched" << std::endl;
	}

	~TextEditor()
	{
		//projectList.set_count(uniqueProjectCount);
		std::fstream boutObject(creater + ".bin", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!boutObject.is_open()) { std::cout << "unable to open project *.bin file" << std::endl; }
		else if (!projectList.SerializePartialToOstream(&boutObject)) { std::cout << "unable to write data !data lost" << std::endl; }
	}

};