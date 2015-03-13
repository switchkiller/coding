//	Stack Module

class Stack
{
	private :
		char SP[WIDTH+1];
		int SPValue()
		{
			int ret = 0;
			for (int i=0;i< WIDTH ;i++)
				ret|= (SP[WIDTH -i - 1] == '1')?(1<<i):0;
			return ret;
		}
	public:
		void Init()
		{
			string s = ToStr(255);
			strncpy(SP,s.c_str(),WIDTH);
			return ;
		}
		void Isp()
		{
			int val = SignedValue(SP);
			val++;
			strncpy(SP,ToStr(val).c_str(),WIDTH);
			return ;
		}
		void Dsp()
		{
			int val = SignedValue(SP);
			val--;
			strncpy(SP,ToStr(val).c_str(),WIDTH);
			return ;
		}
		void Lsp(Databus & DB)
		{
			strncpy(SP,DB.DATA,WIDTH);
			return ;
		}
		void Esp(Databus & DB)
		{
			strncpy(DB.DATA,SP,WIDTH);
			return ;
		}
		void Operation(string inst , Databus & DB)
		{
			if (inst[DSP]=='1')
			{
				Dsp();
			}
			if (inst[LSP]=='1')
			{
				Lsp(DB);
			}
			if (inst[ISP]=='1')
			{
				Isp();
			}
			if (inst[ESP]=='1')
			{
				Esp(DB);
			}
			return ;
		}
		string Curr_Value()
		{
			string v = SP;
			return v;
		}
};
