//	Scanning of User's Instruction set file is done is this function

bool  Scan_init(MicroPM & MPM , ALU & ALU1 , RegisterFile & RG , MemoryIO & Mem)
{
	FILE *filepointer;
	char designf[100];
//	cout << "\n\tPlease enter the name of the design file : ";
//	cin >> designf;
	// This work is done to embed the design file in the program
	char design_string[10000];
	strcpy(design_string,"ALU
nop	00000000
stop	00000001
adi	00000010
subi	00000011
ani	00000100
ori	00000101
xri	00000110
cmi	00000111
ret	00001
jmpd	11100
jmpr	11101
cd	11110
cr	11111
add	0001
sub	0010
xor	0011
and	0100
or	0101
cmp	0110
movs	0111
movd	1000
movi	1001
store	1010
load	1011
push	1100
pop	1101
END
Micro-Instructions
stop 1

adi 3
EAR LOR
EPC LMR
IPC ERD SAF 0001 LAR RMS
subi 3
EPC LMR
IPC ERD LOR
EAR SAF 0010 LAR RMS
xri 3
EAR LOR
EPC LMR
IPC ERD SAF 0011 LAR RMS
ani 3
EAR LOR
EPC LMR
IPC ERD SAF 0100 LAR RMS
ori 3
EAR LOR
EPC LMR
IPC ERD SAF 0101 LAR RMS
cmi 3
EAR LOR
EPC LMR
IPC ERD SAF 0010 RMS
add 2
ERG LOR
EAR SAF 0001 LAR RMS
sub 2
ERG LOR
EAR SAF 0010 LAR RMS
xor 2
ERG LOR
EAR SAF 0011 LAR RMS
and 2
ERG LOR
EAR SAF 0100 LAR RMS
or 2
ERG LOR
EAR SAF 0101 LAR RMS
cmp 2
ERG LOR
EAR SAF 0010 RMS
movs 2
ERG LOR
SAF 1111 LOR LAR RMS
movd 1
EAR LRG RMS
load 2
ERG LMR
ERD SAF 1111 LOR LAR RMS
store 2
ERG LMR
EAR LWR RMS
push 3
DSP
ESP LMR
ERG LWR RMS
pop 2
ESP LMR
ISP ERD LRG RMS
movi 2
EPC LMR
ERD IPC LRG RMS
jmpd 3
EPC LMR
IPC SFL RMS
ERD LPC RMS
jmpr 2
SFL RMS
EAR LPC RMS
cd 6
EPC LMR
IPC SFL RMS
ERD LOR DSP
ESP LMR
EPC LWR
EOR LPC RMS
cr 5
RMS SFL
DSP
ESP LMR
EPC LWR
EAR LPC RMS
ret 3
RMS SFL
ESP LMR
ISP ERD LPC RMS
END");
	FILE *embed_file = fopen("~/.tmp_file","w");
	fprintf(embed_file,"%s",design_string);
	fclose(embed_file);
	strcpy(designf,"~/.tmp_file");
	filepointer = fopen(designf,"r");
	if (errno)
	{
		perror("Error with the file ");
		return false;
	}
	fclose(filepointer);
	ifstream fin(designf);
	string str1 , str2 , str3;
	fin >> str1;
	if (str1 == "Flags")
	{
		fin >> str1;
		string str2="";
		while (str1 != "END")
		{
			if (flag_lookup.find(str1) == flag_lookup.end())
			{
				cout << "  Invalid flag symbol used :  " << str1 << "\n";
				return false;
			}
			fin >> str2;
			flag_lookup[str1] = str2;
			fin >> str1;
		}
		fin >> str1;
	}
	if (str1 == "ALU")
	{
		fin >> str1;
		while (str1 != "END")
		{
			fin >> str2 ;
			// check if the bit string is valid
			{
				for (int j =0 ; j < str2.length() ; j++)
					if (str2[j]!= '0' && str2[j] != '1')
					{
						cout << "Invalid opcode " << str2 <<" , should be a 0-1 bit string \n";
						return false ;
					}
			}
			inst_len[str1] = str2.length();
			ALU1.SelectBits[str1] = str2;
			fin >> str1;
		}
		fin >> str1;
	}
	if (str1=="Micro-Instructions")
	{
		fin >> str1;
		string str ="", str3;
		int t = 0 , k =0 , l , in;
		while (str1 != "END")
		{
			fin >> in ;
			str3 = ALU1.SelectBits[str1];
			l = str3.length();
			if (k==0)
			{
				for (int i=str3.length()-1;i>=0;i--)
				{
					t = t + (((int)pow(2.0,(l-i-1)*1.0))*(str3[i]-'0'));
				}
				k++;
				t+=3;
			}
			lookup[ALU1.SelectBits[str1]] = t;
			getline(fin,str);
			for (int i=0;i<in;i++)
			{
				getline(fin,str2);
				string inp = "000000000000000000000000000000000000000000" ;
				inp[MFL]='1';
				int i;
				//parsing input line
				l = str2.length();
				{
					// Check for multiple enables
					char str_use[100];
					strncpy(str_use,str2.c_str(),l);str_use[l]=0;
					int count_E = 0, count_e ;
					for ( count_e = 0 ; str_use[count_e] != 0 && count_e < l ;++count_e )
					{
						while (str_use[count_e] == ' ')
							++count_e;
						if (str_use[count_e] == 'E')
						{
							++count_E;
							string ewr="";
							while (str_use[count_e] != ' ' && str_use[count_e] != 0 )
							{
								ewr = ewr + str_use[count_e];
								++count_e;
							}
						}
						else
						{
							while (str_use[count_e] != ' ' && str_use[count_e] != 0)
								++count_e;
						}
					}
					if (count_E > 1)
					{
						cout << " Microinstruction Error:  More than one Enable in a microinstruction : " << str2 << "\n";
						return false;
					}
				}
				for (i=0;i<l;i++)
				{
					while (str2[i]==' ')i++;
					while (str2[i]!=' ' && i < l)
					{
						str+=str2[i++];
					}
					if ( str=="SAF" )
					{
						while (str2[i]==' ')i++;
						string bits="";
						while (str2[i]!=' ' && i < l)
						{
							if (str2[i]!='0' && str2[i] != '1')
							{
								cout << "Invalid value for select bits in " << str2 <<" , should be a 0-1 bit string \n";
								return false ;
							}
							bits+=str2[i++];
						}
						inp[SAF]=bits[0];
						inp[SAF+1]=bits[1];
						inp[SAF+2]=bits[2];
						inp[SAF+3]=bits[3];
					}
					else if (str=="EOR")
						inp[EOR]='1';
					else if (str == "SFL")
						inp[SFL]='1';
					else if (str=="ROR")
						inp[ROR]='1';
					else if (str=="LOR")
						inp[LOR]='1';
					else if (str=="EAR")
						inp[EAR]='1';
					else if (str=="RAR")
						inp[RAR]='1';
					else if (str=="LAR")
						inp[LAR]='1';
					else if (str=="ERG")
						inp[ERG]='1';
					else if (str=="LRG")
						inp[LRG]='1';
					else if (str=="MRG")
						inp[MRG]='1';
					else if (str=="MFL")
						inp[MFL]='1';
					else if (str=="EFL")
						inp[EFL]='1';
					else if (str=="MFE")
						inp[MFE]='1';
					else if (str=="RMS")
						inp[RMS]='1';
					else if (str=="LMS")
						inp[LMS]='1';
					else if (str=="LIR")
						inp[LIR]='1';
					else if (str=="LSP")
						inp[LSP]='1';
					else if (str=="DSP")
						inp[DSP]='1';
					else if (str=="ISP")
						inp[ISP]='1';
					else if (str=="ESP")
						inp[ESP]='1';
					else if (str=="LPC")
						inp[LPC]='1';
					else if (str=="IPC")
						inp[IPC]='1';
					else if (str=="EPC")
						inp[EPC]='1';
					else if (str=="LMR")
						inp[LMR]='1';
					else if (str=="LWR")
						inp[LWR]='1';
					else if (str=="ERD")
						inp[ERD]='1';
	//				else if (str=="LIO")
	//					inp[LIO]='1';
					else if (str != " " && str != "" && str != "\t" && str != "\n"){
						cout << "  Invalid  symbol used :  " << str << "\n";
						return false;
					}
					str="";
				}
				MPM.Addr_MS[t++] = inp;
			}
			fin >> str1;
		}
	}
	fin.close();
	return true ;
}
