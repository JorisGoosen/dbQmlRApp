cmake_minimum_required(VERSION 3.21)

project(qmlR)
find_package(Qt6 REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui QuickControls2)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MESSAGE_CONTEXT_SHOW ON)

qt6_standard_project_setup()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_FIND_FRAMEWORK ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_VERBOSE_MAKEFILE 0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_USE_QTSVG 1)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_DLL)
add_definitions(-DRCPP_NO_SUGAR)
include_directories(${QT_INCLUDE_DIR})
link_directories(${QT_LIBRARY_DIR})

find_package(SQLite3 3.41.2 REQUIRED)


message(STATUS "Collecting R info")
execute_process(COMMAND "R RHOME" OUTPUT_VARIABLE R_HOME)
message(STATUS "R_HOME: ${R_HOME}")
set(NUM_TRUNC_CHARS 2)


execute_process(COMMAND "Rscript -e \"renv::status()\"" OUTPUT_VARIABLE RENV_STATUS)
message(STATUS "RENV_STATUS: ${RENV_STATUS}")

execute_process(COMMAND Rscript -e "renv::init(project='${CMAKE_BINARY_DIR}', force=TRUE)" OUTPUT_VARIABLE RENV_INIT_OUTPUT)
message(STATUS "Renv init tells us: ${RENV_INIT_OUTPUT}")

set(RESPIRO_SRC_LOCATION "../../respiro" CACHE STRING "Where is the respiro r package?")
execute_process(COMMAND Rscript -e "renv::install(project='${CMAKE_BINARY_DIR}', prompt=FALSE, packages='${RESPIRO_SRC_LOCATION}')" OUTPUT_VARIABLE RENV_INSTALL_OUTPUT)
message(STATUS "Renv install on ${RESPIRO_SRC_LOCATION} tells us: ${RENV_INSTALL_OUTPUT}")


execute_process(COMMAND Rscript -e "renv::install(project='${CMAKE_BINARY_DIR}', prompt=FALSE, packages=c('Rcpp', 'RInside'))" OUTPUT_VARIABLE RCPP_INSTALL_OUTPUT)
message(STATUS "Renv install Rcpp tells us: ${RCPP_INSTALL_OUTPUT}")

set(PREAMBLE_R "source('renv/activate.R');\n")

execute_process(COMMAND Rscript -e "${PREAMBLE_R} cat(find.package('Rcpp'))" OUTPUT_VARIABLE RCPP_LOCATION)
#execute_process(COMMAND "R CMD config --cppflags" OUTPUT_VARIABLE RCPPFLAGS ECHO_OUTPUT_VARIABLE)
set(RCPPFLAGS -I/Library/Frameworks/R.framework/Resources/include)
string(SUBSTRING ${RCPPFLAGS} ${NUM_TRUNC_CHARS} -1 RCPPINCLUDE)
message(STATUS "RCPPFLAGS: ${RCPPFLAGS} RCPPINCLUDE: ${RCPPINCLUDE}")
include_directories(${RCPPINCLUDE})

set(RCPPCPPFLAGS -I${RCPP_LOCATION}/include)
include_directories(${RCPP_LOCATION}/include)
message(STATUS "RCPP_LOCATION: ${RCPP_LOCATION} \nRCPPCPPFLAGS: ${RCPPCPPFLAGS}")

#execute_process(COMMAND "R CMD config --ldflags" OUTPUT_VARIABLE RLDFLAGS ECHO_OUTPUT_VARIABLE)
#string(LENGTH ${RLDFLAGS} RLDFLAGS_LEN)
#string(STRIP ${RLDFLAGS} RLDFLAGS)

set(RLDFLAGS "-L/opt/R/arm64/lib -F/Library/Frameworks/R.framework/.. -framework R -L/opt/R/arm64/lib -lbz2 -lz -licucore -ldl -lm -liconv")

execute_process(COMMAND Rscript -e "${PREAMBLE_R} RInside:::CxxFlags()" OUTPUT_VARIABLE RINSIDEINCL)

message(STATUS "RINSIDEINCL: ${RINSIDEINCL}")
string(SUBSTRING ${RINSIDEINCL} ${NUM_TRUNC_CHARS} -1 RINSIDEINCL)
include_directories(${RINSIDEINCL})

execute_process(COMMAND Rscript -e "${PREAMBLE_R} RInside:::LdFlags()" OUTPUT_VARIABLE RINSIDELIBS)
string(STRIP ${RINSIDELIBS} RINSIDELIBS )
string(REPLACE "\"" "" RINSIDELIBS ${RINSIDELIBS})

if (${RINSIDELIBS} MATCHES "[-][L]([^ ;])+")
    string(SUBSTRING ${CMAKE_MATCH_0} ${NUM_TRUNC_CHARS} -1 RINSIDELIBS_L)
    link_directories(${RINSIDELIBS_L})
endif()

if (${RINSIDELIBS} MATCHES "[-][l][R]([^;])+")
	string(SUBSTRING ${CMAKE_MATCH_0} ${NUM_TRUNC_CHARS} -1 RINSIDELIBS_l)
endif()

if (${RINSIDELIBS} MATCHES ".+\.a$")
	set(RINSIDELIBS_l ${RINSIDELIBS})
endif()

execute_process(COMMAND R CMD config CXXFLAGS    OUTPUT_VARIABLE RCXXFLAGS)
execute_process(COMMAND R CMD config BLAS_LIBS   OUTPUT_VARIABLE RBLAS)
execute_process(COMMAND R CMD config LAPACK_LIBS OUTPUT_VARIABLE RLAPACK)

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -Wextra ${CMAKE_CXX_FLAGS}")
set(CMAKE_LD_FLAGS "${RLDFLAGS}")

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR
    CMAKE_BUILD_TYPE STREQUAL "RelWithDebugInfo" )
    add_definitions("-DDEBUG")
elseif ( CMAKE_BUILD_TYPE STREQUAL "RELEASE" )
    add_definitions("-O3")
endif()

#Set up our actual application
set(sources
	main.cpp
	respiro.cpp
	rwrapper.cpp
	database.cpp
	settings.cpp
	mainmodel.cpp
	tablemodel.cpp
	channelconf.cpp
	plotrenderer.cpp
	columndefinition.cpp
)

set(headers
	respiro.h
	settings.h
	rwrapper.h
	database.h
	mainmodel.h
	tablemodel.h
	stringutils.h
	channelconf.h
	plotrenderer.h
	enumutilities.h
	columndefinition.h
)

qt_add_executable(qmlR ${sources} ${headers})

qt_add_qml_module(qmlR
	URI qmlRModule
	QML_FILES
	    main.qml
		Init.qml
		Data.qml
		Tafel.qml
		MyText.qml
		Loading.qml
		Hardware.qml
		LastValues.qml
		RectButton.qml
		ChannelConf.qml
		ChannelButton.qml
		HWFeedbackButton.qml
		ChannelsSelector.qml
	NO_RESOURCE_TARGET_PATH
	RESOURCES
	    dummy.png
		images/logo_biont_research.png
		images/logo_biont_research.svg
)

qt_add_resources(qmlR "R"
	PREFIX "/"
	FILES
	   R/writeImage.R
	   R/main.R
	   R/pie.R
	   R/lines.R
)


target_link_libraries(
	qmlR
	PRIVATE
	Qt6::Core
	Qt6::Quick
	Qt6::QuickControls2
	Qt6::Gui
	${BLAS_LIBS}
	${LAPACK_LIBS}
	${RINSIDELIBS_l}
	${RLDFLAGS}
	SQLite::SQLite3
)
