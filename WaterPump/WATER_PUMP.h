#ifndef WATERPUMP_H
#define WATERPUMP_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class WATERPUMP
{
	public:
		WATERPUMP(void);
		WATERPUMP(int pin);
		~WATERPUMP(void);

		void PUMP_ON(void);
		void PUMP_OFF(void);
		bool is_pump_on(void);

		void set_val(int val);
		int get_val(void);

		void set_tempo(int tempo);
		int get_current_tempo(void);

		void tick(void);

	protected:
		int _pin;
		bool _on;
		int _val;
		int _parametre_tempo;
		int _tempo;
};


#endif