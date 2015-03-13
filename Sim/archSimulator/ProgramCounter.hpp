//	This class implements Program Counter Module

class ProgramCounter
{
	private:
		char counter[WIDTH];
	public:
		void Init(string start)
		{
			strcpy(counter,start.c_str());
			return ;
		}
		void Epc(Databus & DB)
		{
			strcpy(DB.DATA,counter);
			return ;
		}
		void Lpc(Databus & DB)
		{
			strcpy(counter,DB.DATA);
			return ;
		}
		void Ipc()
		{
			int t=SignedValue(counter);
			t++;
			string res = ToStr(t);
			strncpy(counter,res.c_str(),WIDTH);
			return ;
		}
		void Operation(string inst , Databus & DB)
		{
			if (inst[IPC]=='1')//Increment
			{
				Ipc();
			}
			if (inst[LPC]=='1')//Load
			{
				Lpc(DB);
			}
			if (inst[EPC]=='1')//Enable
			{
				Epc(DB);
			}
			return ;
		}
		void S_Operation(string inst, Databus & DB)
		{
			if (inst[LPC] == '1')
				Lpc(DB);
		}
		string Curr_Value()
		{
			string st = counter;
			return st;
		}
};
