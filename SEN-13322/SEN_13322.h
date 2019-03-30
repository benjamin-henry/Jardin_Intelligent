#ifndef SEN_13322_H
#define SEN_13322_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class SEN_13322
{
	public:
		SEN_13322(void);
		SEN_13322(int pin);
		~SEN_13322(void);

		void read_data(void);
		int get_data(void);
		int read_n_get_data(void);

		void set_threshold(int thresh);
		int get_threshold(void);

		void set_tempo(int tempo);
		int get_current_tempo(void);

		void tick(void);

		bool is_ready(void);
		void set_ready_flag(bool state);

	protected:
		int _pin;
		int _data;
		int _threshold;
		int _tempo;
		int _parametre_tempo;

		bool _ready;
		
};

#endif