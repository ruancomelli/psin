#ifndef ELECTROSTATIC_FORCE_HPP
#define ELECTROSTATIC_FORCE_HPP

// EntityLib
#include <PhysicalEntity.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <Builder.hpp>
#include <NamedType.hpp>
#include <mp/bool_constant.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
struct ElectrostaticForce
{
	template<typename P1, typename P2>
	struct check : mp::bool_constant<
		has_property<P1, ElectricCharge>::value
		and has_property<P2, ElectricCharge>::value
		>
	{};

	template<typename P1, typename P2>
	constexpr static bool check_v = check<P1, P2>::value;

	template<typename P1, typename P2, typename T>
	static void calculate(P1 & particle, P2 & neighbor, const T &);
};

template<>
struct Builder<ElectrostaticForce>
{
	static void setup(const json & j);
};

} // psin

#include <InteractionDefinitions/ElectrostaticForce.tpp>

#endif
