
/*
 *  	This is the Display Module of the program .
 *	This will be called whenever a Memory Map is printed .
 */

class Display
{
	public:
		char Memory[17][17][WIDTH+1];
		void SetMemory(int address , char value[],MemoryIO & Mem)
		{
//			Mem.SetMem("", value);
			return ;
		}
		void MemoryValue(int start  , int offset , MemoryIO & Mem)
		{
			for (int i=start;i<start + offset;i++)
			{
				if (COUT) // Console Output
				{
					fprintf(stdout,"Address : %d\tValue Stored : %d\n",i,Mem.Memory[PageID][i]);
				}
				if (FOUT) // File Output
				{
					fprintf(fout,"Address : %d\tValue Stored : %s\n",i,Mem.Memory[PageID][i]);
				}
			}
			return ;
		}
		void AllRegisterValues(RegisterFile & RG,ProgramCounter & PC , Stack & St,Accumulator & AC, OperandRegister & Op)
		{
		  //		fprintf(stdout,"\n\n\t\t Value of Registers \n");
				fprintf(stdout,"__________________________________________________________________________\n");
				char pr[10];pr[0]=0;
				fprintf(stdout," r0  r1  r2  r3  r4  r5  r6  r7  r8  r9  r10  r11  PC  SP  AR  OR\n ");
				for (int kk=0;kk<8;kk++)
				{
					sprintf(pr,"r%d",kk);
					string ff=pr;
					fprintf(stdout,"%s  ",toHexS(RG.value_of_register[RG.Registers[ff]]).c_str());
				}
				//fprintf(stdout,"\n r8  r9  r10  r11  PC  SP  AR  OR\n ");
				for (int kk=8;kk<12;kk++)
				{
					sprintf(pr,"r%d",kk);
					string ff=pr;
					if (kk>9)fprintf(stdout," ");
					fprintf(stdout,"%s  ",toHexS(RG.value_of_register[RG.Registers[ff]]).c_str());
				}
				fprintf(stdout,"%s  %s  %s  %s\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());
				fprintf(stdout,"_______________________________________________________________________\n");
		}
		Display()
		{
			strcpy(Memory[0][0]," ");
			strcpy(Memory[0][1],"0");
			strcpy(Memory[0][2],"1");
			strcpy(Memory[0][3],"2");
			strcpy(Memory[0][4],"3");
			strcpy(Memory[0][5],"4");
			strcpy(Memory[0][6],"5");
			strcpy(Memory[0][7],"6");
			strcpy(Memory[0][8],"7");
			strcpy(Memory[0][9],"8");
			strcpy(Memory[0][10],"9");
			strcpy(Memory[0][11],"A");
			strcpy(Memory[0][12],"B");
			strcpy(Memory[0][13],"C");
			strcpy(Memory[0][14],"D");
			strcpy(Memory[0][15],"E");
			strcpy(Memory[0][16],"F");
			strcpy(Memory[1][0],"0");
			strcpy(Memory[2][0],"1");
			strcpy(Memory[3][0],"2");
			strcpy(Memory[4][0],"3");
			strcpy(Memory[5][0],"4");
			strcpy(Memory[6][0],"5");
			strcpy(Memory[7][0],"6");
			strcpy(Memory[8][0],"7");
			strcpy(Memory[9][0],"8");
			strcpy(Memory[10][0],"9");
			strcpy(Memory[11][0],"A");
			strcpy(Memory[12][0],"B");
			strcpy(Memory[13][0],"C");
			strcpy(Memory[14][0],"D");
			strcpy(Memory[15][0],"E");
			strcpy(Memory[16][0],"F");
		}
		void InitialMap(MemoryIO & Mem , RegisterFile & RG , ProgramCounter & PC , Accumulator & AC , OperandRegister & Op , Stack & St)
		{
			int k=0;
			if (COUT)// Console Output if it is selected
			{
				fprintf(stdout,"\n\n\t\t\tMemory Map\n\n");
				fprintf(stdout,"_______________________________________________________________________________________________________________\n\n");
				for (int i=0;i<17;i++)
					fprintf(stdout,"%s     ",Memory[0][i]);
				fprintf(stdout,"\n\n");
				k=0;
				for (int i=1;i<17;i++)
				{
					for (int j=0;j<17;j++)
					{
						if (j==0)
						{
							fprintf(stdout,"%s     ",Memory[i][j]);
							continue;
						}
						if (strcmp(Mem.Memory[PageID][k],""))
						{
							fprintf(stdout,"%s    ",toHex(Mem.Memory[PageID][k]).c_str());
						}
						else
							fprintf(stdout,"      ");
						k++;
					}
					fprintf(stdout,"\n");
				}

				fprintf(stdout,"\n\n\t\t Value of Registers Initially \n");
				fprintf(stdout,"__________________________________________________________________________________________________________________\n\n");
				char pr[10];pr[0]=0;
				fprintf(stdout," r0  r1  r2  r3  r4  r5  r6  r7\n ");
				for (int kk=0;kk<8;kk++)
				{
					sprintf(pr,"r%d",kk);
					string ff=pr;
					fprintf(stdout,"%s  ",toHexS(RG.value_of_register[RG.Registers[ff]]).c_str());
				}
				fprintf(stdout,"\n r8  r9  r10  r11  PC  SP  AR  OR\n ");
				for (int kk=8;kk<12;kk++)
				{
					sprintf(pr,"r%d",kk);
					string ff=pr;
					if (kk>9)fprintf(stdout," ");
					fprintf(stdout,"%s  ",toHexS(RG.value_of_register[RG.Registers[ff]]).c_str());
				}
				fprintf(stdout,"%s  %s  %s  %s\n\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());

/*				fprintf(stdout,"\t\tRegister ID\n\n  \t00\t01\t10\t11\n\n");
				for (int i=0;i<3;i++)
				{
					if (i==0)
						fprintf(stdout,"00");
					else if(i==1)
						fprintf(stdout,"01");
					else if(i==2)
						fprintf(stdout,"10");
					for (int j=0;j<4;j++)
					{
						sprintf(pr,"r%d",kk++);
						string ff=pr;
						fprintf(stdout,"\t%s",toHexS(RG.value_of_register[RG.Registers[ff]]).c_str());
					}
					fprintf(stdout,"\n\n");
				}
				fprintf(stdout,"  \tPC\tSP\tAR\tOR\n\n");
		fprintf(stdout,"  \t%s\t%s\t%s\t%s\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());
*/
				fprintf(stdout,"\n_______________________________________________________________________\n\n");
			}
			if (FOUT)// File Output if it is selected
			{
				fprintf(fout,"\n\n\t\t\tMemory Map\n\n\n");
				fprintf(fout,"_________________________________________________________________________________\n\n");
				for (int i=0;i<17;i++)
					fprintf(fout,"%s     ",Memory[0][i]);
				fprintf(fout,"\n\n");
				k=0;
				for (int i=1;i<17;i++)
				{
					for (int j=0;j<17;j++)
					{
						if (j==0)
						{
							fprintf(fout,"%s     ",Memory[i][j]);
							continue;
						}
						if (strcmp(Mem.Memory[PageID][k],""))
							fprintf(fout,"%s    ",toHex(Mem.Memory[PageID][k]).c_str());
						else
							fprintf(fout,"      ");
						k++;
					}
					fprintf(fout,"\n\n");
				}
				fprintf(fout,"\n\n\t\t Value of Registers Initially \n");
				fprintf(fout,"__________________________________________________________________________________________________________________\n\n");
				char pr[10];pr[0]=0;
				int kk=0;
				fprintf(fout,"\t\tRegister ID\n\n  \t00\t01\t10\t11\n\n");
				for (int i=0;i<3;i++)
				{
					if (i==0)
						fprintf(fout,"00");
					else if(i==1)
						fprintf(fout,"01");
					else if(i==2)
						fprintf(fout,"10");
					for (int j=0;j<4;j++)
					{
						sprintf(pr,"r%d",kk++);
						string ff=pr;
		//				fprintf(fout,"\t",toHex(RG.value_of_register[RG.Registers[ff]].c_str()).c_str());
					}
					fprintf(fout,"\n\n");
				}
				fprintf(fout,"  \tPC\tSP\tAR\tOR\n\n");
		fprintf(fout,"  \t%s\t%s\t%s\t%s\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());
				fprintf(fout,"\n_______________________________________________________________________\n\n");
			}
			return ;
		}
		void FinalMap(MemoryIO & Mem , RegisterFile & RG , ProgramCounter & PC , Accumulator & AC , OperandRegister & Op , Stack & St)
		{
			int k=0;
			if (COUT)// Console Output if it is selected
			{
				fprintf(stdout,"\n\n\t\t\tMemory Map\n\n\n");
				fprintf(stdout,"________________________________________________________________________________________________________________\n");
				for (int i=0;i<17;i++)
					fprintf(stdout,"%s     ",Memory[0][i]);
				fprintf(stdout,"\n\n");
				k=0;
				for (int i=1;i<17;i++)
				{
					for (int j=0;j<17;j++)
					{
						if (j==0)
						{
							fprintf(stdout,"%s     ",Memory[i][j]);
							continue;
						}
						if (strcmp(Mem.Memory[PageID][k],""))
							fprintf(stdout,"%s    ",toHex(Mem.Memory[PageID][k]).c_str());
						else
							fprintf(stdout,"      ");
						k++;
					}
					fprintf(stdout,"\n");
				}
				fprintf(stdout,"\n\n\t\t Value of Registers\n");
				fprintf(stdout,"__________________________________________________________________________________________________________________\n\n");
				char pr[10];pr[0]=0;
				int kk=0;
				fprintf(stdout,"\t\tRegister ID\n\n  \t00\t01\t10\t11\n\n");
				for (int i=0;i<3;i++)
				{
					if (i==0)
						fprintf(stdout,"00");
					else if(i==1)
						fprintf(stdout,"01");
					else if(i==2)
						fprintf(stdout,"10");
					for (int j=0;j<4;j++)
					{
						sprintf(pr,"r%d",kk++);
						string ff=pr;
						fprintf(stdout,"\t%s",toHexS(RG.value_of_register[RG.Registers[ff]]).c_str());
					}
					fprintf(stdout,"\n\n");
				}
				fprintf(stdout,"  \tPC\tSP\tAR\tOR\n\n");
		fprintf(stdout,"  \t%s\t%s\t%s\t%s\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());
				fprintf(stdout,"\n_______________________________________________________________________\n\n");
			}
			if (FOUT)// File  Output if it is selected
			{
				fprintf(fout,"\n\n\t\t\tMemory Map\n\n\n");
				fprintf(fout,"_________________________________________________________________________________\n\n");
				for (int i=0;i<17;i++)
					fprintf(fout,"%s     ",Memory[0][i]);
				fprintf(fout,"\n");
				k=0;
				for (int i=1;i<17;i++)
				{
					for (int j=0;j<17;j++)
					{
						if (j==0)
						{
							fprintf(fout,"%s     ",Memory[i][j]);
							continue;
						}
						if (strcmp(Mem.Memory[PageID][k],""))
							fprintf(fout,"%s    ",toHex(Mem.Memory[PageID][k]).c_str());
						else
							fprintf(fout,"      ");
						k++;
					}
					fprintf(fout,"\n\n");
				}
				fprintf(fout,"\n\n\t\t Value of Registers\n");
				fprintf(fout,"__________________________________________________________________________________________________________________\n\n");
				char pr[10];pr[0]=0;
				int kk=0;
				fprintf(fout,"\t\tRegister ID\n\n  \t00\t01\t10\t11\n\n");
				for (int i=0;i<3;i++)
				{
					if (i==0)
						fprintf(fout,"00");
					else if(i==1)
						fprintf(fout,"01");
					else if(i==2)
						fprintf(fout,"10");
					for (int j=0;j<4;j++)
					{
						sprintf(pr,"r%d",kk++);
						string ff=pr;
		//				fprintf(fout,"\t",toHex(RG.value_of_register[RG.Registers[ff]].c_str()).c_str());
					}
					fprintf(fout,"\n\n");
				}
				fprintf(fout,"  \tPC\tSP\tAR\tOR\n\n");
		fprintf(fout,"  \t%s\t%s\t%s\t%s\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());
				fprintf(fout,"\n_______________________________________________________________________\n\n");
			}
			return ;
		}
		void MemoryMap(MemoryIO & Mem,RegisterFile & RG)
		{
			int k=0;
			if (COUT)// Console Output if it is selected
			{
				fprintf(stdout,"\n\n\t\t\tMemory Map\n\n\n");
				fprintf(stdout,"______________________________________________________________________________________________________________________\n\n");
				for (int i=0;i<17;i++)
					fprintf(stdout,"%s     ",Memory[0][i]);
				fprintf(stdout,"\n\n");
				k=0;
				for (int i=1;i<17;i++)
				{
					for (int j=0;j<17;j++)
					{
						if (j==0)
						{
							fprintf(stdout,"%s     ",Memory[i][j]);
							continue;
						}
						if (strcmp(Mem.Memory[PageID][k],""))
							fprintf(stdout,"%s    ",toHex(Mem.Memory[PageID][k]).c_str());
						else
							fprintf(stdout,"      ");
						k++;
					}
					fprintf(stdout,"\n");
				}
				fprintf(stdout,"\n______________________________________________________________________________________________________________\n\n");
			}
			if (FOUT)// File Output if it is selected
			{
				fprintf(fout,"\n\n\t\t\tMemory Map\n\n\n");
				fprintf(fout,"_________________________________________________________________________________\n\n");
				for (int i=0;i<17;i++)
					fprintf(fout,"%s     ",Memory[0][i]);
				fprintf(fout,"\n\n");
				k=0;
				for (int i=1;i<17;i++)
				{
					for (int j=0;j<17;j++)
					{
						if (j==0)
						{
							fprintf(fout,"%s     ",Memory[i][j]);
							continue;
						}
						if (strcmp(Mem.Memory[PageID][k],""))
							fprintf(fout,"%s    ",toHex(Mem.Memory[PageID][k]).c_str());
						else
							fprintf(fout,"      ");
						k++;
					}
					fprintf(fout,"\n");
				}
				fprintf(fout,"\n_______________________________________________________________________\n\n");
			}
			return ;
		}
		void RegisterValues(MemoryIO & Mem , RegisterFile & RG, ProgramCounter & PC,Accumulator & AC,OperandRegister & Op, Stack & St)
		{
			if (COUT)// Console Output if it is selected
			{
				fprintf(stdout,"\n\n\t\t Value of Registers Initially \n");
				fprintf(stdout,"__________________________________________________________________________________________________________________\n\n");
				char pr[10];pr[0]=0;
				int kk=0;
				fprintf(stdout,"\t\tRegister ID\n\n  \t00\t01\t10\t11\n\n");
				for (int i=0;i<3;i++)
				{
					if (i==0)
						fprintf(stdout,"00");
					else if(i==1)
						fprintf(stdout,"01");
					else if(i==2)
						fprintf(stdout,"10");
					for (int j=0;j<4;j++)
					{
						sprintf(pr,"r%d",kk++);
						string ff=pr;
						fprintf(stdout,"\t%s",toHexS(RG.value_of_register[RG.Registers[ff]]).c_str());
					}
					fprintf(stdout,"\n\n");
				}
				fprintf(stdout,"  \tPC\tSP\tAR\tOR\n\n");
		fprintf(stdout,"  \t%s\t%s\t%s\t%s\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());
				fprintf(stdout,"\n_______________________________________________________________________\n\n");
			}
			if (FOUT)// File Output if it is selected
			{
				fprintf(fout,"\n\n\t\t Value of Registers Initially \n");
				fprintf(fout,"__________________________________________________________________________________________________________________\n\n");
				char pr[10];pr[0]=0;
				int kk=0;
				fprintf(fout,"\t\tRegister ID\n\n  \t00\t01\t10\t11\n\n");
				for (int i=0;i<3;i++)
				{
					if (i==0)
						fprintf(fout,"00");
					else if(i==1)
						fprintf(fout,"01");
					else if(i==2)
						fprintf(fout,"10");
					for (int j=0;j<4;j++)
					{
						sprintf(pr,"r%d",kk++);
						string ff=pr;
				//		fprintf(fout,"\t",toHex(RG.value_of_register[RG.Registers[ff]].c_str()).c_str());
					}
					fprintf(fout,"\n\n");
				}
				fprintf(fout,"  \tPC\tSP\tAR\tOR\n\n");
		fprintf(fout,"  \t%s\t%s\t%s\t%s\n",toHex(PC.Curr_Value().c_str()).c_str(),toHex(St.Curr_Value().c_str()).c_str(),toHex(AC.Curr_Value().c_str()).c_str(),toHex(Op.Curr_Value().c_str()).c_str());
				fprintf(fout,"\n_______________________________________________________________________\n\n");
			}
			return ;
		}
};
