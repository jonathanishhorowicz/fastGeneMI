#ifndef __FAST_MINET__
#define __FAST_MINET__

#define _USE_MATH_DEFINES

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <utility> 

#include <omp.h>
// [[Rcpp::plugins(openmp)]]
#include <unistd.h>

using namespace Rcpp;

// In disc_mi_estimators.cpp
arma::mat mim_ML_cpp(NumericMatrix disc_expr_data);
arma::mat mim_MM_cpp(NumericMatrix disc_expr_data);
arma::mat mim_CS_cpp(NumericMatrix disc_expr_data);
arma::mat mim_shrink_cpp(NumericMatrix disc_expr_data);

// In jackknife.cpp
arma::vec remove_sample_marg(const arma::vec& p_marg, const int n_samples, const int sample_val);
arma::mat remove_sample_joint(const arma::mat& p_joint, const int n_samples,
                              const int sample_val_i, const int sample_val_j);
arma::mat mim_JK_cpp(NumericMatrix disc_expr_data);

// In bayesian_blocks.cpp
arma::vec fitness(const arma::uvec& N_k, const arma::vec& T_k);
double prior(const int N, const int Ntot);
arma::vec get_bb_bin_edges(const arma::vec& expr_prof);
arma::Mat<int> disc_dataset_bb_cpp(NumericMatrix expr_data);
arma::vec get_bb_bin_edges_cpp(NumericVector expr_prof);

// In emprical_dist_getters.cpp
arma::vec get_emp_marg_dist(const arma::Mat<int>& disc_data);
arma::mat get_emp_joint_dist(const arma::Mat<int>& disc_data_col_i, const arma::Mat<int>& disc_data_col_j);

// In bspline_mi.cpp
arma::mat mim_bspline_cpp(NumericMatrix expr_data, const int order, NumericVector nbins);

class Bspline {
  
public:
  Bspline(const int k_, const int n_bins_, const arma::vec& x_, const arma::vec& t_);
  void print() const;
  inline arma::sp_mat compute_bspl_coeffs();
  
private:
  int n_bins, k, n_pts; // # bins and spline order
  arma::vec x, z, t; // Points at which to evaluate and knot vector
  double tmax;
  
  // arma::vec get_knots(const int k, const int n_bins);
  
  // Basis
  arma::vec basis0(const double zi) const;
  arma::vec basis(const double zi, const int p) const;
};

// In util_funcs.cpp
arma::mat R2armaMat_num(NumericMatrix rMat);
arma::vec R2armaVec_num(NumericVector rVec);
int rNumVec2int(NumericVector rVec);
double get_marginal_ml_entropy(const arma::vec& p_marg);
double get_joint_ml_entropy(const arma::mat& p_joint);
int get_n_gene_pairs(const int n_genes);
arma::Mat<int> get_idx_lookup_mat(const int n_genes);
std::vector<std::pair <int,int> > get_ij_list(const int n_genes);

# endif // __FAST_MINET__
