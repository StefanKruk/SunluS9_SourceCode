/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * feature/runout.h - Runout sensor support
 */

#include "../sd/cardreader.h"
#include "../module/printcounter.h"
#include "../module/planner.h"
#include "../module/stepper.h" // for block_t
#include "../gcode/queue.h"
#include "../feature/pause.h"

#include "../inc/MarlinConfig.h"
#include "../lcd/extui/dgus/DGUSScreenHandler.h"

#if ENABLED(EXTENSIBLE_UI)
    #include "../lcd/extui/ui_api.h"
#endif

//#define FILAMENT_RUNOUT_SENSOR_DEBUG
#ifndef FILAMENT_RUNOUT_THRESHOLD
    #define FILAMENT_RUNOUT_THRESHOLD 5
#endif

static volatile uint16_t counter_change_all;
// Return a bitmask of runout pin states
void poll_runout_pins();
void event_filament_runout(const uint8_t extruder,uint8_t err_code);
static void poll_runout_pins_enter(){poll_runout_pins();}



template<class RESPONSE_T, class SENSOR_T>
class TFilamentMonitor;
class FilamentSensorEncoder;
class FilamentSensorSwitch;
class RunoutResponseDelayed;
class RunoutResponseDebounced;

/********************************* TEMPLATE SPECIALIZATION *********************************/

typedef TFilamentMonitor<
          TERN(HAS_FILAMENT_RUNOUT_DISTANCE, RunoutResponseDelayed, RunoutResponseDebounced),
          TERN(FILAMENT_MOTION_SENSOR, FilamentSensorEncoder, FilamentSensorSwitch)
        > FilamentMonitor;

extern FilamentMonitor runout;


/*******************************************************************************************/

class FilamentMonitorBase {
  public:
    static bool filament_ran_out;
	static int8_t enabled;
	static volatile  bool test_filament_ran_out;
    #if ENABLED(HOST_ACTION_COMMANDS)
        static bool host_handling;
    #else
        static constexpr bool host_handling = false;
    #endif
};

template<class RESPONSE_T, class SENSOR_T>
class TFilamentMonitor : public FilamentMonitorBase {
  private:
    typedef RESPONSE_T response_t;
    typedef SENSOR_T   sensor_t;
    static  response_t response;
    static  sensor_t   sensor;

  public:
    static inline void setup() {
      sensor.setup();
      reset();
    }

	uint8_t get_has_run_out()	{return sensor.has_run_out();}
	void add_change()	{return sensor.add_change();}

    static inline void reset() {
      filament_ran_out = false;
      response.reset();
	  sensor.reset();
    }

	void setFilamentRunout_enabled(uint8_t en)
	{
		if(((enabled&0x03)==0)&&((en&0x03)!=0))
		{
			attachInterrupt(0,poll_runout_pins_enter,CHANGE);
		}
		enabled=en;
	}

    // Call this method when filament is present,
    // so the response can reset its counter.
    static inline void filament_present(const uint8_t extruder) {
      response.filament_present(extruder);
    }

    #if HAS_FILAMENT_RUNOUT_DISTANCE
        static inline float& runout_distance() { return response.runout_distance_mm; }
        static inline void set_runout_distance(const_float_t mm) { response.runout_distance_mm = mm; }
    #endif

    // Handle a block completion. RunoutResponseDelayed uses this to
    // add up the length of filament moved while the filament is out.
    static inline void block_completed(const block_t * const b) {
      if (enabled!=0) {
        response.block_completed(b);
        sensor.block_completed(b);
      }
    }


    // Give the response a chance to update its counter.
    static inline void run() {
    // ��һ�γ�������֮�󣬻ָ���ӡ�Ͳ��ٽ����������
    // ���˼·�����˻ָ���ӡ֮���ȳ��� FILAMENT_RUNOUT_DISTANCE_MM ���ж��Ƿ����ϣ�����У��ͼ�����ӡ
    // ������ж���䣬Ҫ�ټ�һ���ж�����

      if(enabled!=0 && !filament_ran_out && (printingIsActive() || did_pause_print) ){//|| test_filament_ran_out)
        TERN_(HAS_FILAMENT_RUNOUT_DISTANCE, cli()); // Prevent RunoutResponseDelayed::block_completed from accumulating here
        response.run();
        sensor.run();
        uint8_t runout_flags ;//= sensor.has_run_out();
		if((sensor.has_run_out() & 0x03)!=0)
			runout_flags=0xff;
		else
			runout_flags=0;
        TERN_(HAS_FILAMENT_RUNOUT_DISTANCE, sei());
        #if MULTI_FILAMENT_SENSOR
            #if ENABLED(WATCH_ALL_RUNOUT_SENSORS)
                const bool ran_out = !!runout_flags;  // any sensor triggers
                uint8_t extruder = 0;
                if (ran_out) {
                  uint8_t bitmask = runout_flags;
                  while (!(bitmask & 1)) {
                    bitmask >>= 1;
                    extruder++;
                  }
                }
            #else
                const bool ran_out = TEST(runout_flags, active_extruder);  // suppress non active extruders
                uint8_t extruder = active_extruder;
            #endif
        #else
            const bool ran_out = !!runout_flags;
            uint8_t extruder = active_extruder;
        #endif

        #if ENABLED(FILAMENT_RUNOUT_SENSOR_DEBUG)
            if (runout_flags) {
              SERIAL_ECHOPGM("Runout Sensors: ");
              LOOP_L_N(i, 8) SERIAL_ECHO('0' + TEST(runout_flags, i));
              SERIAL_ECHOPAIR(" -> ", extruder);
              if (ran_out) SERIAL_ECHOPGM(" RUN OUT");
              SERIAL_EOL();
            }
        #endif
		

        if (ran_out) {
			filament_ran_out = true;
          event_filament_runout(extruder,runout_flags);
          planner.synchronize();
		  
        }
		
      }
    }
	
	
};

/*************************** FILAMENT PRESENCE SENSORS ***************************/

class FilamentSensorBase {
  protected:
    /**
     * Called by FilamentSensorSwitch::run when filament is detected.
     * Called by FilamentSensorEncoder::block_completed when motion is detected.
     */
    static inline void filament_present(const uint8_t extruder) {
      runout.filament_present(extruder); // ...which calls response.filament_present(extruder)
    }

  public:
    static inline void setup() {
      #define _INIT_RUNOUT_PIN(P,S,U,D) do{ if (ENABLED(U)) SET_INPUT_PULLUP(P); else if (ENABLED(D)) SET_INPUT_PULLDOWN(P); else SET_INPUT(P); }while(0)
      #define  INIT_RUNOUT_PIN(N) _INIT_RUNOUT_PIN(FIL_RUNOUT##N##_PIN, FIL_RUNOUT##N##_STATE, FIL_RUNOUT##N##_PULLUP, FIL_RUNOUT##N##_PULLDOWN)
      #if NUM_RUNOUT_SENSORS >= 1
          INIT_RUNOUT_PIN(1);
  	    pinMode(FIL_RUNOUT1_PIN,INPUT_PULLUP);
  		attachInterrupt(0,poll_runout_pins_enter,CHANGE);
      #endif
      #if NUM_RUNOUT_SENSORS >= 2
          INIT_RUNOUT_PIN(2);
      #endif
      #if NUM_RUNOUT_SENSORS >= 3
          INIT_RUNOUT_PIN(3);
      #endif
      #if NUM_RUNOUT_SENSORS >= 4
          INIT_RUNOUT_PIN(4);
      #endif
      #if NUM_RUNOUT_SENSORS >= 5
          INIT_RUNOUT_PIN(5);
      #endif
      #if NUM_RUNOUT_SENSORS >= 6
          INIT_RUNOUT_PIN(6);
      #endif
      #if NUM_RUNOUT_SENSORS >= 7
          INIT_RUNOUT_PIN(7);
      #endif
      #if NUM_RUNOUT_SENSORS >= 8
          INIT_RUNOUT_PIN(8);
      #endif
      #undef _INIT_RUNOUT_PIN
      #undef  INIT_RUNOUT_PIN
	  
    }
    // Return a bitmask of runout flag states (1 bits always indicates runout)
    static inline uint8_t poll_runout_states() {
		return 0;
    }
};

#if ENABLED(FILAMENT_MOTION_SENSOR)
  
    /**
     * This sensor uses a magnetic encoder disc and a Hall effect
     * sensor (or a slotted disc and optical sensor). The state
     * will toggle between 0 and 1 on filament movement. It can detect
     * filament runout and stripouts or jams.
     */
    class FilamentSensorEncoder : public FilamentSensorBase {
      private:
        static uint8_t motion_detected;
        static inline uint8_t poll_motion_sensor() {
  		return counter_change;
        }
  
      public:
  	  static volatile int8_t counter_change;
  	  static uint8_t direction_bits;
  	  static uint8_t filament_err_num;
  	  static uint8_t Has_Filament_Err;
        static volatile float runout_mm_countdown[NUM_RUNOUT_SENSORS];
  	  
        static inline uint8_t has_run_out() {
          return Has_Filament_Err;
        }
  	  static void add_change() {
          counter_change++;
        }
        static inline void block_completed(const block_t * const b) {
  		direction_bits=b->direction_bits;
  		
          if (did_pause_print || b->steps.e) { // Allow pause purge move to re-trigger runout state//b->steps.x || b->steps.y || b->steps.z || 
            // Only trigger on extrusion with XYZ movement to allow filament change and retract/recover.
            const uint8_t e = b->extruder;
            const int32_t steps = b->steps.e;
  		
  		  
  		  if(TEST(b->direction_bits, E_AXIS))
  		  {
  			  //do{ MYSERIAL1.println("direction_bits_nor:");  }while(0);
  			  //filament_err_num=0;
  			  
  			  //if(ScreenHandler.back_Fliament_State== false)
  			  //Has_Filament_Err=0;
  		  //counter_change=0;
  			  counter_change=0;
  			  
  		  }
  		  else
  		  {			  	
  			  if(steps<0)	MYSERIAL1.println("steps<0:");
  	          runout_mm_countdown[e] += abs(steps * planner.steps_to_mm[E_AXIS_N(e)]);
  			  if(runout_mm_countdown[e] >= FILAMENT_RUNOUT_DISTANCE_MM )
  			  {			
  			  int8_t tmp=(uint8_t)(runout_mm_countdown[e]/FILAMENT_RUNOUT_DISTANCE_MM);
  			  tmp++;
  				runout_mm_countdown[e]=0;
  			  	if(counter_change == 0 && (runout.enabled & 0x01) )
  			  	{
  					//do{ MYSERIAL1.println("counter_change == >>>>0:"); }while(0);
  					filament_err_num++;
  					counter_change=0;
  					if(filament_err_num>RUNOUT_Filament_CNT||(ScreenHandler.getFilament_Check_Flag()))//DAVID 
  					{
  					    ScreenHandler.setFilament_Check_Flag(false);
  						filament_err_num=0;
  			  			Has_Filament_Err=1;//return 1;//no fialment
  					}
  			  	}else{
  					if(counter_change>tmp*5)
  					{
  						//do{ MYSERIAL1.println("counter_change>tmp*5"); }while(0);
  						filament_err_num=0;
  						Has_Filament_Err=0;
  						//counter_change=0;
  						counter_change=0;
  					}
  					else if((abs(counter_change-tmp)>2)&& (runout.enabled & 0x02) )
  					{
  						//do{ MYSERIAL1.println("counter_change>tmp:"); }while(0);
  						filament_err_num++;
  						//counter_change=0;
  						counter_change=0;
  						if(filament_err_num>=RUNOUT_Jams_CNT /*||(ScreenHandler.getFilament_Check_Flag())*/ )
  						{
  							//ScreenHandler.setFilament_Check_Flag(false);
  							filament_err_num=0;
  							Has_Filament_Err=2;
  						}
  					}
  					else
  					{
  						//do{ MYSERIAL1.println("nor:");  }while(0);
  						filament_err_num=0;
  						Has_Filament_Err=0;
  					//counter_change=0;
  						counter_change=0;
  					}
  			  	}
  
  
  				
  			  }
  
  
  		  }  
          }
  
  	
          // If the sensor wheel has moved since the last call to
          // this method reset the runout counter for the extruder.
          if (TEST(motion_detected, b->extruder))
            filament_present(b->extruder);
          // Clear motion triggers for next block
          motion_detected = 0;
  
  	 
  		if(ScreenHandler.back_Fliament_State== true)
  			ScreenHandler.back_Fliament_State=false;
  		
        }
  	  
  	 // static void clean_counter_change(){counter_change=0;}
  	  void reset() {
  		 filament_err_num=0;
  				//counter_change=0;
  				counter_change=0;
  		 runout_mm_countdown[0]=0;
  		 Has_Filament_Err=0;
  		//do{ MYSERIAL1.print("counter_change="); MYSERIAL1.println(counter_change); }while(0);
  		 
        }
        static inline uint8_t run() {return counter_change;}//{ return poll_motion_sensor(); }
    };
  
#else
  
    /**
     * This is a simple endstop switch in the path of the filament.
     * It can detect filament runout, but not stripouts or jams.
     */
    class FilamentSensorSwitch : public FilamentSensorBase {
      private:
        static inline bool poll_runout_state(const uint8_t extruder) {
          const uint8_t runout_states = poll_runout_states();
          #if MULTI_FILAMENT_SENSOR
              if ( !TERN0(DUAL_X_CARRIAGE, idex_is_duplicating())
                && !TERN0(MULTI_NOZZLE_DUPLICATION, extruder_duplication_enabled)
              ) return TEST(runout_states, extruder); // A specific extruder ran out
          #else
              UNUSED(extruder);
          #endif
          return !!runout_states;                   // Any extruder ran out
        }
  
      public:
        static inline void block_completed(const block_t * const) {}
        static inline void run() {
          LOOP_L_N(s, NUM_RUNOUT_SENSORS) {
            const bool out = poll_runout_state(s);
            if (!out) filament_present(s);
            #if ENABLED(FILAMENT_RUNOUT_SENSOR_DEBUG)
                static uint8_t was_out; // = 0
                if (out != TEST(was_out, s)) {
                  TBI(was_out, s);
                  SERIAL_ECHOLNPAIR_P(PSTR("Filament Sensor "), '0' + s, out ? PSTR(" OUT") : PSTR(" IN"));
                }
            #endif
          }
        }
    };
  
  
#endif // !FILAMENT_MOTION_SENSOR

/********************************* RESPONSE TYPE *********************************/

#if HAS_FILAMENT_RUNOUT_DISTANCE
  
    // RunoutResponseDelayed triggers a runout event only if the length
    // of filament specified by FILAMENT_RUNOUT_DISTANCE_MM has been fed
    // during a runout condition.
    class RunoutResponseDelayed {
      private:
       // static volatile float runout_mm_countdown[NUM_RUNOUT_SENSORS];
  
      public:
        static float runout_distance_mm;
  
        static inline void reset() {
          LOOP_L_N(i, NUM_RUNOUT_SENSORS) filament_present(i);
        }
  
        static inline void run() {
          #if ENABLED(FILAMENT_RUNOUT_SENSOR_DEBUG)
              static millis_t t = 0;
              const millis_t ms = millis();
              if (ELAPSED(ms, t)) {
                t = millis() + 1000UL;
              }
          #endif
  		
        }
  
        static inline uint8_t has_run_out() {
          uint8_t runout_flags = 0;
         // LOOP_L_N(i, NUM_RUNOUT_SENSORS) if (runout_mm_countdown[i] < 0) SBI(runout_flags, i);
          return runout_flags;
        }
  
        static inline void filament_present(const uint8_t extruder) {
          //runout_mm_countdown[extruder] = runout_distance_mm;
        }
  
        static inline void block_completed(const block_t * const b) {//��Ҫ�������ȡ������
          if (b->steps.x || b->steps.y || b->steps.z || did_pause_print) { // Allow pause purge move to re-trigger runout state
            // Only trigger on extrusion with XYZ movement to allow filament change and retract/recover.
            const uint8_t e = b->extruder;
            const int32_t steps = b->steps.e;
            //runout_mm_countdown[e] -= (TEST(b->direction_bits, E_AXIS) ? -steps : steps) * planner.steps_to_mm[E_AXIS_N(e)];
          }
        }
    };
  
#else // !HAS_FILAMENT_RUNOUT_DISTANCE
  
    // RunoutResponseDebounced triggers a runout event after a runout
    // condition has been detected runout_threshold times in a row.
  
    class RunoutResponseDebounced {
      private:
        static constexpr int8_t runout_threshold = FILAMENT_RUNOUT_THRESHOLD;
        static int8_t runout_count[NUM_RUNOUT_SENSORS];
  
      public:
        static inline void reset() {
          LOOP_L_N(i, NUM_RUNOUT_SENSORS) filament_present(i);
        }
  
        static inline void run() {
          LOOP_L_N(i, NUM_RUNOUT_SENSORS) if (runout_count[i] >= 0) runout_count[i]--;
        }
  
        static inline uint8_t has_run_out() {
          uint8_t runout_flags = 0;
          LOOP_L_N(i, NUM_RUNOUT_SENSORS) if (runout_count[i] < 0) SBI(runout_flags, i);
          return runout_flags;
        }
  
        static inline void block_completed(const block_t * const) { }
  
        static inline void filament_present(const uint8_t extruder) {
          runout_count[extruder] = runout_threshold;
        }
    };
  
#endif // !HAS_FILAMENT_RUNOUT_DISTANCE
