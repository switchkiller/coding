/*	
 *	Scanning of User's input program is done in this function
 *
 */
	
bool Scan_input(MemoryIO & Mem , ALU & ALU1 , RegisterFile & RG)
{
	char codef[100];
	FILE * filepointer;
	bool flag = false;
	do
	{
		cout << "\n\tPlease enter the program file : ";
		cin >> codef;
       	 	filepointer = fopen(codef,"r");
		if (errno)
		{
			perror("Invalid Entry : ");
		}
		else
			flag = true;
		errno = 0;
	}
	while (flag == false );
	fclose(filepointer);
//	Creating the label table
	{
		ifstream fin(codef);
		string str1="" , str2="" , str3="";
		int line = 0  , l = 0;
		while (TRUE)
		{
			fin >> str1; // Always a new instruction
			if (fin.eof()) // Code end
			{
				break;
			}
			if (str1=="brk")
			{
				breaks.insert(line);
				continue;
			}
			l = str1.length();
			if (str1[l-1]==':')
			{
				//Label Handle
				if (labels.find(str1)!=labels.end())
				{
					cout << "Error : Redefinition of label  : " <<str1<<"\n";
					return false ;
				}
				if (CheckHex(str1) == true )
				{
					cout << "The labels cannot be valid Hexadecimal numbers. Please change the label " << str1<<"\n\n";
					return false ;
				}
				// check if label is an instruction
				if (ALU1.SelectBits.count(str1) != 0)
				{
					cout << "Error. Instruction defined as a label : "<<str1<<"\n";
					return false;
				}
				labels.insert(str1);
				label_lookup[str1] = line;
				continue ;
			}
			if (str1[0]=='r' ) // Return Statement
			{
				line++;
				continue;
			}
			if (inst_len[str1] == 4)
			{
				fin >> str2;// Register Value is scanned
				line++;
			}
			if (inst_len[str1] == 8 )
			{
				line++;
			}
			if (str1[0]=='j' || (str1[0]=='c' && (str1[1]=='d' || str1[1]=='r'))) // Jump or Call instruction
       	       		{
				line++;
				if (str1[l-2]=='d' || str1[l-3]=='d')  // only if a direct inst.
				{
					line++;
                        		fin >> str2;
                		}
                	}
			if (str1[l-1] == 'i') // Immediate Instruction
			{
				int j;fin >>j;//Integer Scan
				line++;
			}
		}
		fin.close();
	}
//	Page ID Section	
	cout << "\n\n\tYou have 256 pages in Memory each of size 256 bytes.\n";
	while ( TRUE )
	{
		string ss="";
		cout << "\tSelect Memory page (0-255) : ";
		cin  >> ss;
		bool page="true";
		int l_ss = ss.length();
		for (int i=0;i<l_ss;i++)
		{
			if (((ss[i]-'0') > 9) || ((ss[i]-'0')<0))
			{
				cout << "Invalid Entry : Enter a number 0-255 \n";
				page = false;
				break;
			}
		}
		if (page == false )
			continue ;
		int _tt = atoi(ss.c_str());
		if (_tt<0 || _tt > 255)
		{
			cout << "Invalid PageID : Enter a number 0-255 \n";
			continue ;
		}
		if (pages.find(_tt) == pages.end())
		{
			pages.insert(_tt);
			PageID = _tt;
			break;
		}
		else
		{
			char ch = 'y';
			cout << "\n\tPage  already used . Do you want to use it [y/n]? : ";
			cin >> ch;
			if (ch == 'y')
			{
				PageID = _tt;
				break;
			}
		}
	}

//	Label table ready

	bool ret = Make_operation( codef , Mem , ALU1 , RG);
	
	if (ret == false )
		return ret;
	return true;
}
