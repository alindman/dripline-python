#ifndef DRIPLINE_PYBIND_SERVICE
#define DRIPLINE_PYBIND_SERVICE

#include "service.hh"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/iostream.h"

namespace dripline_pybind
{
    void export_service( pybind11::module& mod )
    {
        pybind11::class_< dripline::service, std::shared_ptr< dripline::service > >( mod, "Service", "Used to send and receive simple messages" )
            .def( pybind11::init< const scarab::param_node&,
                                   const std::string&,
                                   const std::string&,
                                   const unsigned int,
                                   const std::string&,
                                   const bool
                                   >(),
                   pybind11::call_guard<pybind11::scoped_ostream_redirect,
                   pybind11::scoped_estream_redirect>(),
                   pybind11::arg( "a_config" ) = scarab::param_node(),
                   pybind11::arg( "a_queue_name" ) = "",
                   pybind11::arg( "a_broker_address" ) = "",
                   pybind11::arg( "a_port" ) = 0,
                   pybind11::arg( "a_auth_file" ) = "",
                   pybind11::arg( "a_make_connection" ) = true
            )

            .def( "start", [](service& a_service){ py::gil_scoped_release a_release;
                          a_service.start(); }, //&dripline::service::start,
                  pybind11::call_guard<pybind11::scoped_ostream_redirect,
                          pybind11::scoped_estream_redirect>() )
            .def( "listen", &dripline::service::listen,
                  pybind11::call_guard<//pybind11::gil_scoped_release,
                          pybind11::scoped_ostream_redirect,
                          pybind11::scoped_estream_redirect>() )
            .def( "stop", &dripline::service::stop,
                    pybind11::call_guard<pybind11::scoped_ostream_redirect,
                          pybind11::scoped_estream_redirect>() )
            .def( "add_child", &dripline::service::add_child,
                    pybind11::call_guard<pybind11::scoped_ostream_redirect,
                          pybind11::scoped_estream_redirect>() )
            .def( "add_async_child", &dripline::service::add_async_child,
                    pybind11::call_guard<pybind11::scoped_ostream_redirect,
                          pybind11::scoped_estream_redirect>() )
            .def( "noisy_func", []() { pybind11::scoped_ostream_redirect stream(std::cout, pybind11::module::import("sys").attr("stdout"));})
            ;
    }
} /* namespace dripline_pybind */

#endif /* DRIPLINE_PYBIND_SERVICE */
