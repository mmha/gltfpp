add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json SYSTEM INTERFACE json/src)
target_compile_features(nlohmann_json INTERFACE cxx_std_11)

add_library(microsoft_gsl INTERFACE)
target_include_directories(microsoft_gsl SYSTEM INTERFACE GSL/include)

add_library(boost_outcome INTERFACE)
target_include_directories(boost_outcome SYSTEM INTERFACE "boost.outcome/include")
target_compile_definitions(boost_outcome INTERFACE BOOST_OUTCOME_ENABLE_ADVANCED)
target_compile_features(boost_outcome INTERFACE cxx_std_14)

add_library(Catch INTERFACE)
target_include_directories(Catch SYSTEM INTERFACE "Catch/include")

add_library(better_enums INTERFACE)
target_include_directories(better_enums SYSTEM INTERFACE "better-enums")
target_compile_features(better_enums INTERFACE cxx_std_11)
