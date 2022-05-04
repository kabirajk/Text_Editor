class Editor{
	Files::Project* currentProject = nullptr;
	std::string fileName;
	int currentVersion;
	fileVer::Filedata fileDataList;
	fileVer::File* currentHead=nullptr;

public:
	Editor(Files::Project* project)
	{
		currentProject = project;
		fileName = currentProject->filename() + currentProject->creater();
		currentVersion = currentProject->currentversion();
		std::cout << "loaded";
		readData(fileName);
		
		if (fileDataList.filedatabase_size() == 0){ addCommit(); }
		
		currentHead = fileDataList.mutable_filedatabase(currentVersion-1);
		printData();
		fileEditor();
		
	}
	void setHead(){ currentHead = fileDataList.mutable_filedatabase(currentVersion-1); }

	void addCommit(int version = 1, int commitcount = 1)
	{
		fileVer::File* newfile = fileDataList.add_filedatabase();
		newfile->set_commitcount(commitcount);
		const time_t Time = time(0);
		char createdtime[26];
		ctime_s(createdtime, 26, &Time);
		
		newfile->set_createdtime(std::string(createdtime));
		std::cout << newfile->createdtime() << std::endl;
		newfile->set_version(version);
	}

	void copystring(fileVer::File* from, fileVer::File* to)
	{
		for (int i = 0; i <from->textline_size(); i++)
		{
			to->add_textline(from->textline(i));
		}
	}

	void fileEditor() 
	{

		int count = fileDataList.filedatabase(currentVersion-1).commitcount();
		//std::cout << count;
		while(1)
		{
			system("cls");
			std::cout << "File Editor" << std::endl;
			Display();
			std::cout << std::endl;
			std::cout << "1 => Add, 2 => Update, 3 => Remove, 4 => Display, 5 => revertVersion 6 => exit " << std::endl;
			int option = -1;
			std::cin >> option;
			if (option == 1) 
			{
				/*Add*/Add();
				count += 1;
			}
			if (option == 2) 
			{
				/*Update*/ Update();
				count += 1;
			}
			if (option == 3) 
			{
				/*Remove*/ Remove();
				count += 1;
			}
			if (option == 4)
			{
				/*Display*/ Display();
			}

			if (option == 5) 
			{	//!ADD Version count As repeated
				/*RevertVersion*/ revertVersion();
			}
			if (option == 6) {/*break of loop*/ break; }

			if (count % (5+1) == 0 ) 
			{ 
				std::cout << currentVersion <<" " << fileName << std::endl;
				currentVersion += 1;
				addCommit();
				copystring(currentHead, fileDataList.mutable_filedatabase(currentVersion - 1));
				currentHead->set_commitcount(1);
				setHead();
				count = 1;
				
			}

			if (count != currentHead->commitcount()) { currentHead->set_commitcount(count); }
				}
	}

	void printData() 
	{
		std::cout << "[File]: "<<currentProject->filename() << " by " << currentProject->creater() << std::endl;
	}
	
	void Add()
	{
		std::string line;
		int flag = 0;
		std::cin.ignore();
		getline(std::cin, line);
		currentHead->add_textline()->assign(line.c_str());

		
	}
	void Update(){

		Display();
		std::string line;
		int index;
		std::cout<< "enter the index to update " << std::endl;
		std::cin >> index;
		if((index>=0 && index<currentHead->textline_size())&& currentHead->textline_size()!=0)
		std::cout << "Enter the text to be changed in " << index;
		std::cin.ignore();
		getline(std::cin, line);
		currentHead->mutable_textline(index)->assign(line.c_str());
		
	}
	void Remove()
	{
		Display();
		
		//std::string line;
		int index;
		std::cout << "enter the index to Delete " << std::endl;
		std::cin >> index;
		auto element = currentHead->textline(index);
		//currentHead->mutable_textline(index)->clear();
		for(auto it=currentHead->textline().begin();it!=currentHead->textline().end(); it++)
		{
			if (std::string(it->data()) == element) { currentHead->mutable_textline()->erase(it); break; };
		}
	
	}
	void Display()
	{	//implement empty file
		system("cls");
		std::cout <<"[" << fileName << "]  [V" << currentVersion << "]" << std::endl;
		for (int lineindex = 0; lineindex < currentHead->textline_size(); lineindex += 1)
			std::cout << lineindex << ". " << currentHead->textline(lineindex) << std::endl;
		if (!currentHead->textline_size()) { std::cout << "[File Empty]" << std::endl; }
	}
	void revertVersion(){
		for(int i=0;i< fileDataList.filedatabase_size(); i += 1)
		{
			std::cout << i+1 <<( i+1 == currentVersion?"*" : "") << " ";
		}
		int versiontohop;
		if (fileDataList.filedatabase_size() > 0 )
		{	
			
			std::cin >> versiontohop;
			if (versiontohop>0 && versiontohop <= fileDataList.filedatabase_size())
			{
				currentVersion = versiontohop;
				setHead();
			}
		}
	}

	void readData(std::string fileversion)
	{
		std::fstream binObject(fileversion+".bin", std::ios::in | std::ios::binary);
		if (!binObject.is_open())
		{
			std::cout << "textfile *.bin not found creating a new file" << std::endl;
		}
		else if (!(fileDataList.ParseFromIstream(&binObject)))
		{
			std::cout << "error while prasing *.bin file" << std::endl;
		}
	}

	void writeData(std::string fileversion)
	{
		std::fstream boutObject(fileversion + ".bin", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!boutObject.is_open()) { std::cout << "unable to open textfile *.bin file" << std::endl; }
		else if (!fileDataList.SerializePartialToOstream(&boutObject)) { std::cout << "unable to write data !data lost" << std::endl; }
	}

	~Editor() { writeData(fileName); currentProject->set_currentversion(currentVersion); }

};