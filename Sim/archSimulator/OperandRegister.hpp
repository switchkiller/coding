//	Operand Register Module

class OperandRegister
{
	private :
		char Operand[WIDTH+1];
	public:
		void Eor(Databus & DB)
		{
			strncpy(DB.DATA,Operand,WIDTH);
			return ;
		}
		void Lor(Databus & DB)
		{
			strncpy(Operand,DB.DATA,WIDTH);
			return ;
		}
		void Ror()
		{
			strncpy(Operand,"00000000",WIDTH);
			return ;
		}
		void Operation(string inst , Databus & DB)
		{
			if (inst[EOR]=='1')
			{
				Eor(DB);
			}
			if (inst[ROR]=='1')
			{
				Ror();
			}
			if (inst[LOR] == '1')
			{
				Lor(DB);
			}
			return ;
		}
		string Curr_Value()
		{
			string s = Operand;
			return s;
		}
};
