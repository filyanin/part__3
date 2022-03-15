#include <iostream>
#include <vector>

class Vehicle {
public:

	virtual std::ostream& print(std::ostream& _stream) const = 0;

	friend  std::ostream& operator<<(std::ostream& _stream, const Vehicle& _vehicle) {

		return _vehicle.print(_stream);

	}
};

class Wheel {
public:
	Wheel() {}
	Wheel(float _diametr) {

		diametr = _diametr;
	}
	std::ostream& printDiametr(std::ostream& _stream) {

		return (_stream << diametr << " ");

	}

protected:

	float diametr;

};


class Engine {
public:
	Engine() {}

	Engine(float _power) {

		power = _power;

	}

	std::ostream& printPower(std::ostream& _stream) const {

		return (_stream << "Engine: " << power << " ");

	}

	float GetPower() {
		return power;
	}

protected:
	float power;
};


/*Для унификации и на основе сходства перенёс переменные члены класса Wheel в клас RoadVehicle в виде динамического массива, если надо будет изменить, напиште*/
class RoadVehicle : public Vehicle {
public:
	RoadVehicle() {}

	RoadVehicle(float _rideHeight) {

		rideHeight = new float(_rideHeight);
		wheels = nullptr;
		wheelsCount = nullptr;

	}

	RoadVehicle(float _rideHeight, int _wheelsCount) {

		rideHeight = new float(_rideHeight);
		wheels = nullptr;
		wheelsCount = new int(_wheelsCount);

	}

	std::ostream& printWheels(std::ostream& _stream) const {

		_stream << "Wheels: ";

		if (wheels != nullptr) {

			for (int i = 0; i < *wheelsCount; i++) {

				wheels[i].printDiametr(_stream);

			}
		}

		return _stream;

	}

	std::ostream& printRideHeight(std::ostream& _stream) const {

		return (_stream << "Ride height: " << *rideHeight << " ");

	}

	virtual std::ostream& print(std::ostream& _stream) const override {

		_stream << "Road vehicle ";
		return printRideHeight(_stream);

	}

	virtual ~RoadVehicle() {

		delete[] wheels;
		delete wheelsCount;
		delete rideHeight;

	}

protected:

	float* rideHeight;
	Wheel *wheels;
	int* wheelsCount;

};



class WaterVehicle : public Vehicle {
public:

	WaterVehicle() {}

	WaterVehicle(float _draft) {

		draft = new float(_draft);

	}

	std::ostream& printDraft(std::ostream& _stream) const {

		return (_stream << "Draft: " << *draft << " ");

	}

	virtual std::ostream& print(std::ostream& _stream) const override {

		_stream << "Water vehicle ";
		return printDraft(_stream);

	}

	virtual ~WaterVehicle() {

		delete draft;

	}
protected:

	float* draft;

};

class Bicycle : public RoadVehicle {
public:
	Bicycle() {}

	Bicycle(Wheel _frontWheel, Wheel _backWheel, float _rideHeight) : RoadVehicle(_rideHeight, 2) {

		wheels = new Wheel[2]{ _frontWheel, _backWheel };
		

	}

	virtual std::ostream& print(std::ostream& _stream) const override {

		_stream << "Bicycle ";
		printWheels(_stream);
		return printRideHeight(_stream);

	}

};

class Car : public RoadVehicle {

public:

	Car(Engine _engine, Wheel _frontLeftWheel, Wheel _frontRightWheel, Wheel _backLeftWheel, Wheel _backRightWheel, float _rideHeight) : RoadVehicle(_rideHeight, 4) {

		engine = _engine;
		wheels = new Wheel[4]{ _frontLeftWheel,_frontRightWheel,_backLeftWheel,_backRightWheel };

	}

	float GetPower() {
		return engine.GetPower();
	}

	virtual std::ostream& print(std::ostream& _stream) const override {

		_stream << "Car ";
		engine.printPower(_stream);
		printWheels(_stream);
		return printRideHeight(_stream);

	}

protected:
	Engine engine;
};

float getHighestPower(std::vector<Vehicle*> v) {

	float maxPower = 0;
	for (int i = 0; i < v.size(); i++)
	{

		if (Car* tmpCar = dynamic_cast<Car*>(v[i])) {
			if (maxPower < tmpCar->GetPower()) {

				maxPower = tmpCar->GetPower();

			}
		}

	}

	return maxPower;

}
int main()
{
	Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);

	std::cout << c << '\n';


	Bicycle t(Wheel(20), Wheel(20), 300);

	std::cout << t << '\n' << '\n';


	std::vector<Vehicle*> v;

	v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));


	//под этот класс не было спецификации
	//v.push_back(new Circle(Point(1, 2, 3), 7));

	v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));

	v.push_back(new WaterVehicle(5000));

	std::cout << "The highest power is " << getHighestPower(v) << '\n';

	for (int i = v.size() - 1; i > 0; i--) {
		delete v[i];
	}

}
