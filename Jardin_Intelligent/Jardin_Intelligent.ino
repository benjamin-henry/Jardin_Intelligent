#include <TimerOne.h>
#include <Plante.h>

int led = LED_BUILTIN;
bool ledOn = 0;

void Toggle(int pin, bool *flagPin) // faire pulser la led du Méga chaque seconde pour être sûr qu'on est pas bloqué dans le programme
{
  *flagPin = !*flagPin;
  digitalWrite(pin, *flagPin);
}

bool TMR0_flagOn = 0;
bool TMR0_flag100Hz = 0;
bool TMR0_flag50Hz = 0;
bool TMR0_flag10Hz = 0;
bool TMR0_flag2Hz = 0;
bool TMR0_flag1Hz = 0;
int  TMR0_cnt100Hz = 9;
int  TMR0_cnt50Hz = 1;
int  TMR0_cnt10Hz = 4;
int  TMR0_cnt2Hz = 4;
int  TMR0_cnt1Hz = 1;

void HardwareCallback(void)
{
  TMR0_flagOn = 1;
  if (!TMR0_cnt100Hz)
  {
    TMR0_cnt100Hz = 9;
    TMR0_flag100Hz = 1;
    if (!TMR0_cnt50Hz)
    {
      TMR0_cnt50Hz = 1;
      TMR0_flag50Hz = 1;
      if (!TMR0_cnt10Hz)
      {
        TMR0_cnt10Hz = 4;
        TMR0_flag10Hz = 1;
        if (!TMR0_cnt2Hz)
        {
          TMR0_cnt2Hz = 4;
          TMR0_flag2Hz = 1;
          if (!TMR0_cnt1Hz)
          {
            TMR0_cnt1Hz = 1;
            TMR0_flag1Hz = 1;
          } else(TMR0_cnt1Hz--);
        } else(TMR0_cnt2Hz--);
      } else(TMR0_cnt10Hz--);
    } else(TMR0_cnt50Hz--);
  } else(TMR0_cnt100Hz--);
}

PLANTE choux;
int choux_sensor_pin = 0; //A0
int choux_pump_pin = 6; //PWM sur digital_Pins 6

PLANTE tomates;
int tomates_sensor_pin = 1; //A1
int tomates_pump_pin = 9; //PWM sur digital_Pins 9


void setup()
{
  choux = PLANTE(choux_sensor_pin, choux_pump_pin);
  choux.set_sensor_threshold(100); // si valeur lue < threshold alors activer pompe
  choux.set_sensor_tempo(300); //déclenche une mesure toutes les 300 secondes (5 minutes)
  choux.set_pump_tempo(10); // la pompe restera active pendant 10 secondes si le capteur indique un manque d'humidité

  tomates = PLANTE(tomates_sensor_pin, tomates_pump_pin);
  tomates.set_sensor_threshold(160); // si valeur lue < threshold alors activer pompe
  tomates.set_sensor_tempo(300); //déclenche une mesure toutes les 300 secondes (5 minutes)
  tomates.set_pump_tempo(20); // la pompe restera active pendant 20 secondes si le capteur indique un manque d'humidité

  Timer1.initialize(1000); // période en microsecondes, donc 1 milliseconde ici
  Timer1.attachInterrupt(HardwareCallback); // à chaque milliseconde écoulée, on déclenche la routine "HardwareCallback" qui sert à cadencer de façon régulière le système, d'où l'utilisation d'un timer

  /*Serial.begin(115200);
    Serial.setTimeout(5);*/
}

void loop()
{
  if (TMR0_flagOn) //tâche 1kHz
  {
    TMR0_flagOn = 0;
  }

  if (TMR0_flag100Hz) //tâche 100Hz
  {
    TMR0_flag100Hz = 0;
  }

  if (TMR0_flag50Hz) //tâche 50Hz
  {
    TMR0_flag50Hz = 0;
  }

  if (TMR0_flag10Hz) //tâche 10Hz
  {
    TMR0_flag10Hz = 0;
    if (ledOn)
    {
      Toggle(led, &ledOn);
    }
  }

  if (TMR0_flag2Hz) //tâche 2Hz
  {
    TMR0_flag2Hz = 0;
  }

  if (TMR0_flag1Hz) //tâche 1Hz
  {
    TMR0_flag1Hz = 0;
    choux.tick(); //actualiser les valeurs à chaque seconde
    tomates.tick();
    Toggle(led, &ledOn);
  }
}
