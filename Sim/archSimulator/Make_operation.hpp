 /*	
 *	This is a mini interpreter module called by the Scan file as a subroutine .
 *
 */

bool Make_operation(char fname[] , MemoryIO & Mem , ALU & ALU1 , RegisterFile & RG)
{
	string str1="" , str2 = "" , str3="";
	ifstream fin(fname);
	int k = 0;
	while ( TRUE )
	{
		fin >> str1;
		if (fin.eof())
			break;
		if (str1[str1.length()-1]==':') // Label
		{
			continue;
			//Do Nothing
		}
		// Error check if the mneumonic instruction is valid
		if (inst_len[str1] == 8) // Instruction of 8 bit length
		{
			char tmp[100];tmp[0]=0;
			strcpy(tmp,ALU1.SelectBits[str1].c_str());
			strcpy(Mem.Memory[PageID][k++],tmp);
		}
		if (inst_len[str1] == 4 ) // It is not an immediate instruction
		{
			char tmp[100];tmp[0]=0;
			fin >> str2;
			// str2 contains the name of the register. Check if invalid name is given.
			{
				if (RG.Registers.count(str2) == 0 )
				{
					cout << "Invalid register number "<<str2<<"\n";
					return false ;
				}
			}
			strcpy(tmp,ALU1.SelectBits[str1].c_str());	/**/
			strcat(tmp,RG.Registers[str2].c_str());		/**/
			strcpy(Mem.Memory[PageID][k++],tmp);
		}
		if (str1[str1.length()-1]=='i') // If immediate instruction
		{
			int j;fin >>j;
			string f = ToStr(j);
			char tmp[100];tmp[0]=0;
			strcpy(tmp,f.c_str());
			strcpy(Mem.Memory[PageID][k++],tmp);
		}
		// 5 bit instructions 
		{
			if (str1[0]=='j' && str1[str1.length()-1]!=':')//Jump instruction
			{
				char tmp[100];tmp[0]=0;
				int l = str1.length();
				string ret = "", fl="";
				bool direct = false;
				if (str1[l-1] == 'z' || str1[l-1]=='c' || str1[l-1]=='p')
				{
					if (str1[l-2]=='o' || str1[l-2]=='n') //  op , nz , nc flag
					{
						ret = str1.substr(0,l-2);
						fl = fl + str1[l-2] + str1[l-1];
						if (str1[l-3]=='d')
							direct = true;
					}
					else
					{
						ret = str1.substr(0,l-1);
						fl = fl + str1[l-1];
						if (str1[l-2]=='d')
							direct = true;
					}
				}
				if (str1[l-1]=='m')
				{
					ret = str1.substr(0,l-1);
					fl = fl + str1[l-1];
					if (str1[l-2]=='d')
						direct = true;
				}
				if (str1[l-1]=='u')
				{
					ret = str1.substr(0,l-1);
					fl = "u";
					if (str1[l-2]=='d')
						direct = true;
				}
				if (ALU1.SelectBits.count(ret) == 0)
				{
					cout << "Error. Undefined Symbol : "<<str1<<"\n";
					return false;
				}
				strcpy(tmp,ALU1.SelectBits[ret].c_str());
				if (flag_lookup.count(fl) == 0)
				{
					cout << "Error. Undefined Flag : "<<fl<<"\n";
					return false;
				}
				strcat(tmp,flag_lookup[fl].c_str());
				strcpy(Mem.Memory[PageID][k++],tmp);
				if (direct == true )
				{
					string s="";
					fin >> s;
					if (CheckHex(s) == false )
					{
						s=s+":";
						if (labels.find(s)==labels.end())
						{
							printf("Undefined Label :\t%s\n",s.c_str());
							return false ;
						}
						int j = label_lookup[s] ; // AVI Changed
						s = ToStr(j);
					}
					else
					{
						bool chk = CheckHex(s);
						if (chk == true)
						{
							s = HexToBin(s);
						}
						else
						{
							s=s+":";
							if (labels.find(s)==labels.end())
							{
								printf("Undefined Label :\t%s\n",s.c_str());
								return false ;
							}
							int j = label_lookup[s]; //AVI Changed
							s = ToStr(j);
						}
					}
					strcpy(Mem.Memory[PageID][k++],s.c_str());
				}
			}
			if (str1[str1.length()-1]!=':' && (str1[0]=='c' && (str1[1]=='d' || str1[1]=='r')))//Call instruction
			{
				char tmp[100];tmp[0]=0;
				int l = str1.length();
				string ret = "", fl="";
				bool direct = false;
				if (str1[l-1] == 'z' || str1[l-1]=='c' || str1[l-1]=='p')
				{
					if (str1[l-2]=='o' || str1[l-2]=='n') //  op , nz , nc flag
					{
						ret = str1.substr(0,l-2);
						fl = fl + str1[l-2]+str1[l-1];
						if (str1[l-3]=='d')
							direct = true;
					}
					else
					{
						ret = str1.substr(0,l-1);
						fl = fl + str1[l-1];
						if (str1[l-2]=='d')
							direct = true;
					}
				}
				if (str1[l-1]=='m')
				{
					ret = str1.substr(0,l-1);
					fl = fl + str1[l-1];
					if (str1[l-2]=='d')
						direct = true;
				}
				if (str1[l-1]=='u')
				{
					ret = str1.substr(0,l-1);
					fl = "u";
					if (str1[l-2]=='d')
						direct = true;
				}
				if (ALU1.SelectBits.count(ret) == 0)
				{
					cout << "Error. Undefined Symbol : "<<str1<<"\n";
					return false;
				}
				strcpy(tmp,ALU1.SelectBits[ret].c_str());
				if (flag_lookup.count(fl) == 0)
				{
					cout << "Error. Undefined Flag : "<<fl<<"\n";
					return false;
				}
				strcat(tmp,flag_lookup[fl].c_str());
				strcpy(Mem.Memory[PageID][k++],tmp);
				if (direct == true )
				{
					string s="";
					fin >> s;
					if (CheckHex(s) == false )
					{
						s=s+":";
						if (labels.find(s)==labels.end())
						{
							printf("Undefined Label :\t%s\n",s.c_str());
							return false ;
						}
						int j = label_lookup[s];
						s = ToStr(j);
					}
					else
					{
						bool chk = CheckHex(s);
						if (chk == true)
						{
							s = HexToBin(s);
						}
						else
						{
							s=s+":";
							if (labels.find(s)==labels.end())
							{
								printf("Undefined Label :\t%s\n",s.c_str());
								return false ;
							}
							int j = label_lookup[s];
							s = ToStr(j);
						}
					}
					strcpy(Mem.Memory[PageID][k++],s.c_str());
				}
			}
			if (str1[0]=='r' && str1[str1.length()-1]!=':') // A return instruction
			{
				/* Code for return  */
				char tmp[100];tmp[0]=0;
				int l = str1.length();
				string ret = "", fl="";
				if (str1[l-1] == 'z' || str1[l-1]=='c' || str1[l-1]=='p')
				{
					if (str1[l-2]=='o' || str1[l-2]=='n') //  op , nz , nc flag
					{
						ret = str1.substr(0,l-2);
						fl = fl + str1[l-2]+str1[l-1];
					}
					else
					{
						ret = str1.substr(0,l-1);
						fl = fl + str1[l-1];
					}
				}
				if (str1[l-1]=='m')
				{
					ret = str1.substr(0,l-1);
					fl = fl + str1[l-1];
				}
				if (str1[l-1]=='u')
				{
					ret = str1.substr(0,l-1);
					fl = fl + str1[l-1];
				}
				if (ALU1.SelectBits.count(ret) == 0)
				{
					cout << "Error. Undefined Symbol : "<<str1<<"\n";
					return false;
				}
				strcpy(tmp,ALU1.SelectBits[ret].c_str());
				if (flag_lookup.count(fl) == 0)
				{
					cout << "Error. Undefined Flag : "<<fl<<"\n";
					return false;
				}
				strcat(tmp,flag_lookup[fl].c_str());
				strcpy(Mem.Memory[PageID][k++],tmp);
			}
		}
	}
	fin.close();
	return true;
}
