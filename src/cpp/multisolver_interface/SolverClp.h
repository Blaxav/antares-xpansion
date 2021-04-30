#pragma once

#include "SolverAbstract.h"
#include "ClpSimplex.hpp"

#include "CoinHelperFunctions.hpp"
#include "CoinIndexedVector.hpp"

enum CLP_STATUS {
	CLP_OPTIMAL,
	CLP_PRIMAL_INFEASIBLE,
	CLP_DUAL_INFEASIBLE,
	CLP_STOPPED,
	CLP_ERRORED
};

/*!
* \class class SolverXpress
* \brief Daughter class of AsbtractSolver implementing solver XPRESS FICO
*/
class SolverClp : public SolverAbstract {

/*************************************************************************************************
----------------------------------------    ATTRIBUTES    ---------------------------------------
*************************************************************************************************/
    static int _NumberOfProblems;	/*!< Counter of the total number of Cplex problems 
                                    declared to set or end the environment */
public:
	ClpSimplex _clp;
	CoinMessageHandler _message_handler;

/*************************************************************************************************
-----------------------------------    Constructor/Desctructor    --------------------------------
*************************************************************************************************/
public:
	/**
    * @brief Default constructor of a XPRESS solver
    */
	SolverClp();

	/**
    * @brief Copy constructor of XPRESS, copy the problem toCopy in memory and name it "name"
	*
	* @param toCopy : Pointer to an AbstractSolver object, containing a CLP solver to copy
    */
	SolverClp(const SolverAbstract::Ptr toCopy);

	virtual ~SolverClp();
	virtual int get_number_of_instances();

/*************************************************************************************************
---------------------------------    Output and stream management    -----------------------------
*************************************************************************************************/


/*************************************************************************************************
------    Destruction or creation of inner strctures and datas, closing environments    ----------
*************************************************************************************************/
public:
	virtual void init() ;
    virtual void free() ;

/*************************************************************************************************
-------------------------------    Reading & Writing problems    -------------------------------
*************************************************************************************************/
public:
	virtual void write_prob(const char* name, const char* flags) const;
    virtual void read_prob(const char* prob_name, const char* flags);
    virtual void copy_prob(const SolverAbstract::Ptr fictif_solv);


/*************************************************************************************************
-----------------------    Get general informations about problem    ----------------------------
*************************************************************************************************/
public:
    virtual int  get_ncols() const;
    virtual int  get_nrows() const;
	virtual int  get_nelems() const;
    virtual int get_n_integer_vars() const;
	virtual void get_obj(double* obj, int first, int last) const;
	virtual void get_rows(int* mstart, int* mclind, double* dmatval, int size, int* nels, 
                    int first, int last) const;
	virtual void get_row_type(char* qrtype, int first, int last) const;
	virtual void get_rhs(double* rhs, int first, int last) const;
	virtual void get_rhs_range(double* range, int first, int last) const;
	virtual void get_col_type(char* coltype, int first, int last) const;
	virtual void get_lb(double* lb, int fisrt, int last) const;
    virtual void get_ub(double* ub, int fisrt, int last) const;

	virtual int get_row_index(std::string const& name) const;
	virtual int get_col_index(std::string const& name) const;
	virtual int get_row_names(int first, int last, std::vector<std::string>& names);
	virtual int get_col_names(int first, int last, std::vector<std::string>& names);

/*************************************************************************************************
------------------------------    Methods to modify problem    ----------------------------------
*************************************************************************************************/
public:
    virtual void del_rows(int first, int last);
    virtual void add_rows(int newrows, int newnz, const char* qrtype, const double* rhs, 
		            const double* range, const int* mstart, const int* mclind, 
                    const double* dmatval);
    virtual void add_cols(int newcol, int newnz, const double* objx, const int* mstart, 
                    const int* mrwind, const double* dmatval, const double* bdl, 
                    const double* bdu);
    virtual void add_name(int type, const char* cnames, int indice);
    virtual void chg_obj(int nels, const int* mindex, const double* obj);
    virtual void chg_bounds(int nbds, const int* mindex, const char* qbtype, const double* bnd);
    virtual void chg_col_type(int nels, const int* mindex, const char* qctype);
	virtual void chg_rhs(int id_row, double val);
    virtual void chg_coef(int id_row, int id_col, double val);
	virtual void chg_row_name(int id_row, std::string & name);
	virtual void chg_col_name(int id_col, std::string & name);
	
/*************************************************************************************************
-----------------------------    Methods to solve the problem    ---------------------------------
*************************************************************************************************/    
public:
    virtual void solve_lp(int& lp_status);
	virtual void solve_mip(int& lp_status);
	
/*************************************************************************************************
-------------------------    Methods to get solutions information    -----------------------------
*************************************************************************************************/
public:	
	/**
	* @brief Returns the current basis into the user�s data arrays.
	*
	* @param rstatus    : Integer array of length ROWS to the basis status of the slack, surplus or
						artifficial variable associated with each row. The status will be one of:
						0 slack, surplus or artifficial is free;
						1 slack, surplus or artifficial is basic;
						2 slack, surplus or artifficial is at upper bound;
						3 slack, surplus or artifficial is at lower bound;
						4 slack, surplus or artifficial is super basic.
						May be NULL if not required.
	* @param cstatus    : Integer array of length COLS to hold the basis status of the columns
						in the constraint matrix. The status will be one of:
						0 variable is free;
						1 variable is basic;
						2 variable is at upper bound;
						3 variable is at lower bound;
						4 variable is super basic
						May be NULL if not required.
	*/
	virtual void get_basis(int* rstatus, int* cstatus) const;
	virtual void get_mip_value(double& lb) const;
	virtual void get_lp_value(double& lb) const;
	virtual void get_simplex_ite(int& result) const;
	virtual void get_lp_sol(double* primals, double* duals, 
                    double* reduced_costs);
    virtual void get_mip_sol(double* primals);

/*************************************************************************************************
------------------------    Methods to set algorithm or logs levels    ---------------------------
*************************************************************************************************/
public:
	virtual void set_output_log_level(int loglevel);
	virtual void set_algorithm(std::string const& algo);
    virtual void set_threads(int n_threads);
	virtual void optimality_gap(double gap);
	virtual void set_simplex_iter(int iter);
};