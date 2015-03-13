//	Decoder Class

class Decoder
{
	private :
		int Address ;
		string opcode ;
		string Bit_opcode;
	public:
		void Operation(string inst , Databus & DB)
		{
			if (inst[LIR]=='1')
			{
				opcode = "";
				Bit_opcode = "";
				inst = DB.DATA;
				opcode = opcode + inst[0] + inst[1] + inst[2] + inst[3];
				Bit_opcode = opcode + inst[4];//5 bits of instruction for special instructions
				//Accomodate call , jump instruction and instructions of 0 address
				if (Bit_opcode == "00001" || Bit_opcode=="11100" || Bit_opcode=="11101" || Bit_opcode=="11110" || Bit_opcode=="11111")
				{
					opcode = Bit_opcode;
				}
				if (Bit_opcode == "00000")
					opcode = inst;
/*				if (opcode =="0000" || opcode=="1110" || opcode=="1111") //   CHECK 
				{
					if ( inst != "00000000" && inst != "00000001") { // jmpd/jmpr/cd/cr/ret 
						opcode = Bit_opcode;//Entire instruction length
					}
					else {// Stop  and nop 
						opcode = inst;
					}
				}
*/				
				Address = lookup[opcode];
			}
			return ;
		}
		int CurrAddress()
		{
			return Address;
		}
		int LastBit()
		{
			return (Bit_opcode[4]-'0');
		}
};

