//	Instruction Operand Register Module

class IORegister
{
	public:
		void Operation(string inst , Databus & DB, RegisterFile & RG , FlagRegister & FL)
		{
			if (inst[LIO]=='1')//Check if LIO == 1 for a new instruction only
			{
				string sn="";
				sn = sn + DB.DATA[4] + DB.DATA[5] + DB.DATA[6] + DB.DATA[7];
				RG.Snoop(sn);
				// Last 4 bits for Register ID
				sn = "";
				sn = sn + DB.DATA[5] + DB.DATA[6] + DB.DATA[7];
				// Last 3 bits of Flag
				FL.Snoop(sn);
				return ;
			}
		}
};
