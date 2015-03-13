//	Accumulator Module

class Accumulator
{
	private:
		char Result[WIDTH+1];
	public:
		void Ear(Databus & DB)
		{
			strncpy(DB.DATA,Result,WIDTH);
			return ;
		}
		void Lar(ALU & A)
		{

			strcpy(Result,A.getResult().c_str());
			return ;
		}
		void Rar()
		{
			strcpy(Result,"00000000");
			return ;
		}
		void Operation(string inst , Databus & DB , ALU & A)
		{
			if (inst[EAR]=='1')
			{
				Ear(DB);
			}
			if (inst[RAR]=='1')
			{
				Rar();
			}
			if (inst[LAR]=='1')
			{
				Lar(A);
			}
			return ;
		}
		void S_Operation(string inst, Databus &DB )
		{
			if (inst[EAR] == '1')
			{
				Ear(DB);
			}
			return ;
		}
		string Curr_Value()
		{
			string v = Result;
			return v;
		}
};

