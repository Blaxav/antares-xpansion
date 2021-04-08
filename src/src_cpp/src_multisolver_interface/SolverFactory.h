#pragma once

#include "SolverAbstract.h"
#ifdef CPLEX
#include "SolverCplex.h"
#endif
#ifdef XPRESS
#include "SolverXpress.h"
#endif
#ifdef CLP_CBC
#include "SolverCbc.h"
#include "SolverClp.h"
#endif

/*!
* \class class SolverFactory
* \brief Class to manage the creation of solvers from the different implementations
*/
class SolverFactory {
public:

    std::vector<std::string> _available_solvers;

public:
    /**
    * @brief Constructor of SolverFactory, fills the list of available solvers
    */
    SolverFactory();

public:
    /**
    * @brief Creates and returns to an object solver from the wanted implementation
    *
    * @param solver_name : Name of the solver to use
    */
    SolverAbstract::Ptr create_solver(const std::string solver_name);

    /**
    * @brief Returns a reference to the list of available solvers
    */
    const std::vector<std::string>& get_solvers_list() const;
};