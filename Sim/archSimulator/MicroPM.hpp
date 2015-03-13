/*	
	Microprogram Memory
 */	
class MicroPM
{
	public:

/*	This is the map which will store the instructions stored at the address specified in the 
	above map. Every instruction will have a bit sequence according to it . The bit string will
	be stored as a string of characters and each instruction will have 40 bits ALWAYS. Data
	movement and gate selections will be based on these bit sequences . 
*/
		map<int  , string > Addr_MS;

		string Fetch(int address)
		{
			return Addr_MS[address];
		}
		void Operation(string inst)
		{
			return ;
		}
};
