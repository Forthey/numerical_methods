#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <main.grpc.pb.h>

#include "integral.hpp"


/// \brief Подынтегральная функция
double f(double x) {
    return (x * x * x * x - 2.9 * x * x * x + 6.5 * x * x - 7 * x - 5.4) * std::cos(2.0 * x);
}
//
///// \brief Подынтегральная функция
//double f(double x) {
//    return (x * x * x * x - 2.9 * x * x * x + 6.5 * x * x - 7 * x - 5.4);
//}


/// \class gRPC server класс для обмена данными
class EvaluateIntegralService : public nm::EvaluateIntegral::Service {
    /// \brief функция принимает поток данных (a, b, epsilon) и возвращает поток результатов (value, iter_cnt, h)
    /// \param context контекст обмена
    /// \param stream[in][out] переменная для обмена данными
    /// \return статус обработки (OK)
    grpc::Status Evaluate(
            grpc::ServerContext *context,
            grpc::ServerReaderWriter<nm::Integral, nm::Requirements> *stream) override {
        nm::Requirements requirements;
        IntegralCalculator calculator(f);

        nm::Integral integral;

        std::cout << "--- Receive calc requests ---" << std::endl;
        while (stream->Read(&requirements)) {
            std::cout << "Receive calc request" << std::endl;
            auto result = calculator.calculateThreeEight(
                    requirements.a(),
                    requirements.b(),
                    requirements.epsilon()
            );

            integral.set_value_38(result.value);
            integral.set_call_cnt_38(result.callCnt);

            std::cout << "Calculate 3/8" << std::endl;

            result = calculator.calculateGauss(
                    requirements.a(),
                    requirements.b(),
                    requirements.epsilon()
            );

            integral.set_value_gauss(result.value);
            integral.set_call_cnt_gauss(result.callCnt);

            std::cout << "Return calc result" << std::endl;
            stream->Write(integral);
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