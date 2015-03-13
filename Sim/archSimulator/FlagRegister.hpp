//	Flag Register Module

class FlagRegister
{
	private:
		char FLAG[8];
		string SN;
		/*
		 * 	FLAG[0] = Unconditional
		*	FLAG[1] = Zero    Bit
		* 	FLAG[3] = Sign    Bit
		*	FLAG[5] = Carry   Bit
		*	FLAG[7] = Parity  Bit  ( ODD )
		*/
	public:
		FlagRegister()
		{
			FLAG[0]='1';
		}
		void Snoop(string s)
		{
			SN = s;
			return ;
		}
		void Operation(string inst)
		{
			return ;
		}
		int getFLAG()
		{
			int v = Value(SN.c_str());
			return (FLAG[v]-'0');
		}
		void SetBit(int bit)
		{
			if ( bit >=1 && bit<8 )
				FLAG[bit]='1';
			return ;
		}
		void ResetBit(int bit)
		{
			if ( bit>=1 && bit<8 )
				FLAG[bit]='0';
			return ;
		}
		void PrintAllFlags()
		{
			cout << "\nFlag Values\n";
			cout << " Uncondtional Flag : "<<FLAG[0]<<"  Zero Flag : "<<FLAG[1]<<"  Sign Flag : "<<FLAG[3]<<"  Carry Flag : "<< FLAG[5];
			cout << "  Parity Flag : "<<FLAG[7]<<"\n\n";
			return ;
		}
};
