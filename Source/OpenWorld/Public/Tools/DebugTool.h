// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR
#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "string"
#endif

#pragma region LogValue

// Check if T override ToString() method
template <typename T, typename = void>
struct THasToString : std::false_type {};

template <typename T>
struct THasToString<T, std::void_t<decltype(std::declval<T>().ToString())>> : std::true_type {};

#if WITH_EDITOR
	// Case: T has ToString() method
	template<typename T>
	std::enable_if_t<THasToString<T>::value, void>
	LogValue(const T& Value, const FString& Identifier = "")
	{
		const FString OutputString = Value.ToString();
		UE_LOG(LogTemp, Log, TEXT("%s: %s"), *Identifier, *OutputString);
	}

	// Case: No ToString() method, can cast to std::string type
	template<typename T>
	std::enable_if_t<!THasToString<T>::value && std::is_convertible_v<T, std::string>, void>
	LogValue(const T& Value, const FString& Identifier = "")
	{
		const FString OutputString = static_cast<std::string>(Value);
		UE_LOG(LogTemp, Log, TEXT("%s: %s"), *Identifier, *OutputString);
	}

	// Case: No ToString() method, arithmetic type
	template<typename T>
	std::enable_if_t<!THasToString<T>::value && std::is_arithmetic_v<T>, void>
	LogValue(const T& Value, const FString& Identifier = "")
	{
		UE_LOG(LogTemp, Log, TEXT("%s: %f"), *Identifier, static_cast<double>(Value));
	}

	// Case: No ToString() method, below 4 overloads support char array or const char*
	inline void LogValue(const char* Value, const FString& Identifier = "")
	{
		UE_LOG(LogTemp, Log, TEXT("%s: %hs"), *Identifier, Value);
	}

	template<size_t N>
	void LogValue(const char (&Value)[N], const FString& Identifier = "")
	{
		UE_LOG(LogTemp, Log, TEXT("%s: %hs"), *Identifier, Value);
	}

	inline void LogValue(const wchar_t* Value, const FString& Identifier = "")
	{
		UE_LOG(LogTemp, Log, TEXT("%s: %ls"), *Identifier, Value);
	}

	template<size_t N>
	void LogValue(const wchar_t (&Value)[N], const FString& Identifier = "")
	{
		UE_LOG(LogTemp, Log, TEXT("%s: %ls"), *Identifier, Value);
	}

	// Case: Cannot use LogValue, Log Warning
	template<typename T>
	std::enable_if_t<!THasToString<T>::value && !std::is_arithmetic_v<T>
		&& !std::is_same_v<T, const char*> && !std::is_same_v<T, const wchar_t*>, void>
	LogValue(const T& Value, const FString& Identifier = "")
	{
		const FString OutputString = TEXT("LogValue not supported");
		UE_LOG(LogTemp, Warning, TEXT("%s: %s, type: %hs"), *Identifier, *OutputString, typeid(T).name());
	}
#else
	template<typename T>
	void LogValue(const T&, const Fstring&)
	{
		
	}
#endif

#pragma endregion LogValue