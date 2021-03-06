#ifndef GEAR_INTEGRATOR_HPP
#define GEAR_INTEGRATOR_HPP

// JSONLib
#include <json.hpp>

// UtilsLib
#include <string.hpp>

// Standard
#include <utility>

namespace psin {
	
struct GearIntegrator
{
	template<typename Index, typename Value>
	class Time
	{
	public:
		using index_type = Index;
		using value_type = Value;
		using time_pair = std::pair<index_type, value_type>;

		Time(const value_type & initialInstant, const value_type & timeStep, const value_type & finalInstant);

		void start();
		void update();
		bool end() const;

		index_type getIndex() const;
		value_type getTimeStep() const;

		string getIndexTag() const;
		string getTimeTag() const;

		std::pair<index_type, value_type> as_pair() const;
		json as_json() const;

	private:
		index_type timeIndex;
		value_type time;

		value_type initialInstant;
		value_type timeStep;
		value_type finalInstant;
	};
};

} // psin

#include <IntegratorDefinitions/GearIntegrator.tpp>

#endif // GEAR_INTEGRATOR_HPP
