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
	static void call(const string & interactionName, const path & filepath)
	{
		if( NamedType<I>::name == interactionName )
		{
			json j = read_json(filepath.string());

			Builder<I>::build(j.at(NamedType<I>::name));
		}
	}
};

template<typename EntityVector>
struct conditionally_build_entity
{
	using Entity = typename EntityVector::value_type;

	template<typename ParticleTuple>
	static void call(const string & entityType, const path & filepath, ParticleTuple & entities, string & entityName)
	{
		if( NamedType<Entity>::name == entityType)
		{
			json j = read_json(filepath.string());

			Entity entity = j;

			entityName = entity.getName();
			std::get<EntityVector>(entities).insert( entity );
		}
	}
};

} // detail

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::setup(int argc, char * argv[])
{
	fileTree["input"]["main"] = CommandLineParser::parseArgvIntoSimulationPath(argc, argv);

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
		string interactionName(it.key());
		path interactionInputFilePath(it.value());

		interactionsToUse.insert( interactionName );
		mp::visit<InteractionList, detail::conditionally_build_interaction>::call_same(interactionName, interactionInputFilePath);
		fileTree["input"]["interaction"][interactionName] = interactionInputFilePath;
	}

	json particles = j["particles"];
	for(json::iterator it = particles.begin(); it != particles.end(); ++it) 
	{
		string particleType(it.key());
		string particleName;
		path particleInputFilePath(it.value());

		mp::visit<ParticleList, detail::conditionally_build_particle>::call_same(particleType, particleInputFilePath, particles, particleName);
		fileTree["input"]["entity"][particleName] = particleInputFilePath;
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
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
template<typename I>
bool Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::useInteraction()
{
	return interactionsToUse.count(NamedType<I>::name) > 0;
}

} // psin

#endif // SIMULATION_TPP
