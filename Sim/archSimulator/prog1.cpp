
#include "Processor.hpp"

#include "Databus.hpp"
#include "Stack.hpp"
#include "ProgramCounter.hpp"
#include "OperandRegister.hpp"
#include "FlagRegister.hpp"
#include "ALU.hpp"
#include "Accumulator.hpp"
#include "Decoder.hpp"
#include "MemoryAR.hpp"
#include "MemoryIO.hpp"
#include "MicroPM.hpp"
#include "MicroSequencer.hpp"
#include "RegisterFile.hpp"
#include "IORegister.hpp"
#include "Make_operation.hpp"
#include "Scan_init.hpp"
#include "Scan_input.hpp"
#include "Display.hpp"

void *fun(void *n)
{
  struct timespec T1 , T2;
  T1.tv_sec =0;
  T1.tv_nsec = 100000000;
  while (1)
    {
      FLAG = '1';
      nanosleep(&T1,&T2);
      FLAG = '0' ;
      nanosleep(&T1,&T2);
    }
  return NULL;
}

unsigned int cycle = 0;

//	Instances of all the modules

Databus DB;

MemoryAR MR;

Decoder DC;

Accumulator AC;

RegisterFile RG;

MemoryIO Mem;

Stack SP;

FlagRegister FL;

IORegister IOR;

MicroPM MPM;

MicroSequencer MS;

OperandRegister OP;

ALU ALU1;

ProgramCounter PC;

Display Disp ;

int clocks = 0;

int main(int argc , char *argv[])
{

  //	Setting the Flag lookup table /*   May have to take this from user ..... check later */
  flag_lookup["u"]	="000";
  flag_lookup["z"]	="001";
  flag_lookup["nz"]	="010";
  flag_lookup["p"]	="011";
  flag_lookup["m"]	="100";
  flag_lookup["c"]	="101";
  flag_lookup["nc"]	="110";
  flag_lookup["op"]	="111";
  //	Flag lookup table completed

  //	Feeding the first three locations of MicroProgram Memory 	 /*HAS TO BE USER FED */
  //	            00000000001111111111222222222233333333334
  //	            01234567890123456789012345678901234567890
  MPM.Addr_MS[0] = "00000000000000000000000000000010010000000";
  MPM.Addr_MS[1] = "00000000000000000000000001000001000110000";
  MPM.Addr_MS[2] = "00000000000000000000000100000000000000000";

  //	Scanning of User's instruction set is done by a different module

  bool ret = Scan_init(MPM,ALU1,RG,Mem);
  if (ret == false  )
    {
      cout << "\nProblem in scanning the design file. Please correct the file and try again\n";
      return -1 ;// Problem in scanning
    }

  //	Scanning of User's input program file is done by a different module
  char ch = 'n';

  if (errno)
    {
      perror ("Pre-execution error ");
      return -1;
    }

  while ( TRUE )
    {
      MS.clear();
      labels.clear();
      label_lookup.clear();
      breaks.clear();
      ret = Scan_input(Mem,ALU1,RG);
      if (ret == false)
	{
	  cout << "\nProblem with the user program file. Please correct the file and try again.\n"; 
	  return -1 ;
	}

      //	 NEW ADDED  -   Date 16th Nov 2009
      //	 Scaning a memory input file from the user
      if ( false == Mem.FillMemory())
	{
	  return -1;
	}

      //	Initializing Modules
      PC.Init("00000000");   /* Change */
      SP.Init();
      //	Modules initialized

      if (errno)
	{
	  perror ("Input file error  ");
	  return -1;
	}

      //	Initializing Databus
      strcpy(DB.DATA,"");
      DB.FLAG = FREE;

      //	Initial Memory Map
      cout << "\tDo you want to print the initial contents of Memory and Registers ? [y/n] : ";
      cin >> ch;
      if (ch == 'y')
	Disp.InitialMap(Mem,RG,PC,AC,OP,SP);

      //	Execution of Program
      bool val = EXECUTE(0);

      if (errno)
	{
	  perror("Error in execution ");
	  break;
	}

      //	Final Memory Map
      cout << "\tDo you want to print the final contents of Memory and Registers [y/n]?  : ";
      cin >> ch;
      if (ch == 'y')
	Disp.FinalMap(Mem,RG,PC,AC,OP,SP);
		
      cout << "\n\tTotal number of clock cycles taken to run the program  :\t"<<clocks<<"\n\n";
		
      cout << "\n\tDo you want to run another program [y/n] ? :";
      cin >> ch;
      if (ch !='y')
	break;
      labels.clear();
      clocks = 0;
      label_lookup.clear();
      breaks.clear();
    }
  return 0;
}

bool EXECUTE(int ret_inst)
{
  cout << "\n\t At any time during the exection of the program, the following keywords can be used\n";
  cout << "\t'rc' : To change   the current register contents\n";
  cout << "\t'rd' : To display  the current register contents\n";
  cout << "\t'md' : To display  the current memory and register contents\n";
  cout << "\t'mc' : To change   the current execution mode\n";
  cout << "\t'rc' : To change   the current break point state \n";
  cout << "\t'fp' : To print all the current flag contents\n";
  string tmp = "" , mode = "";
  char input[100];input[0]=0;
  cout << "\n  Set the Execution Mode by pressing one of the following :\n";
  cout << "\t'm' : execute Microinstruction by Microinstruction\n";
  cout << "\t'i' : execute Instruction by Instruction\n";
  cout << "\t'p' : execute entire program (default mode)\n";
  strcpy(input,"p");
  while (true)
    {
      cout << "\tExecution Mode : ";
      getchar();
      scanf("%[^\n]",input);
      mode = input ;
      if (mode != "p" && mode !="m" && mode!="i")
	{
	  cout << "Invalid Entry . Press (m/i/p) .\n";
	  continue ;
	}
      break;
    }
  cout << "\tPress 'bp' to set additional break-points besides (brk) in the program  : ";
  getchar();
  scanf("%[^\n]",input);
  tmp = input ;
  bool be = false ;
  if (tmp == "bp")
    {
      if (SetBreakPoints() == false )
	return false ;
    }
  cout << "\tPress be/bd to enable/disable all break-points (default disable)\n";
  string Microinstruction="";
  int count_inst = -1; // Counter to count the number of instructions executed
  cout << "\n\tProgram Execution Begins .......\n\n";
  while ( TRUE )
    {
      /*
	This is the main loop. All modules are executed in this order. NOTICE
      */
      ret_inst = MS.Sequencer(ret_inst , DC , FL);
      if (ret_inst == 0)
	count_inst++;
      Microinstruction = MPM.Fetch(ret_inst);
      PC.Operation(Microinstruction , DB);		//Program Counter Module
      MR.Operation(Microinstruction,DB);		//Memory Address Module
      Mem.Operation(Microinstruction,DB,MR);		//Memory Address Module
      DC.Operation(Microinstruction,DB);		//Decoder Module
      MS.Operation(Microinstruction,DC);		//MicroSequencer Module
      IOR.Operation(Microinstruction,DB,RG,FL);	//Instr. Oper. Register Module
      RG.Operation(Microinstruction,DB,PC,SP,AC,OP,ALU1);		//Register File Module
      OP.Operation(Microinstruction,DB);		//Operand Module
      AC.S_Operation(Microinstruction,DB);		// Special Accumulator Operation (only to EAR)
      ALU1.Operation(Microinstruction,DB,OP,FL);	//ALU Module
      AC.Operation(Microinstruction,DB,ALU1);		//Accumulator Module
      SP.Operation(Microinstruction,DB);		//Stack Module
      MR.Operation(Microinstruction,DB);		//Memory Address Module
      Mem.Operation(Microinstruction,DB,MR);		//Memory Address Module
      RG.Operation(Microinstruction,DB,PC,SP,AC,OP,ALU1);		//Register File Module
      OP.Operation(Microinstruction,DB);		//Operand Module
      PC.S_Operation(Microinstruction, DB);		// Special PC Operation
      //		FL.Operation(Microinstruction);			//Flag Register Module (only to LPC)
      if (Microinstruction == "000000000000000000001000000000000000000000")
	break;
      clocks++;
      if (Print(mode,count_inst,ret_inst,Microinstruction , be) ==  false)
	return false;
    }
  return true;
}

//return value : true ==>> Scan the character  or false ==>> do not scan character

bool Print(string & mode , int count_inst , int ret_inst, string Inst , bool & be)
{
  string tmp="";
  char input[100];input[0]=0;
  strcpy(input,mode.c_str());
  if (mode == "m")
    {
      cout << "\tLast microinstruction : "<< Inst <<"\n";
      Disp.AllRegisterValues(RG, PC, SP, AC, OP);
      SelectOperations(mode,be);
    }
  else if (ret_inst == 0 && mode == "i")
    {
      cout << "Last Instruction : " << Mem.Memory[PageID][count_inst]<<"\n";
      Disp.AllRegisterValues(RG, PC, SP, AC, OP);
      SelectOperations(mode,be);
    }
  else if (be == true && breaks.find(count_inst)!=breaks.end())
    {
      breaks.erase(count_inst);
      cout << "Break-point at address : "<< toHexS(ToStr(count_inst))<<"\n";
      SelectOperations(mode,be);
    }
  return true;
}

void SelectOperations(string &mode, bool &be)
{
  char input[100];input[0]=0;
  string tmp = "";
  while (1)
    {
      printf("                                   ");
      getchar();
      scanf("%[^\n]",input);   // input a keyword eg. 'rc' for changing register etc.
      tmp = input;
      if (tmp == "rc")  // Change register values 
	{
	  ChangeRegisterValue();
	}
      if (tmp == "rd" || tmp == "r")  // Display Register and state values
	{
	  Disp.AllRegisterValues(RG,PC,SP,AC,OP); // Print all register values PC,SP,AR,OR including
	}
      if (tmp == "md")  // Display Register and  memory state values
	{
	  // Disp.FinalMap(DM,RG,PC,AC,OP,SP);// Print all register and memory values PC,SP,AR,OR including
	  Disp.MemoryMap(Mem, RG);
	  Disp.AllRegisterValues(RG, PC, SP, AC, OP);
	}
      if (tmp == "mc") // Change execution mode
	{
	  ChangeExecutionModeValue(mode);
	}
      if (tmp == "fp")  // Print All Flags
	{
	  PrintFlagValues();
	}
      if (tmp == "bc") // Change break point state
	{
	  ChangeBreakPointState(be);
	}
      if (strlen(input) == 0)
	break;
      input[0]=0;
    }
}

void ChangeExecutionModeValue(string &mode)
{
  cout << "\tEnter the new execution mode (m/i/p) :";
  char input[100];input[0]=0;
  string tmp;
  getchar();
  scanf("%[^\n]",input);
  tmp = input;
  if (tmp == "m" || tmp == "p" || tmp == "i")
    mode = input ;
}

void PrintFlagValues()
{
  FL.PrintAllFlags();
}

void ChangeBreakPointState(bool &be)
{
  char input[100];input[0]=0;
  string tmp="";
  cout << " Enter 'be' to enable and 'bd' to disable breakpoints : ";
  scanf("%[^\n]",input);
  tmp = input;
  if (tmp == "be")
    be = true ;
  if (tmp == "bd")
    be = false ;
}

void ChangeRegisterValue()
{
  cout << "\tEnter 'c' to skip this mode and continue \n";
  while ( true )
    {
      string t1="",t2="";
      cout << "Register (r0-r11) : ";
      cin >> t1;
      if (t1 == "c")
	break ;
      if (RG.Registers.find(t1) == RG.Registers.end())
	{
	  cout << "\tError in register value . Not changing value . ";
	}
      else
	{
	  cout << "New Contents (in Hex) : ";
	  cin >> t2;
	  if (CheckHex(t2) == false)
	    {
	      cout << "Error in value . Did not change .\n";
	    }
	  else
	    {
	      RG.value_of_register[RG.Registers[t1]] = HexToBin(t2);
	    }
	}
    }
}

bool SetBreakPoints()
{
  string tmp ;
  int in,c=0;
  cout << "Enter -1 as address of break-point to quit from this mode\n";
  while ( true )
    {
      cout << "bp"<<c++<<" : ";
      cin >> tmp; // Hex Code 
      if (tmp == "-1")
	break;
      if (CheckHex(tmp) == false )
	{
	  cout << "Invalid Hex value . Quitting . \n";
	  return false ;
	}
      breaks.insert(Value(HexToBin(tmp).c_str()));
    }
  return true ;
}
