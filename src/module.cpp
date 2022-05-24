#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include "reorient_facets.h"

namespace py = pybind11;

auto py_reorient_facets(
    const Eigen::MatrixXd &V,
    const Eigen::MatrixXi &F,
    int rays_total,
    int rays_minimum,
    bool facet_wise,
    bool use_parity,
    bool is_verbose)
{

  Eigen::MatrixXi FF;
  Eigen::VectorXi I;
  Eigen::VectorXi C;
  reorient_facets(V,F,rays_total,rays_minimum,facet_wise,use_parity,is_verbose,FF,I,C);
  return py::make_tuple(FF,I,C);
}

PYBIND11_MODULE(reorient_facets, m) {
  m.def("reorient_facets", &py_reorient_facets,"reorient_facets",
    py::arg("V"),
    py::arg("F"),
    py::arg("rays_total")=0,
    py::arg("rays_minimum")=10,
    py::arg("facet_wise")=false,
    py::arg("use_parity")=false,
    py::arg("is_verbose")=false);
}
