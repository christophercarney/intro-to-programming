//Christopher Carney CMPSC 121 Section 002
//Homework #1, September 2013
//This program takes empirical data from a test shot to determine the acceleration due to gravity on the angry birds planet
//This data is then used to measure other calculations

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double i_displace;			//initial displacement; how far the rock moves after 1 rotation
	double time;				 //how long the projrectile took to reach the inital displacement
	double i_velocity;			//inital velocity of the object also the constant in v = kc (where v is initial velocity and c is # of cranks since input is 1 v = k)
	double gravity;				//acceleration due to gravity on the planet
	double maxRange;			//maximum range of the object [ANSWER OUTPUT NEEDED]
	double height_8cranks;		// the height of the projectile after 8 cranks [ANSWER OUTPUT NEEDED]
	double launch_height;		// the height the cannon has to be to reach the same distance in only 7 cranks [ANSWER OUTPUT NEEDED]
	double max_i_velocity;		//using Hookes law calculate the maximum initial velocity after 9 cranks
	double timeMaxDistance;		//time it takes for an object to reach the maximum distance
	double velocity_8cranks;
	double time_8cranks;
	double velocity_7cranks;
	double time_7cranks;
	double inputDistance;


	cout << "How far (in meters) did the rock move after one revolution? "; //user inputs initial displacement and time after prompted
	cin >> i_displace;
	cout << "How much time (in seconds) did it take to get there? ";
	cin >> time;
	cout << "[E.C.] How far away is the target? ";
	cin >> inputDistance;


	i_velocity = i_displace / time;			//using initial displacement and time it took to reach that solve for the initial velocity
	gravity = (2 * i_velocity) / time;		//derive an equation from [v - (1/2) g t] to solve for gravity on the planet


	max_i_velocity = i_velocity * 9;						//velocity is directly proportional to cranks v=kc (where k is constant and c is cranks) k=v/c ... k = i_velocity / 1
	timeMaxDistance = (2 * max_i_velocity) / gravity;		//derived from the equation v - (1/2) g t to solve for the time it takes to reach max distance
	maxRange = max_i_velocity * timeMaxDistance;			//use the equation x = v t to  


	// Use direct proportion v=kc to solve for v and use x / v = t to solve for time and use in equation below
	velocity_8cranks = i_velocity * 8;
	time_8cranks = 750 / velocity_8cranks;
	height_8cranks = (velocity_8cranks * time_8cranks) - (0.5 * gravity * (time_8cranks * time_8cranks)); //using the equation x = v t - (1/2) g t² where x is the net altitude


	//use a similar method knowing it has to hit 750m in 7 cranks to figure out how high up it will have to be to hit 750
	velocity_7cranks = i_velocity * 7;
	time_7cranks = 750 / velocity_7cranks;  // t = x / v
	launch_height = -1 * ((750) - (0.5 * (gravity * ((750 * 750) / (velocity_7cranks * velocity_7cranks))))); //substitute t = x / v for the equation x = vt - 1/2 g t^2 multiply by -1 b/c it is expressed in height above ground from downwards


	//[E.C.] gives reasonable answers, if unable to find a solution within 300m vertically it is considered unobtainable
	int n = 1;
	double v_crank;
	double v_time;
	double v_height = -10;

	while (v_height < 0 || v_height > 300) {
		v_crank = i_velocity * n;
		v_time = inputDistance / v_crank;
		v_height = -1 * ((v_crank * v_time) - (0.5 * gravity * (v_time * v_time)));
		n = n + 1;}

	//output results with 2 decimals
	cout << fixed << setprecision(2) << "The maximum range for this mortar seems to be " << maxRange << " meters." << endl;
	cout << fixed << setprecision(2) << "At 8 cranks, the projectile would be at a height of " << height_8cranks << "m after moving 750m in the horizontal." << endl;
	cout << fixed << setprecision(2) << "To hit at only 7 cranks requires launching from a height of " << launch_height << " meters." << endl;
	cout << fixed << setprecision(2) << "To hit a distance of " << inputDistance << " would require " << (v_crank / i_velocity) << " cranks and to be launched from a height of " << v_height << " meters." << endl;

	return 0;

}