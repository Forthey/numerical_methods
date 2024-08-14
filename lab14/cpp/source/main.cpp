#include <iostream>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <main.grpc.pb.h>

#include "BoundaryProblemSolver.hpp"


double f(double x, double y, double der_y) {
    double e_x = std::exp(x);
    return (e_x + e_x * y + der_y) / (e_x + 1);
}

double c(double u, double der_u, double v, double der_v) {
    return (std::exp(1) - u - 1) / v;
}


/// \class gRPC server класс для обмена данными
class EvaluateIntegralService : public nm::EvaluateBoundary::Service {
    /// \brief функция принимает поток данных (a, b, epsilon) и возвращает поток результатов (x, y, h)
    /// \param context контекст обмена
    /// \param stream[in][out] переменная для обмена данными
    /// \return статус обработки (OK)
    grpc::Status Evaluate(
            grpc::ServerContext *context,
            grpc::ServerReaderWriter<nm::TabFuncWithH, nm::Requirements> *stream) override {
        nm::Requirements requirements;
        BoundaryProblemSolver solver(f);



        std::cout << "--- Receive calc requests ---" << std::endl;
        while (stream->Read(&requirements)) {
            std::cout << "Receive calc request" << std::endl;
            auto result = solver.solve(
                    requirements.a(), requirements.b(),
                    Vector<2>(requirements.homo_cauchy().y(), requirements.homo_cauchy().dy()),
                            Vector<2>(requirements.cauchy().y(), requirements.cauchy().dy()),
                                    c, requirements.epsilon());
            nm::TabFuncWithH tabFunc;

            for (int i = 0; i < result.tabFunc.size(); i++) {
                nm::Point* point = tabFunc.add_points();
                point->set_x(result.tabFunc[i].x);
                point->set_y(result.tabFunc[i].y);
                tabFunc.add_h(result.h[i == 0 ? 0 : i - 1]);
            }

            std::cout << "Return calc result" << std::endl;
            stream->Write(tabFunc);
        }
        return grpc::Status::OK;
    }

    /// \brief функция принимает поток данных (a, b, h0) и возвращает поток результатов (x, y)
    /// \param context контекст обмена
    /// \param stream[in][out] переменная для обмена данными
    /// \return статус обработки (OK)
    grpc::Status EvaluateConst(
            grpc::ServerContext *context,
            grpc::ServerReaderWriter<nm::TabFunc, nm::RequirementsConst> *stream) override {
        nm::RequirementsConst requirements;
        BoundaryProblemSolver solver(f);

        std::cout << "--- Receive calc requests ---" << std::endl;
        while (stream->Read(&requirements)) {
            std::cout << "Receive calc request" << std::endl;
            auto result = solver.solveConst(
                    requirements.a(), requirements.b(),
                    Vector<2>(requirements.homo_cauchy().y(), requirements.homo_cauchy().dy()),
                    Vector<2>(requirements.cauchy().y(), requirements.cauchy().dy()),
                    c, requirements.h0());
            nm::TabFunc tabFunc;
            for (auto & _point : result) {
                nm::Point* point = tabFunc.add_points();
                point->set_x(_point.x);
                point->set_y(_point.y);
            }
            std::cout << "Return calc result" << std::endl;
            stream->Write(tabFunc);
        }
        return grpc::Status::OK;
    }
};

void RunServer(uint16_t port) {
    std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
    EvaluateIntegralService service;

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
