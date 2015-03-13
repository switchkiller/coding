//	Memory Address Module

class MemoryAR
{
	private:
		char Address[WIDTH + 1];
	public:
		void SetAddress(Databus & DB)
		{
			strcpy(Address,DB.DATA);
			return ;
		}
		string GetAddress()
		{
			string ret = Address;
			return ret;
		}
		void Operation(string inst , Databus & DB)
		{
			if (inst[LMR] == '1')
			{
				strcpy(Address,DB.DATA);
				return ;
			}
			return ;
		}
};

