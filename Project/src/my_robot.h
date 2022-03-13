#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#include "enviro.h"
#include <string>
#include <math.h>

namespace
{

    using namespace enviro;
    using namespace std;

    class MovingForward : public State, public AgentInterface {
        public:
            void entry(const Event &e) {}
            void during()
            {
                track_velocity(10, 0);
                if (sensor_value(0) < 40)
                {
                    emit(Event(tick_name));
                }
            }
            void exit(const Event &e) {}
            void set_tick_name(std::string s) { tick_name = s; }
            std::string tick_name;
    };

    class Rotating : public State, public AgentInterface {
        public:
            void entry(const Event &e) { 
                 if(sensor_value(1) < sensor_value(2)) {
                     rate = -3.14;
                     return;
                 }
                 else {
                     rate = 3.14;
                     return;
                 }
            }
            void during()
            {
                track_velocity(0, rate);
                if (sensor_value(0) > 140) {
                    emit(Event(tick_name));
                }
                // if (sensor_value(0) > 140 && sensor_value(1) >200)
                // {
                //     cout<<"from 39 line:"<< sensor_value(0)<<", "<<sensor_value(1)<<endl;
                //     emit(Event(tick_name));
                // }
                // if (sensor_value(0) > 170 && sensor_value(2) >170)
                // {
                //     cout<<"from 44 line:"<< sensor_value(0)<<", "<<sensor_value(2)<<endl;
                //     emit(Event(tick_name));
                // }
                // if (sensor_value(1) > 170 && sensor_value(2) >170)
                // {
                //     cout<<"from 49 line:"<< sensor_value(1)<<", "<<sensor_value(2)<<endl;
                //     emit(Event(tick_name));
                // }
            }
            void exit(const Event &e) {}
            double rate;
            void set_tick_name(std::string s) { tick_name = s; }
            std::string tick_name;
    };

    class MyRobotController : public StateMachine, public AgentInterface {

        public:
        MovingForward moving_forward;
        Rotating rotating;
        std::string tick_name;

        MyRobotController() : StateMachine() {


            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand() % 1000); // use an agent specific generated
                                                                    // event name in case there are
                                                                    // multiple instances of this class
            add_transition(tick_name, moving_forward, rotating);
            add_transition(tick_name, rotating, moving_forward);
            moving_forward.set_tick_name(tick_name);
            rotating.set_tick_name(tick_name);

        
        }

    };

    class MyRobot : public Agent {
        public:
        MyRobot(json spec, World& world) : Agent(spec, world) {
            add_process(c);
        }
        private:
        MyRobotController c;
    };

    DECLARE_INTERFACE(MyRobot)

}

#endif