#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "planeClasses.h"
using namespace std;

void clone_encrypt_and_print(Object& plane);

int additive_object_id = 1;  //global variable to assign the ID of each new object

int main() {
    
    srand ( time(NULL) );
    
    String description("'This is a Plane'");          
    String title("'Airplane'");
    int random_capacity = (rand() % 201) + 100;       //randomized passenger capacity : 100-300
	
	Plane plane(description , title , random_capacity);      
	
	String name1("'Security'");
    String name2("'Mechanic'");
    String name3("'Cleaner'");
    
	SecurityEmployee security_emp(name1);       
	MaintenanceEmployee maintenance_emp(name2);
	CleaningEmployee cleaning_emp(name3);
	
	plane.process(security_emp);               
	plane.process(maintenance_emp);
	plane.process(cleaning_emp);
	
	security_emp.report();                 
	maintenance_emp.report();
	cleaning_emp.report();
	
	plane.ready_check();                
	
	cout << "Plane ready to take off!" << endl;
	
	clone_encrypt_and_print(plane);     
}
	
	
