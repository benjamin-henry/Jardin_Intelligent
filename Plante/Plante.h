#ifndef PLANTE_H
#define PLANTE_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "WATER_PUMP.h"
#include "SEN_13322.h"

class PLANTE
{
	public:
		PLANTE(void);
		PLANTE(int sensor_pin, int sensor_type, int pump_pin);
		~PLANTE(void);

		void set_sensor_threshold(int thresh);
		int get_sensor_threshold(void);
		
		void set_sensor_tempo(int tempo);
		int get_sensor_tempo(void);

		void set_pump_val(int val);
		int get_pump_val(void);

		void set_pump_tempo(int tempo);
		int get_pump_tempo(void);

		void RUN(void);
		void tick(void);

	protected:
		SEN_13322 _sensor;
		WATERPUMP _pump;
};


#endif
