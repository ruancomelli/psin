#define BOOST_TEST_MODULE EntityLibTest

// UtilsLib
#include <Test.hpp>
#include <Vector3D.hpp>
#include <Vector.hpp>

// EntityLib
#include <Boundary.hpp>
#include <FixedBoundary.hpp>
#include <FixedInfinitePlane.hpp>

#include <HandledEntity.hpp>
#include <Particle.hpp>
#include <PhysicalEntity.hpp>
#include <SpatialEntity.hpp>
#include <SocialEntity.hpp>
#include <SphericalParticle.hpp>

// PropertyLib
#include <Property.hpp>
#include <PropertyDefinitions.hpp>

// Standard
#include <cstdio>
#include <iostream>
#include <type_traits>

using namespace psin;

using namespace std;

namespace psin {
	template<typename Out>
	Out& operator<<(Out& out, const std::vector<Vector3D> & v)
	{
		for( auto&& entry : v )
		{
			out << entry << std::endl;
		}

		return out;
	}
} // psin

TestCase(HandledEntity_Test)
{
	HandledEntity entity1;

	// Test the default handle and the getHandle function
	int defaultHandle = DEFAULT_HANDLED_ENTITY_HANDLE;
	checkEqual( entity1.getHandle() , defaultHandle );

	// Test the setHandle function
	int handleToSet = 2;
	entity1.setHandle(handleToSet);
	checkEqual( entity1.getHandle() , handleToSet );

	// Test constructor passing one argument
	int initialHandle = 1;
	HandledEntity entity2(initialHandle);

	checkEqual( entity2.getHandle() , initialHandle );

	HandledEntity entity3 = entity1;

	checkEqual( entity1.getHandle(), entity3.getHandle() );

	int commonHandle = 7;
	HandledEntity entity4(commonHandle);
	HandledEntity entity5(commonHandle);

	check(entity4 == entity5);
}

TestCase(SocialEntityBaseClass_Test)
{
	int defaultHandle = -1;
	int handleToSet = 3;

	SocialEntity social1;

	checkEqual(social1.getHandle(), defaultHandle);

	social1.setHandle(handleToSet);

	checkEqual(social1.getHandle(), handleToSet);

	SocialEntity social2(handleToSet);

	checkEqual(social2.getHandle(), handleToSet);
}

TestCase(SocialEntityNeighborhood_Test)
{
	int handle1 = 3;
	int handle2 = 10;

	SocialEntity social;

	check(social.getNeighborhood().empty());

	SocialEntity neighbor1(handle1);
	SocialEntity neighbor2(handle2);

	social.addNeighbor(neighbor1);
	social.addNeighbor(neighbor2);

	check(social.getNeighborhood().count(handle1));
	check(social.getNeighborhood().count(handle2));

	social.removeNeighbor(neighbor2);

	check(social.getNeighborhood().count(handle1));
	check(!social.getNeighborhood().count(handle2));
}

TestCase(SpatialEntityTaylorOrderTest)
{
	int validTaylorOrder1 = 4;
	int validTaylorOrder2 = 5;

	SpatialEntity spatial(validTaylorOrder1);
	checkEqual(spatial.getTaylorOrder(), validTaylorOrder1);

	// Uncomment the following lines to get runtime errors:
	// int invalidTaylorOrder1 = -1;
	// SpatialEntity invalidSpatial(invalidTaylorOrder1);

	spatial.setTaylorOrder(validTaylorOrder2);
	checkEqual(spatial.getTaylorOrder(), validTaylorOrder2);

	// Uncomment the following lines to get runtime errors:
	// int invalidTaylorOrder2 = -1;
	// spatial.setTaylorOrder(invalidTaylorOrder2);

	SpatialEntity spatial3;
	checkEqual(spatial3.getTaylorOrder(), DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
}

TestCase(SpatialEntityPositionMatrixOrientationMatrixTest)
{
	std::vector<Vector3D> positionMatrix;
	positionMatrix.push_back( Vector3D(1.8, 2.5, 3.9) );
	positionMatrix.push_back( Vector3D(8.6, 7.4, 2.1) );
	positionMatrix.push_back( Vector3D(-1.2, 0.0, 300.5) );
	positionMatrix.push_back( Vector3D(-9.9, 0.31, 0.0021) );
	positionMatrix.push_back( Vector3D(8.9, -1111.0, 3.9) );

	std::vector<Vector3D> orientationMatrix;
	orientationMatrix.push_back( Vector3D(5.8, -4.65, -0.12) );
	orientationMatrix.push_back( Vector3D(86.9, 61.45, -10.89) );
	orientationMatrix.push_back( Vector3D(1.89, -65.0, 0.0) );
	orientationMatrix.push_back( Vector3D(0.0, 18.5, 11.54) );
	orientationMatrix.push_back( Vector3D(-89.56, 112.0, 123456789.0) );

	SpatialEntity spatial( positionMatrix.size() - 1 );
	spatial.setPositionMatrix(positionMatrix);
	spatial.setOrientationMatrix(orientationMatrix);

	checkEqual(spatial.getPositionMatrix(), positionMatrix);
	checkEqual(spatial.getOrientationMatrix(), orientationMatrix);

	// Uncomment the following lines to get runtime errors:
	// orientationMatrix.push_back( Vector3D(-0.5, 12.13, 89.78) );
	// spatial.setOrientationMatrix(orientationMatrix);
}

TestCase(SpatialEntityPositionVelocityAccelerationTest)
{
	int validDerivative = 3;

	SpatialEntity spatial;

	Vector3D position1(1.5, 1.6, 1.7);
	Vector3D position2(-0.5, 1.55, 30.65);
	Vector3D position3(3.14159, 1.55, 0.0);

	spatial.setPosition(position1);
	checkEqual(spatial.getPosition(), position1);

	spatial.setPosition(position2.x(), position2.y(), position2.z());
	checkEqual(spatial.getPosition(), position2);

	spatial.setPosition(position3.x(), position3.y());
	checkEqual(spatial.getPosition(), position3);

	Vector3D velocity1(8.9, 11.5, 36.5);
	Vector3D velocity2(7.1, 131.7, 0.58);
	Vector3D velocity3(-11.25, 0.56, 0.0);

	spatial.setVelocity(velocity1);
	checkEqual(spatial.getVelocity(), velocity1);

	spatial.setVelocity(velocity2.x(), velocity2.y(), velocity2.z());
	checkEqual(spatial.getVelocity(), velocity2);

	spatial.setVelocity(velocity3.x(), velocity3.y());
	checkEqual(spatial.getVelocity(), velocity3);

	Vector3D acceleration1(18.07, -3.141598, 1.618);
	Vector3D acceleration2(1.2351, -485.6, 12.5);
	Vector3D acceleration3(88.97, 15.65, 0.0);

	spatial.setAcceleration(acceleration1);
	checkEqual(spatial.getAcceleration(), acceleration1);

	spatial.setAcceleration(acceleration2.x(), acceleration2.y(), acceleration2.z());
	checkEqual(spatial.getAcceleration(), acceleration2);

	spatial.setAcceleration(acceleration3.x(), acceleration3.y());
	checkEqual(spatial.getAcceleration(), acceleration3);

	Vector3D derivative1(2.98, 9.87, -8251.02);
	Vector3D derivative2(0.0, -68.1, 48.8);
	Vector3D derivative3(-64.5, 112358.1321, 0.0);

	spatial.setPositionDerivative(validDerivative, derivative1);
	checkEqual(spatial.getPositionDerivative(validDerivative), derivative1);

	spatial.setPositionDerivative(validDerivative, derivative2.x(), derivative2.y(), derivative2.z());
	checkEqual(spatial.getPositionDerivative(validDerivative), derivative2);

	spatial.setPositionDerivative(validDerivative, derivative3.x(), derivative3.y());
	checkEqual(spatial.getPositionDerivative(validDerivative), derivative3);

	// Uncomment the following lines to get runtime errors:
	// int invalidDerivative = -1;
	// spatial.setPositionDerivative(invalidDerivative, derivative1);
	// spatial.getPositionDerivative(invalidDerivative);
}

TestCase(SpatialEntityAngularPositionVelocityAccelerationTest)
{
	int validDerivative = 3;

	SpatialEntity spatial;

	Vector3D orientation1(1.5, 1.6, 1.7);
	Vector3D orientation2(-0.5, 1.55, 30.65);
	Vector3D orientation3(3.14159, 1.55, 0.0);

	spatial.setOrientation(orientation1);
	checkEqual(spatial.getOrientation(), orientation1);

	spatial.setOrientation(orientation2.x(), orientation2.y(), orientation2.z());
	checkEqual(spatial.getOrientation(), orientation2);

	spatial.setOrientation(orientation3.x(), orientation3.y());
	checkEqual(spatial.getOrientation(), orientation3);

	Vector3D angularVelocity1(8.9, 11.5, 36.5);
	Vector3D angularVelocity2(7.1, 131.7, 0.58);
	Vector3D angularVelocity3(-11.25, 0.56, 0.0);

	spatial.setAngularVelocity(angularVelocity1);
	checkEqual(spatial.getAngularVelocity(), angularVelocity1);

	spatial.setAngularVelocity(angularVelocity2.x(), angularVelocity2.y(), angularVelocity2.z());
	checkEqual(spatial.getAngularVelocity(), angularVelocity2);

	spatial.setAngularVelocity(angularVelocity3.x(), angularVelocity3.y());
	checkEqual(spatial.getAngularVelocity(), angularVelocity3);

	Vector3D angularAcceleration1(18.07, -3.141598, 1.618);
	Vector3D angularAcceleration2(1.2351, -485.6, 12.5);
	Vector3D angularAcceleration3(88.97, 15.65, 0.0);

	spatial.setAngularAcceleration(angularAcceleration1);
	checkEqual(spatial.getAngularAcceleration(), angularAcceleration1);

	spatial.setAngularAcceleration(angularAcceleration2.x(), angularAcceleration2.y(), angularAcceleration2.z());
	checkEqual(spatial.getAngularAcceleration(), angularAcceleration2);

	spatial.setAngularAcceleration(angularAcceleration3.x(), angularAcceleration3.y());
	checkEqual(spatial.getAngularAcceleration(), angularAcceleration3);

	Vector3D derivative1(2.98, 9.87, -8251.02);
	Vector3D derivative2(0.0, -68.1, 48.8);
	Vector3D derivative3(-64.5, 112358.1321, 0.0);

	spatial.setOrientationDerivative(validDerivative, derivative1);
	checkEqual(spatial.getOrientationDerivative(validDerivative), derivative1);

	spatial.setOrientationDerivative(validDerivative, derivative2.x(), derivative2.y(), derivative2.z());
	checkEqual(spatial.getOrientationDerivative(validDerivative), derivative2);

	spatial.setOrientationDerivative(validDerivative, derivative3.x(), derivative3.y());
	checkEqual(spatial.getOrientationDerivative(validDerivative), derivative3);

	// Uncomment the following lines to get runtime errors:
	// int invalidDerivative = -1;
	// spatial.setOrientationDerivative(invalidDerivative, derivative1);
	// spatial.getOrientationDerivative(invalidDerivative);
}

TestCase(SpatialEntityDistanceTest)
{
	Vector3D leftPosition = Vector3D(-3.1415, 1.618, -2.718);
	Vector3D rightPosition = Vector3D(11.12, -58.13, 21.34);
	double distanceValue = (leftPosition - rightPosition).length();

	SpatialEntity left;
	SpatialEntity right;

	left.setPosition(leftPosition);
	right.setPosition(rightPosition);

	checkEqual(distance(left, right), distanceValue);
}

TestCase(SpatialEntityNormalDirectionTest)
{
	SpatialEntity spatial0;
	SpatialEntity spatial1;

	Vector3D normalVector(5.6, 7.8, 9.1);
	Vector3D normalVersor(normalVector.normalized());

	Vector3D position0(-8.5, 1.4, 20.6);
	Vector3D position1(position0 + normalVector);

	spatial0.setPosition(position0);
	spatial1.setPosition(position1);

	checkEqual(spatial0.normalVersor(spatial1), normalVersor);
}

TestCase(json_SpatialEntity_Test)
{
	json j{
		{"Position", 
			{{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0},
			{7.0, 8.0, 9.0},
			{10.0, 11.0, 12.0}}
		},
		{"Orientation", 
			{{-10.0, -11.0, -12.0},
			{7.0, 8.0, 9.0},
			{-4.0, -5.0, -6.0},
			{1.0, 2.0, 3.0}}
		}
	};

	SpatialEntity spatial = j;

	std::vector<Vector3D> position{
		{1.0, 2.0, 3.0},
		{4.0, 5.0, 6.0}, 
		{7.0, 8.0, 9.0},
		{10.0, 11.0, 12.0}
	};

	std::vector<Vector3D> orientation{
		{-10.0, -11.0, -12.0},
		{7.0, 8.0, 9.0},
		{-4.0, -5.0, -6.0}, 
		{1.0, 2.0, 3.0}
	};

	checkEqual(
		spatial.getPositionMatrix(),
		position
	);

	checkEqual(
		spatial.getOrientationMatrix(),
		orientation
	);

	json j2 = spatial;
	checkEqual(j2, j);
}

TestCase(PhysicalEntityInstantiationTest)
{
	PhysicalEntity<int, double, char> physicalEntitySuccess1;
	PhysicalEntity<int, double, double> physicalEntitySuccess2;
}

TestCase(PhysicalEntityPropertyListTest)
{
	PhysicalEntity<int, double, char> physicalEntity;

	check((std::is_same<
		PhysicalEntity<int, double, char>::PropertyList,
		mp::type_collection<int, double, char>
	>::value));
}

TestCase(PhysicalEntityPropertyTest)
{
	int intValue = 3;
	double doubleValue = 5.6;

	PhysicalEntity<int, double> physicalEntity;
	physicalEntity.property<int>() = intValue;
	physicalEntity.property<double>() = doubleValue;

	checkEqual(physicalEntity.property<int>(), intValue);
	checkEqual(physicalEntity.property<double>(), doubleValue);

	auto x = physicalEntity.property<double>();
	x *= 2;

	// Check that physicalEntity.property<double>() didn't change
	checkEqual(physicalEntity.property<double>(), doubleValue);

	PhysicalEntity<int, double> physicalEntity1;
	physicalEntity1.property<int>() = intValue;

	PhysicalEntity<int, double> physicalEntity2(physicalEntity1);
	checkEqual(physicalEntity2.property<int>(), intValue);
}

TestCase(PhysicalEntity_has_property_Test)
{
	check((
			has_property< 
				PhysicalEntity<Mass, Volume>,
				Mass
			>::value
		));
	check( not(
			has_property< 
				PhysicalEntity<Mass, Volume>,
				PoissonRatio
			>::value
		));
	check((
			has_properties< 
				PhysicalEntity<Mass, Volume>
			>::value
		));
	check((
			has_properties< 
				PhysicalEntity<Mass, Volume>,
				Mass,
				Volume
			>::value
		));
	check( not(
			has_properties< 
				PhysicalEntity<Mass, Volume>,
				Mass,
				PoissonRatio
			>::value
		));
}

namespace PhysicalEntityCallPropertyMemberFunction_Test_namespace
{
	struct A
	{
		int f()
		{
			return 5;
		}
	};
}

TestCase(PhysicalEntityCallPropertyMemberFunction_Test)
{
	using namespace PhysicalEntityCallPropertyMemberFunction_Test_namespace;
	
	int returnValue = 5;
	PhysicalEntity<A> physicalEntity;

	checkEqual(physicalEntity.property<A>().f(), returnValue);
}

namespace PhysicalEntityInputAndOutput_Test_namespace
{
	struct TestedProperty : public Property<double>
	{};
}

TestCase(PhysicalEntityInputAndOutput_Test)
{
	using namespace PhysicalEntityInputAndOutput_Test_namespace;

	double tolerance = 1e-12;
	double defaultValue = 0.0;
	double value = 3.14;

	PhysicalEntity<TestedProperty> inputter;
	PhysicalEntity<TestedProperty> outputter;

	inputter.property<TestedProperty>().set(defaultValue);
	outputter.property<TestedProperty>().set(value);

	string fileName = "PhysicalEntity_Input_Output_Test.txt";
	fstream file(fileName, fstream::in | fstream::out | fstream::trunc);

	outputter.output<TestedProperty>(file);

	file.clear();
	file.seekg(0, ios::beg);

	inputter.input<TestedProperty>(file);

	checkClose(inputter.property<TestedProperty>().get(), value, tolerance);

	file.close();

	std::remove(fileName.c_str());
}

namespace PhysicalEntity_set__and__get_Test_namespace
{
	struct DummyType {};
	struct PropertyWithoutGetAndSetFunctions
		: public Property<DummyType> 
	{};
}

TestCase(PhysicalEntity_set__and__get_Test)
{
	using namespace PhysicalEntity_set__and__get_Test_namespace;

	{
		double tolerance = 1e-12;
		double massValue = 15.4;

		PhysicalEntity<Mass> physicalEntity;

		physicalEntity.set<Mass>(massValue);
		checkClose(physicalEntity.get<Mass>(), massValue, tolerance);
	}

	// Uncomment the following test to get compilation errors because PhysicalEntity_set__and__get_Test_PropertyWithoutGetAndSetFunctions has no functions 'set' and 'get'
	{
		PropertyWithoutGetAndSetFunctions physicalEntity;
		// physicalEntity.get<DummyType>();
	}

}

TestCase(MassInPhysicalEntityTest)
{
	double massValue = 5;
	PhysicalEntity<Mass> physicalEntity;

	check( !( physicalEntity.assigned<Mass>() ) );

	physicalEntity.set<Mass>(massValue);

	check(( physicalEntity.assigned<Mass>() ));

	checkEqual(physicalEntity.get<Mass>(), massValue);
}

TestCase(json_PhysicalEntity_Test)
{
	double massValue = 15.4;
	double volumeValue = 89.5;

	json j{
		{"Mass", massValue},
		{"Volume", volumeValue}
	};

	PhysicalEntity<Mass, Volume, MomentOfInertia> p = j;
	json j2 = p;

	check(p.assigned<Mass>());
	check(p.assigned<Volume>());
	check(!p.assigned<MomentOfInertia>());
	checkEqual(p.get<Mass>(), massValue);
	checkEqual(p.get<Volume>(), volumeValue);
	checkEqual(j2, j);
}

TestCase(ParticleConstructorTest)
{
	int defaultTaylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER;

	string name = "Tarintor";
	int taylorOrder = 4;

	double massValue = 3.1415;
	double volumeValue = 1.618;

	Particle<Volume> particle1;
	checkEqual(particle1.getName(), Named::defaultName);
	checkEqual(particle1.getTaylorOrder(), defaultTaylorOrder);

	Particle<Volume> particle2(name, taylorOrder);
	checkEqual(particle2.getName(), name);
	checkEqual(particle2.getTaylorOrder(), taylorOrder);

	PhysicalEntity<Mass, MomentOfInertia, Volume> physicalEntity;
	physicalEntity.set<Mass>(massValue);
	physicalEntity.set<Volume>(volumeValue);

	// Particle<Mass, Volume, MomentOfInertia> particle3(physicalEntity);
	// checkEqual(particle3.get<Mass>(), massValue);
	// checkEqual(particle3.get<Volume>(), volumeValue);
}

TestCase(ParticleForcesAndTorquesTest)
{
	Particle<> particle;

	checkEqual(particle.getBodyForce(), nullVector3D());
	checkEqual(particle.getContactForce(), nullVector3D());
	checkEqual(particle.getResultingForce(), nullVector3D());
	checkEqual(particle.getResultingTorque(), nullVector3D());

	Vector3D bodyForce1(1, 0.5, 3.14);
	particle.addBodyForce(bodyForce1);
	checkEqual(particle.getBodyForce(), bodyForce1);
	checkEqual(particle.getContactForce(), nullVector3D());
	checkEqual(particle.getResultingForce(), bodyForce1);

	Vector3D bodyForce2(-9.81, 5.5, 1.618);
	particle.addBodyForce(bodyForce2);
	checkEqual(particle.getBodyForce(), bodyForce1 + bodyForce2);
	checkEqual(particle.getContactForce(), nullVector3D());
	checkEqual(particle.getResultingForce(), bodyForce1 + bodyForce2);

	Vector3D contactForce1(0.1, 2.3, 4.5);
	particle.addContactForce(contactForce1);
	checkEqual(particle.getBodyForce(), bodyForce1 + bodyForce2);
	checkEqual(particle.getContactForce(), contactForce1);
	checkEqual(particle.getResultingForce(), bodyForce1 + bodyForce2 + contactForce1);

	Vector3D contactForce2(-4.5, 11.1, 10000);
	particle.addContactForce(contactForce2);
	checkEqual(particle.getBodyForce(), bodyForce1 + bodyForce2);
	checkEqual(particle.getContactForce(), contactForce1 + contactForce2);
	checkEqual(particle.getResultingForce(), bodyForce1 + bodyForce2 + contactForce1 + contactForce2);

	Vector3D bodyForce3(8.9, -6.5, 0);
	Vector3D contactForce3(0, 0, 7);
	particle.setBodyForce(bodyForce3);
	particle.setContactForce(contactForce3);
	checkEqual(particle.getBodyForce(), bodyForce3);
	checkEqual(particle.getContactForce(), contactForce3);
	checkEqual(particle.getResultingForce(), bodyForce3 + contactForce3);

	Vector3D torque1(-1, 0.5, 6.9);
	particle.addTorque(torque1);
	checkEqual(particle.getResultingTorque(), torque1);

	Vector3D torque2(99, 66, 33);
	particle.addTorque(torque2);
	checkEqual(particle.getResultingTorque(), torque1 + torque2);

	Vector3D torque3(-9, 0.45, 3.14159);
	particle.setResultingTorque(torque3);
	checkEqual(particle.getResultingTorque(), torque3);
}

TestCase(ParticleMomentumAndEnergyTest)
{
	double tolerance = 1e-12;

	double mass = 55;
	double momentOfInertia = 78.56;

	Vector3D position(8.8, -5.7, 0.23);
	Vector3D velocity(1.5, -4.8, 9.9);
	Vector3D angularVelocity(8.9, 7.7, -11.1);

	Vector3D linearMomentum = mass * velocity;
	Vector3D angularMomentum = mass * cross( position, velocity ) + momentOfInertia * angularVelocity;

	double translationalEnergy = 0.5 * mass * velocity.squaredLength();
	double rotationalEnergy = 0.5 * momentOfInertia * angularVelocity.squaredLength();
	double kineticEnergy = translationalEnergy + rotationalEnergy;

	Particle<> particle;

	particle.set<Mass>(mass);
	particle.set<MomentOfInertia>(momentOfInertia);

	particle.setPosition(position);
	particle.setVelocity(velocity);
	particle.setAngularVelocity(angularVelocity);

	checkEqual(particle.getLinearMomentum(), linearMomentum);
	checkEqual(particle.getAngularMomentum(), angularMomentum);
	checkClose(particle.getKineticEnergy(), kineticEnergy, tolerance);
	checkClose(particle.getTranslationalEnergy(), translationalEnergy, tolerance);
	checkClose(particle.getRotationalEnergy(), rotationalEnergy, tolerance);
}

TestCase(json_Particle_Test)
{
	json j{
		{"Name", "Tarintor"},
		{"Mass", 3791},
		{"Position", 
			{{1.0, 2.0, 3.0},
			{4.0, 5.0, 6.0},
			{7.0, 8.0, 9.0},
			{10.0, 11.0, 12.0}}
		},
		{"Orientation", 
			{{-10.0, -11.0, -12.0},
			{7.0, 8.0, 9.0},
			{-4.0, -5.0, -6.0},
			{1.0, 2.0, 3.0}}
		}
	};

	std::vector<Vector3D> position{
		{1.0, 2.0, 3.0},
		{4.0, 5.0, 6.0}, 
		{7.0, 8.0, 9.0},
		{10.0, 11.0, 12.0}
	};

	std::vector<Vector3D> orientation{
		{-10.0, -11.0, -12.0},
		{7.0, 8.0, 9.0},
		{-4.0, -5.0, -6.0}, 
		{1.0, 2.0, 3.0}
	};

	Particle<> p = j;

	checkEqual(p.getPositionMatrix(), position);
	checkEqual(p.getOrientationMatrix(), orientation);
	checkEqual(p.getName(), "Tarintor");
	checkEqual(p.get<Mass>(), 3791);

	json j2 = p;

	json j3 = merge(
			j,
			json{
				{"bodyForce", {0, 0, 0}},
				{"contactForce", {0, 0, 0}},
				{"resultingTorque", {0, 0, 0}}
			}
		);

	checkEqual(j2, j3);
}

TestCase(SphericalParticleConstructorsTest)
{
	// Default constructor
	{
		SphericalParticle<> sph;

		checkEqual(sph.getName(), Named::defaultName);
		checkEqual(sph.getTaylorOrder(), DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
	}

	// Constructor with parameters
	{	
		string name = "Tarintor";
		int taylorOrder = 4;

		SphericalParticle<> sph(name, taylorOrder);

		checkEqual(sph.getName(), name);
		checkEqual(sph.getTaylorOrder(), taylorOrder);
	}
	
	// Constructor with base particle
	{
		string name = "Tarintor";
		int taylorOrder = 4;
		
		Particle<Radius> particle(name, taylorOrder);
		Vector3D position(1.1, 2.5, 9.7);

		particle.setPosition(position);

		SphericalParticle<> sph(particle);

		checkEqual(sph.getName(), name);
		checkEqual(sph.getTaylorOrder(), taylorOrder);
		checkEqual(sph.getPosition(), position);
	}
}

TestCase(SphericalParticle_relativeTangentialVelocity_Test)
{
	{	// Calculate using random numbers
		SphericalParticle<> sph0;
		SphericalParticle<> sph1;

		Vector3D position0(1.5, 0.8, 8.7);
		Vector3D position1(-8.5, 7.5, 0.84);

		Vector3D velocity0(8.99, 7.88, 5.64);
		Vector3D velocity1(0.25, 22.7, 9.78);

		Vector3D angularVelocity0(3.15, 7.89, -98.55);
		Vector3D angularVelocity1(6.52, -8.74, -0.25);

		double radius0 = 0.6 * distance(position0, position1);
		double radius1 = 0.5 * distance(position0, position1);

		sph0.set<Radius>(radius0);
		sph1.set<Radius>(radius1);

		sph0.setPosition(position0);
		sph1.setPosition(position1);

		sph0.setVelocity(velocity0);
		sph1.setVelocity(velocity1);

		sph0.setAngularVelocity(angularVelocity0);
		sph1.setAngularVelocity(angularVelocity1);

		Vector3D normalVersor = (position1 - position0).normalized();
		Vector3D velocityDifference = velocity1 - velocity0;

		Vector3D contact = contactPoint(sph0, sph1);

		Vector3D relativeTangentialCenterVelocity = velocityDifference - dot(velocityDifference, normalVersor) * normalVersor;
		Vector3D relativeTangentialRotationalVelocity = cross(angularVelocity1, contact - position1) - cross(angularVelocity0, contact - position0);

		Vector3D relativeTangentialVelocity = relativeTangentialCenterVelocity + relativeTangentialRotationalVelocity;

		checkEqual(sph0.relativeTangentialVelocity(sph1), relativeTangentialVelocity);
	}

	{	// Intuitive case
		SphericalParticle<> sph0;
		SphericalParticle<> sph1;
		SphericalParticle<> sph2;

		double radius0 = 1.0;
		double radius1 = 1.0;
		double radius2 = 1.0;

		Vector3D position0(0.0, 0.0, 0.0);
		Vector3D position1(2.0, 0.0, 0.0);
		Vector3D position2(-2.0, 0.0, 0.0);

		Vector3D velocity0(0.0, 0.0, 0.0);
		Vector3D velocity1(0.0, 0.0, 0.0);
		Vector3D velocity2(0.0, 1.0, 0.0);

		Vector3D angularVelocity0(0.0, 0.0, 0.0);
		Vector3D angularVelocity1(0.0, 0.0, 1.0);
		Vector3D angularVelocity2(0.0, 0.0, 0.0);

		Vector3D relativeTangentialVelocity01(0.0, -1.0, 0.0);	// angularVelocity1 * radius1
		Vector3D relativeTangentialVelocity02(0.0, 1.0, 0.0);
		
		sph0.set<Radius>(radius0);
		sph1.set<Radius>(radius1);
		sph2.set<Radius>(radius2);

		sph0.setPosition(position0);
		sph1.setPosition(position1);
		sph2.setPosition(position2);
		
		sph0.setVelocity(velocity0);
		sph1.setVelocity(velocity1);
		sph2.setVelocity(velocity2);
		
		sph0.setAngularVelocity(angularVelocity0);
		sph1.setAngularVelocity(angularVelocity1);
		sph2.setAngularVelocity(angularVelocity2);

		checkEqual(sph0.relativeTangentialVelocity(sph1), relativeTangentialVelocity01);
		checkEqual(sph0.relativeTangentialVelocity(sph2), relativeTangentialVelocity02);
	}
}

TestCase(SphericalParticle_tangentialVersor_Test)
{
	{	// General case
		SphericalParticle<> sph0;
		SphericalParticle<> sph1;

		Vector3D position0(1.5, 0.8, 8.7);
		Vector3D position1(-8.5, 7.5, 0.84);

		Vector3D velocity0(8.99, 7.88, 5.64);
		Vector3D velocity1(0.25, 22.7, 9.78);

		Vector3D angularVelocity0(3.15, 7.89, -98.55);
		Vector3D angularVelocity1(6.52, -8.74, -0.25);

		double radius0 = 0.6 * distance(position0, position1);
		double radius1 = 0.5 * distance(position0, position1);
		
		sph0.set<Radius>(radius0);
		sph1.set<Radius>(radius1);

		sph0.setPosition(position0);
		sph1.setPosition(position1);
		
		sph0.setVelocity(velocity0);
		sph1.setVelocity(velocity1);
		
		sph0.setAngularVelocity(angularVelocity0);
		sph1.setAngularVelocity(angularVelocity1);

		Vector3D tangentialVersor = sph0.relativeTangentialVelocity(sph1).normalized();

		checkEqual(sph0.tangentialVersor(sph1), tangentialVersor);
	}

	{	// Intuitive case
		SphericalParticle<> sph0;
		SphericalParticle<> sph1;

		double radius0 = 1.0;
		double radius1 = 1.0;

		Vector3D position0(0.0, 0.0, 0.0);
		Vector3D position1(2.0, 0.0, 0.0);

		Vector3D velocity0(0.0, 0.0, 0.0);
		Vector3D velocity1(0.0, 0.0, 1.0);

		Vector3D angularVelocity0(0.0, 0.0, 0.0);
		Vector3D angularVelocity1(0.0, 0.0, 1.0);
		
		sph0.set<Radius>(radius0);
		sph1.set<Radius>(radius1);

		sph0.setPosition(position0);
		sph1.setPosition(position1);
		
		sph0.setVelocity(velocity0);
		sph1.setVelocity(velocity1);
		
		sph0.setAngularVelocity(angularVelocity0);
		sph1.setAngularVelocity(angularVelocity1);

		Vector3D tangentialVersor = (velocity1 - angularVelocity1*radius1).normalized();
	}
}

TestCase(is_spherical_Test)
{
	check((
			is_spherical< SphericalParticle<> >::value
		));
	check( not(
			is_spherical< Particle<Radius> >::value
		));
}

TestCase(SphericalParticleTouchTest)
{
	SphericalParticle<> sph0;
	SphericalParticle<> sph1;
	SphericalParticle<> sph2;

	Vector3D position0(0.0, 0.0, 0.0);
	Vector3D position1(0.0, 0.0, 1.0);
	Vector3D position2(1000.0, 0.0, 0.0);

	double radius0 = 0.8;
	double radius1 = 0.6;
	double radius2 = 0.5;

	sph0.setPosition(position0);
	sph1.setPosition(position1);
	sph2.setPosition(position2);

	sph0.property<Radius>().set(radius0);
	sph1.property<Radius>().set(radius1);
	sph2.property<Radius>().set(radius2);

	check(touch(sph0, sph1));
	check(!touch(sph0, sph2));
	check(!touch(sph1, sph2));
}

TestCase(SphericalParticleOverlapTest)
{
	double tolerance = 1e-12;

	SphericalParticle<> sph0;
	SphericalParticle<> sph1;

	Vector3D position0(0.0, 0.0, 0.0);
	Vector3D position1(0.0, 0.0, 1.0);

	double radius0 = 0.8;
	double radius1 = 0.6;

	sph0.setPosition(position0);
	sph1.setPosition(position1);

	sph0.property<Radius>().set(radius0);
	sph1.property<Radius>().set(radius1);

	double over = 0.4;

	checkClose(overlap(sph0, sph1), over, tolerance);
}

TestCase(SphericalParticleOverlapDerivativeTest)
{
	double tolerance = 1e-12;

	SphericalParticle<> sph0;
	SphericalParticle<> sph1;

	Vector3D position0(0.0, 0.0, 0.0);
	Vector3D position1(0.0, 0.0, 1.0);

	Vector3D velocity0(5.8, 9.7, 4.5);
	Vector3D velocity1(5.8, 9.7, 3.5);

	double radius0 = 0.8;
	double radius1 = 0.6;

	sph0.setPosition(position0);
	sph1.setPosition(position1);

	sph0.setVelocity(velocity0);
	sph1.setVelocity(velocity1);

	sph0.property<Radius>().set(radius0);
	sph1.property<Radius>().set(radius1);

	Vector3D positionDifference = position1 - position0;
	Vector3D velocityDifference = velocity1 - velocity0;
	double overlapDeriv = - dot(positionDifference, velocityDifference) / positionDifference.length();

	checkClose(overlapDerivative(sph0, sph1), overlapDeriv, tolerance);
}

TestCase(SphericalParticleContactPointTest)
{
	SphericalParticle<> sph0;
	SphericalParticle<> sph1;
	SphericalParticle<> sph2;

	Vector3D position0(0.0, 0.0, 0.0);
	Vector3D position1(1.0, 0.0, 0.0);
	Vector3D position2(2.0, 0.0, 0.0);

	double radius0 = 0.8;
	double radius1 = 0.2;
	double radius2 = 0.2;

	sph0.property<Radius>().set(radius0);
	sph1.property<Radius>().set(radius1);
	sph2.property<Radius>().set(radius2);

	sph0.setPosition(position0);
	sph1.setPosition(position1);
	sph2.setPosition(position2);

	Vector3D contact(0.8, 0.0, 0.0);

	checkEqual(contactPoint(sph0, sph1), contact);

	// Uncomment the following line to get runtime errors:
	// contactPoint(sph0, sph2);
}

TestCase(json_SphericalParticle_Test)
{
	json j{
		{"Name", "Saruman"},
		{"Mass", 3524},
		{"Radius", 7108},
		{"Position",
			{
				{0, 1, 2},
				{3, 4, 5},
				{6, 7, 8},
				{9, 10, 11}
			}
		},
		{"Orientation",
			{
				{12, 13, 14},
				{15, 16, 17},
				{-1, -2, -3},
				{-4, -5, -6}
			}
		}
	};

	SphericalParticle<> sph = j;

	checkEqual(sph.getName(), "Saruman");
	checkEqual(sph.get<Mass>(), 3524);
	checkEqual(sph.get<Radius>(), 7108);
	checkEqual(sph.getPosition(), Vector3D(0, 1, 2));
	checkEqual(sph.getOrientation(), Vector3D(12, 13, 14));

	json j2 = sph;

	json j3 = merge(
			j,
			json{
				{"bodyForce", {0, 0, 0}},
				{"contactForce", {0, 0, 0}},
				{"resultingTorque", {0, 0, 0}}
			}
		);

	checkEqual(j2, j3);
}

TestCase(Boundary_Test)
{
	PhysicalEntity<Mass, Volume> physical;
	physical.set<Mass>(18.5);
	physical.set<Volume>(5.2);
	Boundary<Mass, Volume> boundary(Named("Boundary"), physical);
	checkEqual(boundary.getName(), "Boundary");
	checkEqual(boundary.get<Mass>(), 18.5);
	checkEqual(boundary.get<Volume>(), 5.2);
}

TestCase(FixedBoundary_Test)
{
	PhysicalEntity<Mass, Volume> physical;
	physical.set<Mass>(18.5);
	physical.set<Volume>(5.2);
	Boundary<Mass, Volume> boundary(Named("Fixed"), physical);
	FixedBoundary<Mass, Volume> fixed(boundary);
	fixed.update(3.141592);
	checkEqual(fixed.getName(), "Fixed");
	checkEqual(fixed.get<Mass>(), 18.5);
	checkEqual(fixed.get<Volume>(), 5.2);
}

TestCase(FixedInfinitePlaneTest)
{
	Vector3D origin1(1.0, 2.0, 3.0);
	Vector3D normalVector1(1.0, 1.0, 0.0);

	Vector3D origin2(-1.0, -1.0, -1.0);
	Vector3D vector1(5.0, 6.9, 7.8);
	Vector3D vector2(500, -9.5, 13.6);
	Vector3D vector3 = cross(vector1, vector2);
	double coefficient1 = 4.562;
	double coefficient2 = -560.82;

	FixedInfinitePlane<> plane1(origin1, normalVector1);
	checkEqual(plane1.getNormalVersor(), normalVector1.normalized());

	FixedInfinitePlane<> plane2 = FixedInfinitePlane<>::buildFromOriginAndTwoVectors(origin2, vector1, vector2);
	check(plane2.containsVector(vector1));
	check(plane2.containsVector(vector2));
	check(plane2.containsVector(coefficient1*vector1 + coefficient2*vector2));

	FixedInfinitePlane<> plane3 = FixedInfinitePlane<>::buildFromThreePoints(origin2, vector1 + origin2, vector2 + origin2);
	check( plane2 == plane3 );
}

TestCase(is_plane_Test)
{
	check(is_plane<FixedInfinitePlane<>>::value);
	check(not is_plane<SphericalParticle<>>::value);
}

TestCase(SphericalParticle_and_FixedInfinitePlane_Test)
{
	{
		Vector3D origin(0, 0, 0);
		Vector3D normalVersor(0, 1, 0);
		FixedInfinitePlane<> plane(origin, normalVersor);

		SphericalParticle<> sphere;
		sphere.set<Radius>(1);
		sphere.setPosition( Vector3D(0, 0.6, 0));
		sphere.setVelocity( Vector3D(0, -10, 0));

		check(touch(sphere, plane));
		checkEqual(overlap(sphere, plane), 0.4);
		checkEqual(overlapDerivative(sphere, plane), 10);
	}
	{
		Vector3D origin(0, 0, 0);
		Vector3D normalVersor(0, 1, 0);
		FixedInfinitePlane<> plane(origin, normalVersor);

		SphericalParticle<> sphere;
		sphere.set<Radius>(1);
		sphere.setPosition( Vector3D(0, 1.6, 0));
		sphere.setVelocity( Vector3D(0, -10, 0));

		check(not touch(sphere, plane));
		checkEqual(overlap(sphere, plane), 0);
		checkEqual(overlapDerivative(sphere, plane), 0);
	}
}