//	Register File Module

class RegisterFile
{
	private :
		string snoop;
	public:
		map<string , string> value_of_register;//Value (in binary) contained in the register  eg. value_of_register["0000"]="00000010"
		map<string , string> Registers; // Register  id  , a map from register name to an binary integer  Registers["r0"]="0000"
		void SetRegister(string reg , int val)
		{
			value_of_register[Registers[reg]]=ToStr(val);
			return ;
		}
		RegisterFile()
		{//	8 Registers being supported
			snoop="";
			Registers["r0"]		="0000";
			Registers["r1"]		="0001";
			Registers["r2"]		="0010";
			Registers["r3"]		="0011";
			Registers["r4"]		="0100";
			Registers["r5"]		="0101";
			Registers["r6"]		="0110";
			Registers["r7"]		="0111";
			Registers["r8"]		="1000";
			Registers["r9"]		="1001";
			Registers["r10"]	="1010";
			Registers["r11"]	="1011";
			Registers["PC"]		="1100";
			Registers["SP"]		="1101";
			Registers["AR"]		="1110";
			Registers["OR"]		="1111";
		}
		void Snoop(string S)
		{
			snoop = S;
			return ;
		}
		void Operation(string inst , Databus & DB,ProgramCounter & PC,Stack & St,Accumulator & AC,OperandRegister & Op, ALU & ALU1)
		{
			string oper="";
			if (inst[ERG]=='1')
			{
				if (inst[MRG] == '0')
				{
					oper = snoop;
				}
				else
				{
					oper = inst.substr(SRG,4);
				}
				if (oper == "1100")
				{
					PC.Epc(DB);
				}
				else if (oper == "1101")
				{
					St.Esp(DB);
				}
				else if (oper == "1110")
				{
					AC.Ear(DB);
				}
				else if (oper == "1111")
				{
					Op.Eor(DB);
				}
				else
					strcpy(DB.DATA,value_of_register[oper].c_str());
			}
			if (inst[LRG] == '1')
			{
				if (inst[MRG]=='0')
				{
					oper=snoop;
				}
				else
				{
					oper = inst.substr(SRG,4);
				}
				if (oper == "1100")
				{
					PC.Lpc(DB);
				}
				else if (oper == "1101")
				{
					St.Lsp(DB);
				}
				else if (oper == "1110")
				{
					AC.Lar(ALU1);
				}
				else if (oper == "1111")
				{
					Op.Lor(DB);
				}
				else
				{
					value_of_register[oper]=DB.DATA;
				}
			}
			return ;
		}
};
