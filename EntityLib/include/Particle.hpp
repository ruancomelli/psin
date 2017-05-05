#ifndef PARTICLE_HPP
#define PARTICLE_HPP

// EntityLib
#include <PhysicalEntity.hpp>
#include <SocialEntity.hpp>
#include <SpatialEntity.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

template<typename ... PropertyTypes>
class Particle :
	public PhysicalEntity<PropertyDefinitions::Mass, PropertyDefinitions::MomentOfInertia, PropertyTypes...>,
	public SocialEntity,
	public SpatialEntity
{
	using BasePhysicalEntity = PhysicalEntity<PropertyDefinitions::Mass, PropertyDefinitions::MomentOfInertia, PropertyTypes...>;

	public:	
		// ---- Constructors ----
		explicit Particle(const int handle = DEFAULT_HANDLED_ENTITY_HANDLE, const int taylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
		explicit Particle(const BasePhysicalEntity & base, const int handle = DEFAULT_HANDLED_ENTITY_HANDLE, const int taylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
		
		// ---- Dynamics ----
		void addBodyForce(const Vector3D & force);
		void addContactForce(const Vector3D & force);
		void setBodyForce(const Vector3D & force);
		void setContactForce(const Vector3D & force);

		Vector3D getBodyForce(void) const;
		Vector3D getContactForce(void) const;
		Vector3D getResultingForce(void) const;
		
		void addTorque(const Vector3D & torque);
		void setResultingTorque(const Vector3D & torque);
		Vector3D getResultingTorque(void) const;

		Vector3D getLinearMomentum(void) const;
		Vector3D getAngularMomentum(void) const;

		double getKineticEnergy(void) const;
		double getTranslationalEnergy(void) const;
		double getRotationalEnergy(void) const;
		double getPotentialEnergy(void) const;
		double getMechanicalEnergy(void) const;

		void setGravity(const Vector3D & gravity);
		Vector3D getGravity(void) const;	
		
	private:
		Vector3D bodyForce;
		Vector3D contactForce;

		Vector3D resultingTorque;

		static Vector3D gravity;
};

#include <Particle.tpp>

#endif
