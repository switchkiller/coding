//	ALU class
class ALU
{
	private:
		string Result;
	public:
		map<string,string> SelectBits;
		string getResult()
		{
			return Result;
		}
		void Operation(string  inst , Databus & DB , OperandRegister & Op , FlagRegister & FL)
		{
			bool flag = false;
			string 	SelectFlag="";
			SelectFlag = inst.substr(SAF,4);
			int temp1=0 , temp2 = 0 , result = 0;
			if (SelectFlag == "0000")
			{
				;
			}
			if (SelectFlag == "1111") // dummy select bits
			{
				result = Value(DB.DATA);
				Result = DB.DATA; // AR = DB.DATA : Dummy Instruction
			}
			if (SelectFlag == "0001") // Add select bits
			{
				flag = true;
				temp1 = Value(DB.DATA);
				char S[100];
				strcpy(S,(Op.Curr_Value()).c_str());
				temp2 = Value(S);
				result = temp1 + temp2 ;
				Result = ToStr(result);
			}
			if (SelectFlag == "0010") // Subs select bits
			{
				flag = true;
				temp1 = Value(DB.DATA);
				char S[100];
			       	strcpy(S,(Op.Curr_Value()).c_str());
				temp2 = Value(S);
				result = temp1 - temp2 ;
				Result = ToStr(result);
			}
			if (SelectFlag == "0011") // Xor select bits
			{
				flag = true;
				temp1 = Value(DB.DATA);
			       	char S[100];
				strcpy(S,(Op.Curr_Value()).c_str());
				temp2 = Value(S);
				result = temp1 ^ temp2 ;
				Result = ToStr(result);
			}
			if (SelectFlag == "0100") // and select bits
			{
				flag = true ;
				temp1 = Value(DB.DATA);
				char S[100];
				strcpy(S,(Op.Curr_Value()).c_str());
				temp2 = Value(S);
				result = temp1 & temp2 ;
				Result = ToStr(result);
			}
			if (SelectFlag == "0101") // or select bits
			{
				flag = true ;
				temp1 = Value(DB.DATA);
				char S[100];
				strcpy(S,(Op.Curr_Value()).c_str());
				temp2 = Value(S);
				result = temp1 | temp2 ;
				Result = ToStr(result);
			}
/*		Flag operations .
 *
 *	FLAG[1] = Zero    Bit
 *	FLAG[3] = Sign    Bit
 *	FLAG[5] = Carry   Bit
 *	FLAG[7] = Parity  Bit (Odd only)
 */
			if (flag == true )
			{
				if (result == 0)
				{
					FL.SetBit(1);
					FL.ResetBit(2);
				}
				else
				{
					FL.ResetBit(1);
					FL.SetBit(2);
				}
				if (result < 0)
				{
					FL.SetBit(3);
					FL.ResetBit(4);
				}
				else
				{
					FL.ResetBit(3);
					FL.SetBit(4);
				}
				string tmp = Result;
				int count =0;
				for (unsigned int ii=0;ii<tmp.length();ii++)
				{
					if (tmp[ii]=='1')
						count++;
				}
				if (count%2 == 0)
				{
					FL.ResetBit(7);
				}
				else
				{
					FL.SetBit(7);
				}
				if (result>>9&1)
				{
					FL.SetBit(5);
					FL.ResetBit(6);
				}
				else
				{
					FL.ResetBit(5);
					FL.SetBit(6);
				}
			}
			return ;
		}
};
