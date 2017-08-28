#ifndef COMBINATORY_TPP
#define COMBINATORY_TPP

// UtilsLib
#include <MP/concatenate.hpp>
#include <MP/get.hpp>
#include <MP/length.hpp>
#include <MP/metafunction.hpp>
#include <MP/type_list.hpp>

// Standard
#include <utility>
#include <type_traits>

namespace traits {
	template<size_t S = 0, size_t Value = 0>
	struct make_constant_index_sequence
		: metafunction< 
			typename concatenate< 
				std::index_sequence<Value>, 
				typename make_constant_index_sequence<S-1, Value>::type 
			>::type 
		>
	{};

	template<size_t Value>
	struct make_constant_index_sequence<0, Value>
		: metafunction< std::index_sequence<> >
	{};


	template<typename Indexes, typename Limits>
	struct format_indexes_based_on_limits;

	template<template<size_t...> class List>
	struct format_indexes_based_on_limits<
		List<>,
		List<>
	> : metafunction< List<> >
	{
		constexpr static size_t remainder = 0;
	};

	template<typename T, template<typename, T...> class List>
	struct format_indexes_based_on_limits<
		List<T>,
		List<T>
	> : metafunction< List<T> >
	{
		constexpr static T remainder = 0;
	};

	template<template<size_t...> class List, 
		size_t I, 
		size_t L>
	struct format_indexes_based_on_limits<
		List<I>,
		List<L>
	> : metafunction< List<I%L> >
	{
		constexpr static size_t remainder = I/L;
	};

	template<typename T, template<typename, T...> class List, T I, T L>
	struct format_indexes_based_on_limits<
		List<T, I>,
		List<T, L>
	> : metafunction< List<T, I%L> >
	{
		constexpr static T remainder = I/L;
	};

	template<template<size_t...> class List, 
		size_t I1, size_t I2, size_t...Is, 
		size_t L1, size_t L2, size_t...Ls>
	struct format_indexes_based_on_limits<
		List<I1, I2, Is...>,
		List<L1, L2, Ls...>
	> : metafunction<
			typename concatenate< 
				List<I1%L1>,
				typename format_indexes_based_on_limits<
					List<I2 + I1/L1, Is...>,
					List<L2, Ls...>
				>::type
			>::type 
		>
	{
		constexpr static size_t remainder = format_indexes_based_on_limits<
				List<I2 + I1/L1, Is...>,
				List<L2, Ls...>
			>::remainder; 
	};

	template<typename T, template<typename, T...> class List, 
		T I1, T I2, T...Is, 
		T L1, T L2, T...Ls>
	struct format_indexes_based_on_limits<
		List<T, I1, I2, Is...>,
		List<T, L1, L2, Ls...>
	> : metafunction<
			typename concatenate< 
				List<T, I1%L1>,
				typename format_indexes_based_on_limits<
					List<T, I2 + I1/L1, Is...>,
					List<T, L2, Ls...>
				>::type
			>::type 
		>
	{
		constexpr static T remainder = format_indexes_based_on_limits<
				List<T, I2 + I1/L1, Is...>,
				List<T, L2, Ls...>
			>::remainder; 
	};


	template<typename...TypeLists>
	struct index_limit
		: metafunction< std::index_sequence< length<TypeLists>::value ... > >
	{};

	template<typename...TypeLists>
	struct last_combination_indexes
		: metafunction< std::index_sequence< length<TypeLists>::value - 1 ... > >
	{};

	template<typename Indexes, typename Limits>
	struct next_combination_indexes;

	template<size_t I, size_t...Is, typename Limits>
	struct next_combination_indexes< std::index_sequence<I, Is...>, Limits >
		: format_indexes_based_on_limits< 
			std::index_sequence<I+1, Is...>,
			Limits
		>
	{};


	template<typename Indexes, typename...TypeLists>
	struct get_combination;

	template<size_t...Is, typename...TLs>
	struct get_combination< std::index_sequence<Is...>, TLs... >
		: metafunction< type_list< typename get<Is, TLs>::type ... > >
	{};



	template<typename Indexes, typename...TLs>
	struct iterate_generate_list
		: metafunction<
			typename concatenate<
				type_list<typename get_combination<Indexes, TLs...>::type>,
				typename iterate_generate_list<
					typename next_combination_indexes<Indexes, typename index_limit<TLs...>::type>::type, 
					TLs...
				>::type
			>::type
		>
	{};

	template<typename...TLs>
	struct iterate_generate_list<
		typename last_combination_indexes<TLs...>::type,
		TLs...
	>
		: metafunction<	
			type_list<
				typename get_combination<
					typename last_combination_indexes<TLs...>::type, 
					TLs...
				>::type
			>
		>
	{};



	template<typename...TypeLists>
	struct generate_list
		: iterate_generate_list<
			typename make_constant_index_sequence<sizeof...(TypeLists), 0>::type, 
			TypeLists...
		>
	{};

} // traits

#endif // COMBINATORY_TPP