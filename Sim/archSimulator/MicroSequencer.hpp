//	Micreo Sequencer Module

class MicroSequencer
{
	private:
		int glob;
		char L , R;
		int look;
		string Inst;
		int Address;
	public:
		void clear()
		{
			glob = 0;
		}
		int Sequencer(int address , Decoder & DC , FlagRegister & FL)
		{
			if (address ==0)
				Address = 0 ;
			if (address==0 && glob==0)
			{
				Address=0;
				glob++;
				return 0;
			}
			L = Inst[LMS] ; R = Inst[RMS];
			if (L=='1' && R=='0')
			{
				Address = DC.CurrAddress();
				return Address;
			}
			if (L=='0' && R=='0')
			{
				Address++;
				return Address;
			}
			if (R=='1' && L == '0')
			{
				if (Inst[SFL]=='1')
				{
					int fl = FL.getFLAG();
					if (fl == 0 )
					{
						return 0;
					}
					else
					{
						return ++Address;
					}
				}
				else
				{
					return 0;
				}
			}
			return 0;
		}
		void Operation(string inst , Decoder & DC)
		{
			Inst = inst;
			return ;
		}
};
