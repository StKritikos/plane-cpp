#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class String;
class Employee;


class Object {                              
	
	private:

		int id;

	public:

		Object();
		Object(Object& old);           
virtual ~Object();
		
		int get_id();
		
virtual bool equal(Object& check);
virtual bool identical(Object* check);
virtual String* toString();
virtual Object* clone() = 0;
};




class String : public Object {
	
	private:
	
		string text;
	
	public:
    
	    String(string s);
		String(String& old);
		~String();
		
		string get_text();
		
		bool equal(Object& check);
		String* toString();
		Object* clone();
		
		int length();
		void clear();
		void concat(String& s);
		char at(int position);
		void updateAt(int position , char c);
		void print();
};




class PlaneComponent : public Object {
	
	private:
	
		String description;
		int readiness;  //starts as a 0. +1 everytime an Employee completes his work there
						//based on its value we can check if a component is ready
	public:
	
		PlaneComponent(String& s);
		PlaneComponent(PlaneComponent& pc);
virtual ~PlaneComponent();
		
		String get_description();
		
		bool equal(Object& check);
		String* toString();
		
virtual int ready_check() = 0;
virtual void process(Employee& e) = 0;

		int get_readiness();	//returns 'readiness'
		void add_readiness();	//readiness +1 when an Employee does work there
};




class PassengerCompartment : public PlaneComponent {     
	
	private:
		
		PassengerCompartment* inside;
	
	public:
		
		PassengerCompartment(String& s , int chance);
		PassengerCompartment(PassengerCompartment& pc);
		~PassengerCompartment();
		
		PassengerCompartment* get_inside();
		
		int ready_check();
		void process(Employee& e);
		
		bool equal(Object& check);
		String* toString();
		Object* clone();
};




class PrivateCompartment : public PlaneComponent {         
	
	public:
		
		PrivateCompartment(String& s);
		PrivateCompartment(PrivateCompartment& pc);
virtual ~PrivateCompartment(); 
				
		int ready_check();
		void process(Employee& e);
	
		String* toString();
		Object* clone();
};




class EquipmentCompartment : public PrivateCompartment {  
	
	public:
	
		EquipmentCompartment(String& s);
		EquipmentCompartment(EquipmentCompartment& ec);
		~EquipmentCompartment();
		
		int ready_check();
		void process(Employee& e);
		
		String* toString();
		Object* clone();
};




class CargoBay : public PrivateCompartment {

	private:

		EquipmentCompartment* inside;

	public:

		CargoBay(String& s);
		CargoBay(CargoBay& cb);
		~CargoBay();
		
		EquipmentCompartment* get_inside();
		
		int ready_check();
		void process(Employee& e);
		
		bool equal(Object& check);
		String* toString();
		Object* clone();
	};




class Plane : public Object {
	
	private:
	
		String description;
		String title;
		int capacity;
		
		CargoBay* cargo_b;
		EquipmentCompartment* equip_c[3];
		PassengerCompartment** passenger_c;  //points to an array of pointers. size depends on 'capacity'
	
	public:
		
		Plane(String& s , String& t , int c);
		Plane(Plane& plane);
		~Plane();
		
		String get_description();
		String get_title();
		int get_capacity();
		CargoBay* get_cargo_b();
		EquipmentCompartment** get_equip_c();
		PassengerCompartment** get_passenger_c();
		
		int ready_check();
		void process(Employee& e);
	
		bool equal(Object& check);
		String* toString();
		Object* clone();
		
		int get_num_of_compartments();	//calculates the number of passenger compartments needed
};									    // in the plane base on the randomized passenger capacity




class Employee : public Object {

	private:

		String name;

	public:

		Employee(String& s);
		Employee(Employee& old);
virtual ~Employee();
		
		String get_name();
		
		String* toString();
		bool equal(Object& check);
		
virtual void workOn(Plane& plane) = 0;
virtual void workOn(PassengerCompartment& pc) = 0;
virtual void workOn(EquipmentCompartment& ec) = 0;
virtual void workOn(CargoBay& cb) = 0;
virtual void report() = 0;
};




class SecurityEmployee : public Employee { 

	public:

		SecurityEmployee(String& s);
		SecurityEmployee(SecurityEmployee& se);
		~SecurityEmployee();
		
		String* toString();
		Object* clone();
		
		void workOn(Plane& plane);
		void workOn(PassengerCompartment& pc);
		void workOn(EquipmentCompartment& ec);
		void workOn(CargoBay& cb);
		void report();
};




class MaintenanceEmployee : public Employee {
	
	public:
	
		MaintenanceEmployee(String& s);
		MaintenanceEmployee(MaintenanceEmployee& me);
		~MaintenanceEmployee();
		
		String* toString();
		Object* clone();
		
		void workOn(Plane& plane);
		void workOn(PassengerCompartment& pc);
		void workOn(EquipmentCompartment& ec);
		void workOn(CargoBay& cb);
		void report();
};




class CleaningEmployee : public Employee {   

	public:

		CleaningEmployee(String& s);
		CleaningEmployee(CleaningEmployee& ce);
		~CleaningEmployee();
		
		String* toString();
		Object* clone();
		
		void workOn(Plane& plane);
		void workOn(PassengerCompartment& pc);
		void workOn(EquipmentCompartment& ec);
		void workOn(CargoBay& cb);
		void report();
};
