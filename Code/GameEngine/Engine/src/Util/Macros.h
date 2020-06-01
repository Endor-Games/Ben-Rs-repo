#pragma once

#include <memory>

// ==========================================================================
// System
// ==========================================================================
#ifdef ENGINE_DEBUG
#define ENGINE_ENABLE_ASSERTS
#endif

#ifdef ENGINE_ENABLE_ASSERTS
#define ENGINE_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GLCORE_ASSERT(x, ...)
#endif

// ==========================================================================
// Logging
// ==========================================================================
#define LOG_TRACE(...)         Engine::Log::Get()->trace(__VA_ARGS__)
#define LOG_INFO(...)          Engine::Log::Get()->info(__VA_ARGS__)
#define LOG_WARN(...)          Engine::Log::Get()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         Engine::Log::Get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      Engine::Log::Get()->critical(__VA_ARGS__)

// ==========================================================================
// Events
// ==========================================================================
#define ENGINE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
