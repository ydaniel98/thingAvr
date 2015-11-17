/* NOT USED 

#ifndef PortProtocol_h
#define PortProtocol_h

class PortProtocol {
public:

	uint8_t bits;						// Bits of port (How many pins on the port)

	virtual unsigned int read();	// Reads the value on the port
	virtual bool readAll();			// Returns true if all pins are high

	virtual void set(uint8_t s);	// Sets a value on the port
	virtual void clear();			
	virtual void overflow();		

	virtual void mode(bool m);		// Sets the mode off all the pins the port
};

#endif

*/