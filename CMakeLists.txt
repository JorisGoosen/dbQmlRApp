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

find_package(SQLite3 3.39.5 REQUIRED)

if (WIN32)
    set(ENV{PATH} "C:\\Program Files\\R\\R-4.3.1\\bin\\x64;$ENV{PATH}")
endif()

message(STATUS "Collecting R info")
execute_process(COMMAND R RHOME OUTPUT_VARIABLE R_HOME)

message(STATUS "R Home is: ${R_HOME}")

set(NUM_TRUNC_CHARS 2)

execute_process(COMMAND Rscript CMAKE_SOURCE_DIR/R/main.R)

execute_process(COMMAND R CMD config --cppflags OUTPUT_VARIABLE RCPPFLAGS)
separate_arguments(RCPPFLAGS UNIX_COMMAND ${RCPPFLAGS})

message(STATUS "RCPPFLAGS=${RCPPFLAGS}")
foreach(RCPPFLAG IN LISTS RCPPFLAGS)
    message(STATUS "RCPPFLAG=${RCPPFLAG}")
    string(SUBSTRING ${RCPPFLAG} ${NUM_TRUNC_CHARS} -1 RCPPFLAG)
    list(APPEND RCPP_INCLUDE_DIRS ${RCPPFLAG})
endforeach()
message(STATUS "RCPP_INCLUDE_DIRS=${RCPP_INCLUDE_DIRS}")
include_directories(${RCPP_INCLUDE_DIRS})

execute_process(COMMAND R CMD config --ldflags OUTPUT_VARIABLE RLDFLAGS)
string(LENGTH ${RLDFLAGS} RLDFLAGS_LEN)
string(STRIP ${RLDFLAGS} RLDFLAGS)
message(STATUS "RLDFLAGS=${RLDFLAGS}")

execute_process(COMMAND Rscript -e "Rcpp:::CxxFlags()" OUTPUT_VARIABLE RCPPINCL)
string(SUBSTRING ${RCPPINCL} ${NUM_TRUNC_CHARS} -1 RCPPINCL)
string(REPLACE "\"" "" RCPPINCL ${RCPPINCL}) #Rcpp::CxxFlags() adds quotes around the include directory, which is friendly and all but breaks include_directories
include_directories(${RCPPINCL})
message(STATUS "RCPPINCL=${RCPPINCL}")

execute_process(COMMAND Rscript -e "Rcpp:::LdFlags()" OUTPUT_VARIABLE RCPPLIBS)
if (${RCPPLIBS} MATCHES "[-][L]([^ ;])+")
    string(SUBSTRING ${CMAKE_MATCH_0} ${NUM_TRUNC_CHARS} -1 RCPPLIBS_L)
    link_directories(${RCPPLIBS_L} )
    message(STATUS "RCPPLIBS_L=${RCPPLIBS_L}")
endif()

if (${RCPPLIBS} MATCHES "[-][l][R]([^;])+")
    string(SUBSTRING ${CMAKE_MATCH_0} ${NUM_TRUNC_CHARS} -1 RCPPLIBS_l)
endif()

message(STATUS "RCPPLIBS_l=${RCPPLIBS_l}")

execute_process(COMMAND Rscript -e "RInside:::CxxFlags()"
                OUTPUT_VARIABLE RINSIDEINCL)
string(SUBSTRING ${RINSIDEINCL} ${NUM_TRUNC_CHARS} -1 RINSIDEINCL)
include_directories(${RINSIDEINCL})

execute_process(COMMAND Rscript -e "RInside:::LdFlags()" OUTPUT_VARIABLE RINSIDELIBS)
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

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -Wextra ${CMAKE_CXX_FLAGS}")# -static-libgcc -static-libstdc++") #

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR
    CMAKE_BUILD_TYPE STREQUAL "RelWithDebugInfo" )
    add_definitions("-DDEBUG")
elseif ( CMAKE_BUILD_TYPE STREQUAL "RELEASE" )
    add_definitions("-O3")
endif()

set(sources
	main.cpp
	labels.cpp
	rwrapper.cpp
	database.cpp
	importer.cpp
	settings.cpp
	mainmodel.cpp
	tablemodel.cpp
	plotrenderer.cpp
	plotrenderers.cpp
	filterlistmodel.cpp
	columndefinition.cpp
  	tablemodelfiltered.cpp
	schoolscannertable.cpp
	schoolscannerdefinities.cpp
	abstractsizeprovidertable.cpp
)

set(headers
	labels.h
	settings.h
	rwrapper.h
	database.h
	importer.h
	mainmodel.h
	tablemodel.h
	stringutils.h
	plotrenderer.h
	plotrenderers.h
	enumutilities.h
	filterlistmodel.h
	columndefinition.h
        tablemodelfiltered.h
	schoolscannertable.h
	schoolscannerdefinities.h
	abstractsizeprovidertable.h
)

qt_add_executable(
    qmlR
    ${sources}
    ${headers}
)

qt_add_qml_module(qmlR
	URI qmlRModule
	QML_FILES
            main.qml
            Data.qml
            Plots.qml
            Tafel.qml
            Welkom.qml
            Filter.qml
            Import.qml
            Analyse.qml
            PlotsHori.qml
			Scrollbalk.qml
            RectButton.qml
            MyCheckBox.qml
            FilterList.qml
            PlotFilters.qml
            MyTabButton.qml
            FileBrowser.qml
            FilteredData.qml
	NO_RESOURCE_TARGET_PATH
	QML_FILES
#    RESOURCES
#        img/world.png
)

qt_add_resources(qmlR "R"
	PREFIX "/"
	FILES
	   R/writeImage.R
	   R/main.R
	   R/plot.R
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
	${RCPPLIBS_l}
	${RINSIDELIBS_l}
	${RLDFLAGS}
	SQLite::SQLite3
)

install(
	TARGETS qmlR
	BUNDLE DESTINATION .
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_qml_app_script(
	TARGET qmlR
	OUTPUT_SCRIPT deploy_script
	NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

qt_finalize_project()
