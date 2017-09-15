#ifndef SIMULATION_TPP
#define SIMULATION_TPP

// JSONLib
#include <json.hpp>

// SimulationLib
#include <CommandLineParser.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <mp/visit.hpp>

// Standard
#include <fstream>

namespace psin {

template<typename>
struct Builder;

namespace detail {

template<typename I>
struct conditionally_build_interaction
{
	static void call(const std::string & interactionName, const std::string & filepath)
	{
		if( NamedType<I>::name == interactionName )
		{
			json j = read_json(filepath);

			Builder<I>::build(j.at(NamedType<I>::name));
		}
	}
};

template<typename PVector>
struct conditionally_build_particle
{
	using P = typename PVector::value_type;

	template<typename ParticleTuple>
	static void call(const std::string & particleType, const std::string & filepath, ParticleTuple & particles)
	{
		if( NamedType<P>::name == particleType)
		{
			json j = read_json(filepath);

			P particle = j;

			std::get<PVector>(particles).insert( particle );
		}
	}
};

} // detail

template<
	typename ... ParticleTypes,
	typename ... InteractionTypes
>
void Simulation<
	ParticleList<ParticleTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::setup(int argc, char * argv[])
{
	fileTree["Input"]["Main"] = CommandLineParser::parseArgvIntoSimulationPath(argc, argv);

	json j = read_json(simulationPath);

	this->initialTime = j["initialTime"];
	this->timeStep = j["timeStep"];
	this->finalTime = j["finalTime"];
	this->taylorOrder = j["taylorOrder"];
	this->dimension = j["dimension"];
	this->timeStepsForOutput = j["timeStepsForOutput"];

	json interactions = j["interactions"];
	for(json::iterator it = interactions.begin(); it != interactions.end(); ++it) 
	{
		interactionsToUse.insert( it.key() );
		mp::visit<InteractionList, detail::conditionally_build_interaction>::call_same(it.key(), it.value());
	}

	json particles = j["particles"];
	for(json::iterator it = particles.begin(); it != particles.end(); ++it) 
	{
		mp::visit<ParticleList, detail::conditionally_build_particle>::call_same(it.key(), it.value(), particles);
	}
}

template<
	typename ... ParticleTypes,
	typename ... InteractionTypes
>
void Simulation<
	ParticleList<ParticleTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::simulate()
{
	
}

template<
	typename ... ParticleTypes,
	typename ... InteractionTypes
>
template<typename I>
bool Simulation<
	ParticleList<ParticleTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::useInteraction()
{
	return interactionsToUse.count(NamedType<I>::name) > 0;
}

} // psin

#endif // SIMULATION_TPP
