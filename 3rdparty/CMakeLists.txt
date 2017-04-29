add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json SYSTEM INTERFACE json/src)

add_library(microsoft_gsl INTERFACE)
target_include_directories(microsoft_gsl SYSTEM INTERFACE GSL/include)

add_library(boost_outcome INTERFACE)
target_include_directories(boost_outcome SYSTEM INTERFACE "boost.outcome/include")
target_compile_definitions(boost_outcome INTERFACE BOOST_OUTCOME_ENABLE_ADVANCED)
