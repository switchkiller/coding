//	Memory Module

class MemoryIO
{
	public:
		char Memory[256][256][WIDTH+1];
		MemoryIO()
		{
			for (int i=0;i<256;i++)
				for (int j=0;j<256;j++)
					strcpy(Memory[i][j],"");
		}
		bool FillMemory()
		{
			string fname="";
			cout << " \tEnter file name with Memory details (enter 'none' to escape) :";
			cin >> fname;
			if (fname != "none")
			{
				FILE *fp;
				if ( (fp = fopen(fname.c_str(),"r") ) == NULL )
				{
					cout << " Error opening file\n";
					return -1;
				}
				int t, M , N, k = 0 , l = 0;
				char arr[100];
				while ( (fscanf(fp,"%d %d :",&M,&N)) != EOF )
				{
					if (M == 0 && N == 0)
					{
						break;
					}
					if (M < 0 || N < 0 )
					{
						cout << " Incorrect input file\n";
						return false;
					}
					for (int i=0; i < N; i++)
					{
						fscanf(fp,"%d",&t);
						string s = ToStr(t);
						strcpy(arr,s.c_str());
						if ( M > 255 )
						{
							cout << " Memory Limit Exceeded \n";
							return -1;
						}
						strcpy(Memory[PageID][M++],arr);
					}
					k++;l=0;
				}
				fclose(fp);
			}
			return true;
		}
		void SetMem(char address[WIDTH] , char value[WIDTH])
		{
			int Addr =0;
			Addr = SignedValue(address);
			strcpy(Memory[PageID][Addr],value);
			return ;
		}
		void GetFromMemory(Databus & DB , MemoryAR & MR)
		{
			int Addr =0;
			string ret = MR.GetAddress();
			Addr = SignedValue(ret.c_str());
			strcpy(DB.DATA,Memory[PageID][Addr]);
		}
		void PutIntoMemory(Databus & DB , MemoryAR & MR)
		{
			int Addr =0;
			string ret = MR.GetAddress();
			Addr = SignedValue(ret.c_str());
			strcpy(Memory[PageID][Addr],DB.DATA);
		}
		void Operation(string inst , Databus & DB , MemoryAR & MR )
		{
			if (inst[ERD]=='1')
			{
				GetFromMemory(DB,MR);
			}
			if (inst[LWR]=='1')
			{
				PutIntoMemory(DB,MR);
			}
			return ;
		}
};
