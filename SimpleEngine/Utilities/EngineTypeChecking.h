//
// Created by Vlad Boroday on 2023-04-20.
//

#pragma once

#include <utility>

template<typename T, typename = void>
static constexpr bool HasCreatedMethod()
{
	return false;
}

template<typename T>
static constexpr bool HasCreatedMethod(T*, decltype(std::declval<T>().OnCreated())* = nullptr)
{
	return true;
}


template<typename T, typename = void>
static constexpr bool HasUpdateMethod()
{
	return false;
}

template<typename T>
static constexpr bool HasUpdateMethod(T*, decltype(std::declval<T>().OnUpdate(0.0f))* = nullptr)
{
	return true;
}


template<typename T, typename = void>
static constexpr bool HasOnDestroyMethod()
{
	return false;
}

template<typename T>
static constexpr bool HasOnDestroyMethod(T*, decltype(std::declval<T>().OnEnable())* = nullptr)
{
	return true;
}


template<typename T, typename = void>
struct HasEmptyConstructor : std::false_type
{
};
template<typename T>
struct HasEmptyConstructor<T, std::enable_if_t<std::is_default_constructible_v<T>>> : std::true_type
{
};


