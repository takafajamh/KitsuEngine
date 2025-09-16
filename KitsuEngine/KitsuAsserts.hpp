#pragma once
#include <assert.h>
#include <spdlog/spdlog.h>


// ResourceFoundLevelAssertions - assertions for when resources, assets were not found
// acquisition_assert(x, path, errorM) - for trying to get a file
// kitsu_assert(x, name, errorM, successM)
// kitsu_return_assert(x, name, errorM, successM, val) return a value

// Legend for levels
// 0 - no log
// 1 - log error, continue
// 2 - log error, log success, continue
// 3 - log error, assert
// 4 - log error, log success, assert

#define ResourceFoundLevelAssertions 3	// for acquisition_assert
#define AssertLevel 3					// for kitsu_assert
#define ReturnAssertLevel 3				// for kitsu_return_assert

#if AssertLevel == 0
	#define kitsu_assert(x, message, ...) x
#endif

#if AssertLevel == 1
	#define kitsu_assert(x, message, success, ...) if(!x) { spdlog::error(message, ##__VA_ARGS__); }
#endif

#if AssertLevel == 2
	#define kitsu_assert(x, message, success, ...) if(!x) { spdlog::error(message, ##__VA_ARGS__); } else {spdlog::info(success, ##__VA_ARGS__);}
#endif

#if AssertLevel == 3
	#define kitsu_assert(x, message,success, ...) if(!x) { spdlog::critical(message, ##__VA_ARGS__); assert(x); }
#endif

#if AssertLevel == 4
	#define kitsu_assert(x, message, success, ...) if(!x) { spdlog::critical(message, ##__VA_ARGS__); assert(x);} else {spdlog::info(success, ##__VA_ARGS__);}
#endif


#if ResourceFoundLevelAssertions == 0
	#define acquisition_assert(x, name, errorM) x
#endif 

#if ResourceFoundLevelAssertions == 1
	#define acquisition_assert(x, name, errorM) if{ (!x) spdlog::error("Resource from {} has not been found: {}", name, errorM); }
#endif

#if ResourceFoundLevelAssertions == 2
	#define acquisition_assert(x, name, errorM) if (!x){ spdlog::error("Resource from {} has not been found: {}", name, errorM);} else {spdlog::info("Resource - {} - acquired correctly", name);}
#endif

#if ResourceFoundLevelAssertions == 3
	#define acquisition_assert(x, name, errorM) if (!x){ spdlog::critical("Resource from {} has not been found: {}", name, errorM); assert(!x);}
#endif

#if ResourceFoundLevelAssertions == 4
	#define acquisition_assert(x, name, errorM) if (!x) {spdlog::critical("Resource from {} has not been found: {}", name, errorM); assert(!x);} else {spdlog::info("Resource - {} - acquired correctly", name);}
#endif


#if ReturnAssertLevel == 0
	#define kitsu_return_assert(x, message, ...) x
#endif

#if ReturnAssertLevel == 1
	#define kitsu_return_assert(x, message,success, val, ...) if(!x) { spdlog::error(message, ##__VA_ARGS__); return val;}
#endif

#if ReturnAssertLevel == 2
	#define kitsu_return_assert(x, message, success, val, ...) if(!x) { spdlog::error(message, ##__VA_ARGS__); return val; } else {spdlog::info(success, ##__VA_ARGS__);}
#endif

#if ReturnAssertLevel == 3
	#define kitsu_return_assert(x, message, success, val, ...) if(!x) { spdlog::critical(message, ##__VA_ARGS__); assert(x); return val;}
#endif

#if ReturnAssertLevel == 4
	#define kitsu_return_assert(x, message, success, val, ...) if(!x) { spdlog::critical(message, ##__VA_ARGS__); assert(x); return val;} else {spdlog::info(success, ##__VA_ARGS__);}
#endif
