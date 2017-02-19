#ifndef RAW_PROPERTY_H
#define RAW_PROPERTY_H

// UtilsLib
#include <SharedPointer.h>

// Standard
#include <string>

using namespace std;

template<typename...> class RawProperty;

template<typename type>
void defaultSetter(const type & value, type & destination);

template<typename type>
type defaultGetter(const type & value);

template<typename interfaceType, typename storedType>
class RawProperty<interfaceType, storedType>
{

	template<typename interfaceType, typename storedType>
	using RawPropertyPtr = SharedPointer< RawProperty<interfaceType, storedType> >;

	public:
		// Constructors
		RawProperty();
		explicit RawProperty(const string & name);
		RawProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &));

		// Set and get name
		void setName(const string & name);
		string getName(void) const;

		// Set setter and getter
		void setSetterFunction( void (*setterFunction)(const interfaceType & value, storedType & destination) );
		void setGetterFunction( interfaceType (*getterFunction)(const storedType & value) );

		void (*setter)(const interfaceType & value, storedType & destination) = NULL;
		interfaceType (*getter)(const storedType &) = NULL;

		bool isSimilarTo( const RawProperty<interfaceType, storedType> & other ) const;
		bool isSimilarTo( const RawPropertyPtr<interfaceType, storedType> & other ) const;

		bool isEqualTo( const RawProperty<interfaceType, storedType> & other ) const;
		bool isEqualTo( const RawPropertyPtr<interfaceType, storedType> & other ) const;

	private:
		string name;

}; // class RawProperty<interfaceType, storedType>

template<typename type>
class RawProperty<type> : public RawProperty<type, type>
{
	public:
		RawProperty();
		explicit RawProperty(const string & name, void (*setterFunction)(const type &, type &) = defaultSetter<type>, type (*getterFunction)(const type &) = defaultGetter<type>);
}; // class RawProperty<type, type>

template<typename interfaceType, typename storedType>
using RawPropertyPtr = SharedPointer< RawProperty<interfaceType, storedType> >;

#include <RawProperty.tpp>

#endif
