#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "planeClasses.h"
using namespace std;

extern int additive_object_id;


void clone_encrypt_and_print(Object& plane) {
				
	Object* copied_plane = plane.clone();
	
	if ( (plane.equal(*copied_plane) == 1) && (plane.identical(copied_plane) == 1) )   //checking if plane and copied_plane are equal/identical
		cout << "Plane and copied plane are both equal and identical" << endl;
	else if ( (plane.equal(*copied_plane) == 1) && (plane.identical(copied_plane) == 0) )
		cout << "Plane and copied plane are equal but not identical" << endl;
	else
		cout << "Plane and copied plane are neither equal nor identical" << endl;
		
	String* string_of_plane = plane.toString();
	String* string_of_copied_plane = copied_plane -> toString();
	
	int num_of_positions = (rand() % 10) + 1;  //1-10 positions to change string_of_copied_plane
	int random_position;
	for(int i=0 ; i < num_of_positions ; i++)
	{
		random_position = rand() % (string_of_copied_plane -> length()) + 1;   //a random position of the string changes each time 
		string_of_copied_plane -> updateAt(random_position , '0');  //changing a character of the string to '0'
	}
	string_of_plane -> print();
	string_of_copied_plane -> print();
	
	string_of_plane -> concat(*string_of_copied_plane);  //adding copied string to original
	cout << "Length of both strings combined is : " << string_of_plane -> length() << endl;
	
	if (string_of_plane -> length() % 2 == 0)  //checking if string length is even or odd
		cout << "String's length is even so middle characters are : " << string_of_plane -> at(string_of_plane -> length() / 2) << " and " << string_of_plane -> at(string_of_plane -> length() / 2 + 1) << endl;
	else
		cout << "String's length is even so middle character is : " << string_of_plane -> at(string_of_plane -> length() / 2 + 1) << endl;
	
	string_of_plane -> clear();
	cout << "String's length after clearing it is : " << string_of_plane -> length() << endl;
	
	delete copied_plane;
	delete string_of_plane;
	delete string_of_copied_plane;
}




Object::Object() {
	
	id = additive_object_id; //global variable that starts as 1
	additive_object_id++;    //increases every time so all objects have unique IDs
	
	cout << "An Object was just created" << endl;
}
		
Object::Object(Object& old) {      
	
	id = old.get_id();
	cout << "A copy of an Object was just created" << endl;
}

Object::~Object() {		
	
	cout << "An Object is about to be destroyed" << endl;
}

int Object::get_id() {
	
	return id;
}

bool Object::equal(Object& check) {
	
	if (id == check.get_id())
		return true;
	else
		return false;
}

bool Object::identical(Object* check) {
	
	if (check == this)
		return true;
	else
		return false;
}

String* Object::toString() {
	
	ostringstream temp;       
	
	temp << "This is an Object with id: " << get_id();
	
	String* copy = new String(temp.str());
	return copy;
}








String::String(string s) : Object() {
	
	text = s;
	cout << "A String was just created" << endl;
}

String::String(String& old) : Object(old) {
    
	text = old.text;
	cout << "A copy of a String was just created" << endl;
}

String::~String() {
	
	cout << "A String is about to be destroyed" << endl;
}

string String::get_text() {
	
	return text;
}

bool String::equal(Object& check) {
	
	if (text == ((String&)check).get_text())
		return true;
	else
		return false;	
}

String* String::toString() {
	
	ostringstream temp;
	
	temp << "This is a String with ID: " << get_id() << " and text : " << get_text();
	
	String* copy = new String(temp.str());
	return copy;
}

Object* String::clone() {
	
	Object* copy = new String(*this);
	return copy;
}

int String::length() {
	
	return text.length();
}

void String::clear() {
	
	text.clear();
}

void String::concat(String& s) {
	
	text += s.get_text();
}

char String::at(int position) {
	
	return text.at(position);
}

void String::updateAt(int position , char c) {
	
	text.replace(position,1,1,c);
}

void String::print() {
	
	cout << text << endl;
}








PlaneComponent::PlaneComponent(String& s) : description(s) , readiness(0) {
	
	cout << "A Plane Component was just created" << endl;
}

PlaneComponent::PlaneComponent(PlaneComponent& pc) : Object(pc) , description(pc.get_description().get_text()) {
    
	cout << "A copy of a Plane Component was just created" << endl;
}

PlaneComponent::~PlaneComponent() {
	
	cout << "A Plane Component is about to be destroyed " << endl;
}

String PlaneComponent::get_description() {
	
	return description;
}

bool PlaneComponent::equal(Object& check) {
    
	if (get_id() == check.get_id())
    	return true;
    else
    	return false;
}

String* PlaneComponent::toString() {

    ostringstream temp;
	
	temp << "This is a Plane Component with id: " << get_id() << " and description: " << get_description().get_text();
	
	String* copy = new String(temp.str());
	return copy;
}

int PlaneComponent::get_readiness() {
	
	return readiness;
}

void PlaneComponent::add_readiness() {
	
	readiness += 1;
}








PassengerCompartment::PassengerCompartment(String& s , int chance) : PlaneComponent(s) {      
	
	if (chance == 0)    //chance is randomly 0 or 1
		inside = NULL;
	else
		inside = new PassengerCompartment(s , 0);   //only 1 Passenger Compartment within a Passenger Compartment,so 'chance' should be 0
	
	cout << "A PassengerCompartment was just created" << endl;
}
		
PassengerCompartment::PassengerCompartment(PassengerCompartment& pc) : PlaneComponent(pc) {
    
    if(pc.get_inside() == NULL)
		inside = NULL;
    else
	{
		String s ( pc.get_inside() -> get_description().get_text() );
		inside = new PassengerCompartment(s , 0);  //this is an inside compartment so again 'chance' should be 0
	}
	cout << "A copy of a PassengerCompartment was just created" << endl;
}

PassengerCompartment::~PassengerCompartment() {
	
	if(inside != NULL)
		delete inside;
	cout << "A PassengerCompartment is about to be destroyed" << endl;
}

PassengerCompartment* PassengerCompartment::get_inside() {
	
	return inside;
}
		
int PassengerCompartment::ready_check() {
	
	if(get_readiness() == 2)
	{
		if(inside != NULL)
		{
			return inside -> ready_check();
		}
		cout << "The description is : " << get_description().get_text() << endl << "Passenger Compartment OK" << endl;
		return 1;	
	}
	else
	{
		cout << "The description is : " << get_description().get_text() << endl << "Passenger Compartment not ready" << endl;
		return 0;
	}
}

void PassengerCompartment::process(Employee& e) {
	
	cout << "Employee named " << e.get_name().get_text() << " is working at Passenger Compartment with ID: " << get_id() << endl;
	
	e.workOn(*this);
}

bool PassengerCompartment::equal(Object& check) {
    	
    if (get_id() == check.get_id())
		return true;
	else
		return false;
}

String* PassengerCompartment::toString() {
	
    ostringstream temp;
	
	temp << "This is a Passenger Compartment with ID: " << get_id() << " and description: " << get_description().get_text();
	
	if(inside != NULL)
		temp << " and contains an inside Passenger Compartment";
	else
		temp << " and does not contain an inside Passenger Compartment";
	
	String* copy = new String(temp.str());
	return copy;
}
    
Object* PassengerCompartment::clone() {
    
    Object* copy = new PassengerCompartment(*this);
    return copy;
}








PrivateCompartment::PrivateCompartment(String& s) : PlaneComponent(s) {
	
	cout << "A Private Compartment was just created " << endl;
}

PrivateCompartment::PrivateCompartment(PrivateCompartment& pc) : PlaneComponent(pc) {
	
	cout << "A copy of a Private Compartment was just created " << endl;
}

PrivateCompartment::~PrivateCompartment() {
	
	cout << "A Private Compartment is about to be destroyed" << endl;
}

int PrivateCompartment::ready_check() {
   
    cout << "The description is : " << get_description().get_text() << endl << "Private Compartment OK" << endl;
}

void PrivateCompartment::process(Employee& e) {
    
	cout << "Employee named " << e.get_name().get_text() << " is working at the Private Compartment with ID: " << get_id() << endl;
}
	
String* PrivateCompartment::toString() {
	
    ostringstream temp;
	
	temp << "This a Private Compartment with ID: " << get_id() << " and description " << get_description().get_text();
	
	String* s = new String(temp.str());
	return s;
}

Object* PrivateCompartment::clone() {
    
    Object* copy = new PrivateCompartment(*this);
    return copy;
}








EquipmentCompartment::EquipmentCompartment(String& s) : PrivateCompartment(s) {

	cout << "An Equipment Compartment was just created" << endl;
}

EquipmentCompartment::EquipmentCompartment(EquipmentCompartment& ec) : PrivateCompartment(ec) {
    
	cout << "A copy of an Equipment Compartment was just created" << endl;
}

EquipmentCompartment::~EquipmentCompartment() {
	
	cout << "An Equipment Compartment is about to be destroyed" << endl;
}

int EquipmentCompartment::ready_check() {
    
    if(get_readiness() == 2)
    {
		cout << "The description is : " << get_description().get_text() << endl << "Equipment Compartment OK" << endl;
		return 1;
	}
	else
	{
		cout << "The description is : " << get_description().get_text() << endl << "Equipment Compartment not ready" << endl;
		return 0;
	}
}

void EquipmentCompartment::process(Employee& e) {

    cout << "Employee named " << e.get_name().get_text() << " is working at the Equipment Compartment with ID: " << get_id() << endl;

	e.workOn(*this);
}

String* EquipmentCompartment::toString() {
	
    ostringstream temp;
	
	temp << "This an Equipment Compartment with ID: " << get_id() << " and description " << get_description().get_text();
	
	String* copy = new String(temp.str());
	return copy;
}

Object* EquipmentCompartment::clone() {
    
    Object* copy = new EquipmentCompartment(*this);
    return copy;
}








CargoBay::CargoBay(String& s) : PrivateCompartment(s) {

	String e("This is an Equipment Compartment inside of a Cargo Bay");
	inside = new EquipmentCompartment(e);
	
	cout << "A CargoBay was just created" << endl;
}

CargoBay::CargoBay(CargoBay& cb) : PrivateCompartment(cb) {
	
	inside = new EquipmentCompartment(*(cb.get_inside()));
	cout << "A copy of a Cargo Bay was just created" << endl;
}

CargoBay::~CargoBay() {
	
	delete inside;
	cout << "A Cargo Bay is about to be destroyed" << endl;
}

EquipmentCompartment* CargoBay::get_inside() {
	
	return inside;
}

int CargoBay::ready_check() {
	
	if( (get_readiness() == 3) && (inside -> ready_check() == 1) )
	{
		cout << "The description is : " << get_description().get_text() << endl << "Cargo Bay OK" << endl;		 
		return 1;
	}
	else
	{
		cout << "The description is : " << get_description().get_text() << endl << "Cargo Bay not ready" << endl;
		return 0;
	}
}

void CargoBay::process(Employee& e) {
	
	cout << "Employee named " << e.get_name().get_text() << " is working at the Cargo Bay with ID: " << get_id() << endl;

	e.workOn(*this);
}

bool CargoBay::equal(Object& check) {
	
	if (get_id() == check.get_id())
		return true;
	else
		return false;
}

String* CargoBay::toString() {
	
    ostringstream temp;
    
    temp << "This is a Cargo Bay with ID : " << get_id() << " and description : " << get_description().get_text() << " with an Equipment Compartment inside";
	
	String* copy = new String(temp.str());
	return copy;
}

Object* CargoBay::clone() {
    
    Object* copy = new CargoBay(*this);
    return copy;
}








Plane::Plane(String& s , String& t , int c) : description(s) , title(t) {

	capacity = c;  //c was randomised between 100 and 300
	
	String cb("This is the Cargo Bay of the plane");  			
	cargo_b = new CargoBay(cb);
	
	String ec0("This is the FIRST Equipment Compartment of the Plane (1)"); 
	String ec1("This is the SECOND Equipment Compartment of the Plane (2)");
	String ec2("This is the THIRD Equipment Compartment of the Plane (3)");
	equip_c[0] = new EquipmentCompartment(ec0); 
	equip_c[1] = new EquipmentCompartment(ec1); 
	equip_c[2] = new EquipmentCompartment(ec2); 
	
	int num_of_compartments = capacity/50 + (c % 50 != 0);  //one compartment per 50 passengers plus another one for non-perfect division
	String pc("This is a Passenger Compartment of the plane"); 			
	
	passenger_c = new PassengerCompartment* [num_of_compartments];
	
	for(int i=0 ; i < num_of_compartments ; i++) {
		int chance = rand() % 2; 								//chance is either 0 or 1 to decide if the PassengerCompartment
		passenger_c[i] = new PassengerCompartment(pc , chance); //will have another PassengerCompartment inside of itslef
	}
	
	cout << "A Plane was just created" << endl;
}

Plane::Plane(Plane& plane) : Object(plane) , description(plane.get_description().get_text()) , title(plane.get_title().get_text()) {
	
	capacity = plane.get_capacity();
	
	cargo_b = new CargoBay(*(plane.get_cargo_b()));
	
	for(int i=0 ; i<3 ; i++)
		equip_c[i] = new EquipmentCompartment(*(plane.get_equip_c()[i]));
	
	passenger_c = new PassengerCompartment* [plane.get_num_of_compartments()];
	
	for(int i=0 ; i < plane.get_num_of_compartments() ; i++)
		passenger_c[i] = new PassengerCompartment(*(plane.get_passenger_c()[i]));
		
	cout << "A copy of a Plane was just created" << endl;	
}

Plane::~Plane() {
	
	cout << "A Plane is about to be destroyed" << endl;
	
	delete cargo_b;
	
	for(int i=0 ; i<3 ; i++) 
		delete equip_c[i];

	for(int j=0 ; j < get_num_of_compartments() ; j++) 
		delete passenger_c[j];
		
	delete[] passenger_c;
}

String Plane::get_description() {
	
	return description;
}

String Plane::get_title() {
	
	return title;
}

int Plane::get_capacity() {
	
	return capacity;
}

CargoBay* Plane::get_cargo_b() {
	
	return cargo_b;
}

EquipmentCompartment** Plane::get_equip_c() {
	
	return equip_c;
}

PassengerCompartment** Plane::get_passenger_c() {
	
	return passenger_c;
}
		
int Plane::ready_check() {
	
	int cb_check = cargo_b -> ready_check(); 
	
	int equip_check = 0;
	for(int i=0 ; i<3 ; i++) 
		equip_check += equip_c[i] -> ready_check();
	
	int pass_check = 0;	
	for(int j=0 ; j < get_num_of_compartments() ; j++) 
		pass_check += passenger_c[j] -> ready_check();
	
	if ( (cb_check == 1) && (equip_check == 3) && (pass_check == get_num_of_compartments()) )
	{
		cout << "Plane OK" << endl;
		return 1;	
	}
	else
	{
		cout << "Plane not ready" << endl;
		return 0;
	}
}

void Plane::process(Employee& e) {
	
	cout << "Employee " << e.get_name().get_text() << " is working at the Plane with ID : " << get_id() << endl;
	e.workOn(*this);
}

bool Plane::equal(Object& plane) {
		
	if ( (get_id() == plane.get_id()))
	{	
		for (int i=0 ; i<3 ; i++) 
		{
			if ( equip_c[i] -> equal(*((Plane&)plane).get_equip_c()[i]) == 0) //if equipment compartments are not equal 
				return false;												  //'break' by returning false
		}
		for (int j=0 ; j < get_num_of_compartments() ; j++)
		{
			if ( passenger_c[j] -> equal(*((Plane&)plane).get_passenger_c()[j]) == 0)  //if passenger compartments are not equal
				return false;														   //'break' by returning false
		}
			if ( cargo_b -> equal(*((Plane&)plane).get_cargo_b()) == 0 )	//if cargo bay is not equal
				return false;												//'break' by returning false
		
		return true;														//if everything is equal return true
	}
	else 
		return false;
}

String* Plane::toString() {
	
    ostringstream temp;
    
    temp << "This is a Plane with ID: " << get_id() << " and description: "<< get_description().get_text() << " with title: " << get_title().get_text();
    temp << " and passenger capacity: " << get_capacity() << ".It also contains a Cargo Bay , 3 equipment compartments and " << get_num_of_compartments() << " Passenger Compartments";
    
	String* copy = new String(temp.str());
	return copy;
}

Object* Plane::clone() {

    Object* copy = new Plane(*this);
    return copy;
}

int Plane::get_num_of_compartments() {  //calculates number of compartments in the plane based on the random passenger capacity
	
	return capacity/50 + (capacity % 50 != 0);
}








Employee::Employee(String& s) : name(s) {

	cout << "An Employee was just created" << endl;
}

Employee::Employee(Employee& e) : Object(e) , name(e.name) {
    
	cout << "A copy of an Employee was just created" << endl;
}

Employee::~Employee() {

	cout << "An Employee is about to be destroyed" << endl;
}

String Employee::get_name() {
	
	return name;
}

bool Employee::equal(Object& check) {
	
	String s(((Employee&)check).get_name().get_text()); //get name of employee we want to compare with
	
	if ( name.equal(s) == 1 )
		return true;
	else
		return false;	
}

String* Employee::toString() {
	
	ostringstream temp;
    
	temp << "This is an Employee with ID: " << get_id() << " and name : " << get_name().get_text();
    
	String* copy = new String(temp.str());
	return copy;
}








SecurityEmployee::SecurityEmployee(String& s) : Employee(s) {
	
	cout << "A Security Employee was just created" << endl;
}

SecurityEmployee::SecurityEmployee(SecurityEmployee& se) : Employee(se) {

    cout << "A copy of a Security Employee was just created" << endl;
}

SecurityEmployee::~SecurityEmployee() {
    
	cout << "A Security Employee is about to be destroyed" << endl;
}

String* SecurityEmployee::toString() {
	
	ostringstream temp;
    
	temp << "This is a Security Employee with ID: " << get_id() << " and name : " << get_name().get_text();
    
	String* copy = new String(temp.str());
	return copy;
}

Object* SecurityEmployee::clone() {
	
	Object* copy = new SecurityEmployee(*this);
	return copy;
}

void SecurityEmployee::workOn(Plane& plane) {
		
	cout << "Security Employee " << get_name().get_text() << " is working on the plane" << endl;
	
	for(int i=0 ; i < plane.get_num_of_compartments() ; i++)
		plane.get_passenger_c()[i] -> process(*this);
		
	for(int j=0 ; j<3 ; j++)
		plane.get_equip_c()[j] -> process(*this);
	
	plane.get_cargo_b() -> process(*this);			
}

void SecurityEmployee::workOn(PassengerCompartment& pc) {

	cout << "Security Employee " << get_name().get_text() << " is working on the Passenger Compartment of the plane" << endl;
	pc.add_readiness();
	
	if(pc.get_inside() != NULL)
		workOn(*(pc.get_inside()));
}
	
void SecurityEmployee::workOn(EquipmentCompartment& ec) {
	
	cout << "Security Employee " << get_name().get_text() << " is working on the Equipment Compartment of the plane" << endl;
	ec.add_readiness();
}

void SecurityEmployee::workOn(CargoBay& cb) {
	
	cout << "Security Employee " << get_name().get_text() << " is working on the Cargo Bay of the plane" << endl;
	cb.add_readiness();
	
	workOn(*(cb.get_inside()));
}
	
void SecurityEmployee::report() {
	
	cout << "Security Employee " << get_name().get_text() << " made sure all parts of the plane are SECURE" << endl;
	cout << "OK" << endl;
}








MaintenanceEmployee::MaintenanceEmployee(String& s) : Employee(s) {

	cout << "A Maintenance Employee was just created" << endl;
}

MaintenanceEmployee::MaintenanceEmployee(MaintenanceEmployee& me) : Employee(me) {

    cout << "A copy of a Maintenance Employee was just created" << endl;
}

MaintenanceEmployee::~MaintenanceEmployee() {
	
	cout << "A Maintenance Employee is about to be destroyed" << endl;
}

String* MaintenanceEmployee::toString() {
   
	ostringstream temp;
   
    temp << "This is a Maintenance Employee with ID: " << get_id() << " and name : " << get_name().get_text();
    
	String* copy = new String(temp.str());
	return copy;
}

Object* MaintenanceEmployee::clone() {

	Object* copy = new MaintenanceEmployee(*this);
	return copy;
}

void MaintenanceEmployee::workOn(Plane& plane) {

    cout << "Maintenance Employee " << get_name().get_text() << " is working on the plane" << endl;
		
	for(int j=0 ; j<3 ; j++)
		plane.get_equip_c()[j] -> process(*this);
	
	plane.get_cargo_b() -> process(*this);
}
		
void MaintenanceEmployee::workOn(PassengerCompartment& pc) {}   //empty body so MaintenanceEmployee doesn't become abstract class

void MaintenanceEmployee::workOn(EquipmentCompartment& ec) {

	cout << "Maintenance Employee " << get_name().get_text() << " is working on the Equipment Compartment of the plane" << endl;
	ec.add_readiness();
}

void MaintenanceEmployee::workOn(CargoBay& cb) {
	
	cout << "Maintenance Employee " << get_name().get_text() << " is working on the Cargo Bay of the plane" << endl;
	cb.add_readiness();
	
	workOn(*(cb.get_inside()));
}

void MaintenanceEmployee::report() {
    
	cout << "Maintenance Employee " << get_name().get_text() << " made sure all parts of the plane are MAINTAINED" << endl;
    cout << "OK" << endl;
}








CleaningEmployee::CleaningEmployee(String& s) : Employee(s) {

	cout << "A Cleaning Employee was just created" << endl;
}

CleaningEmployee::CleaningEmployee(CleaningEmployee& ce) : Employee(ce) {

    cout << "A copy of a Cleaning Employee was just created" << endl;
}

CleaningEmployee::~CleaningEmployee() {

	cout << "A Cleaning Employee is about to be destroyed" << endl;
}

String* CleaningEmployee::toString() {
   
	ostringstream temp;
    
	temp << "This is a Cleaning Employee with ID: " << get_id() << " and name " << get_name().get_text();
    
	String* copy = new String(temp.str());
	return copy;
}

Object* CleaningEmployee::clone() {

	Object* copy = new CleaningEmployee(*this);
	return copy;
}

void CleaningEmployee::workOn(Plane& plane) {
    	
	cout << "Cleaning Employee " << get_name().get_text() << " is working on the plane" << endl;
	
	for(int i=0 ; i < plane.get_num_of_compartments() ; i++)
		plane.get_passenger_c()[i] -> process(*this);
	
	plane.get_cargo_b() -> process(*this);
}	
	
void CleaningEmployee::workOn(PassengerCompartment& pc) {
   
    cout << "Cleaning Employee " << get_name().get_text() << " is working on the Passenger Compartment of the plane" << endl;
    pc.add_readiness();
	
	if(pc.get_inside() != NULL)
		workOn(*(pc.get_inside()));
}

void CleaningEmployee::workOn(EquipmentCompartment& ec) {}  //empty body so CleaningEmployee doesn't become abstract class

void CleaningEmployee::workOn(CargoBay& cb) {

	cout << "Cleaning Employee " << get_name().get_text() << " is working on the Cargo Bay of the plane" << endl;
	cb.add_readiness();
	
	workOn(*(cb.get_inside()));
}
	
void CleaningEmployee::report() {
  
    cout << "Cleaning Employee " << get_name().get_text() << " made sure all parts of the plane are CLEANED" << endl;
    cout << "OK" << endl;
}




