#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <main.grpc.pb.h>

#include "quadratic_spline.hpp"


/// \class Класс, обменивающийся данными с python программой
class ComputeSplineServiceImpl : public nm::ComputeSpline::Service {
    int requestCnt = 0;

    /// \brief Функция, принимающая табличные фукнции и возвращающая значение сплайнов
    /// \param context[out] контекст запроса
    /// \param request[in] табличные фукнции
    /// \param response[out] переменная для отправки значений сплайнов
    grpc::Status Evaluate(
            grpc::ServerContext* context,
            nm::TabFuncs const *request,
            grpc::ServerWriter<nm::Spline>* response) override {

        std::cout << std::endl;
        std::cout << std::string(30, '*') << std::endl;
        std::cout << ++requestCnt << std::endl;
        std::cout << "New eval request: " << request->tab_funcs_size() << " tab funcs" << std::endl;

        for (auto& tabFunc : request->tab_funcs()) {
            QuadraticSpline quadraticSpline;

            std::cout << "Register " << tabFunc.points_size() << " root tab func" << std::endl;

            for (auto& point : tabFunc.points()) {
                quadraticSpline.addPointToTabFunc(point.x(), point.y());
            }

            std::vector<QuadPoly> spline = quadraticSpline.evaluateCoefficients();
            std::vector<Point> splineValues = QuadraticSpline::getSplineValues(spline, tabFunc.expand_to());

            nm::Spline splineResponse;

            for (auto& _point : splineValues) {
                nm::Point* point = splineResponse.add_points();
                point->set_x(_point.x);
                point->set_y(_point.y);
            }

            for (auto& _basePoint : quadraticSpline.getPoints()) {
                nm::Point *basePoint = splineResponse.add_base_points();
                basePoint->set_x(_basePoint.x);
                basePoint->set_y(_basePoint.y);
            }

            response->Write(splineResponse);

            std::cout << "Return  " << tabFunc.points_size()-1 << "-poly spline" << std::endl;
        }

        return grpc::Status::OK;
    }

};

void RunServer(uint16_t port) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    ComputeSplineServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    grpc::ServerBuilder builder;

    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shut down. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}


int main() {
    RunServer(4040);
    return EXIT_SUCCESS;
}