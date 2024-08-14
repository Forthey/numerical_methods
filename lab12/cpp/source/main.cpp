#include <iostream>
#include <fstream>
#include <cmath>

#include "runge_kutta.hpp"


class FileParser {
public:
    struct RequirementsP1DTO {
        struct SingleRequirement {
            double endX = 0.0;
            double h0 = 0.0;
        };

        std::vector<SingleRequirement> requirements;
    };
    struct ResultP1DTO {
        struct SingleResult {
            TabFunc const tabFunc;
            double h0 = 0.0;
        };
        std::vector<SingleResult> results;
    };
    struct RequirementsP2DTO {
        struct SingleRequirement {
            double endX = 0.0;
            double epsilon = 0.0;
        };

        std::vector<SingleRequirement> requirements;
    };
    struct ResultP2DTO {
        struct SingleResult {
            TabFunc const tabFunc;
            std::vector<double> const h;
            double epsilon = 0.0;
        };
        std::vector<SingleResult> results;
    };

    FileParser() = delete;

    static bool readRequirementsP1(RequirementsP1DTO &requirements) {
        std::ifstream inFile("../data/in.data");

        if (!inFile.is_open()) {
            return false;
        }

        RequirementsP1DTO::SingleRequirement requirement;
        while (!!(inFile >> requirement.endX >> requirement.h0)) {
            requirements.requirements.push_back(requirement);
        }
        return true;
    }

    static bool writeResultP1(ResultP1DTO const &results) {
        std::ofstream outFile("../data/out.data");

        if (!outFile.is_open()) {
            return false;
        }

        for (auto const &result: results.results) {
            for (Point const &point : result.tabFunc) {
                outFile << point.x << " ";
            }
            outFile << std::endl;
            for (Point const &point : result.tabFunc) {
                outFile << point.y << " ";
            }
            outFile << std::endl;
            outFile << result.h0 << std::endl;
        }
        return true;
    }

    static bool readRequirementsP2(RequirementsP2DTO &requirements) {
        std::ifstream inFile("../data/in.data");

        if (!inFile.is_open()) {
            return false;
        }

        RequirementsP2DTO::SingleRequirement requirement;
        while (!!(inFile >> requirement.endX >> requirement.epsilon)) {
            requirements.requirements.push_back(requirement);
        }
        return true;
    }

    static bool writeResultP2(ResultP2DTO const &results) {
        std::ofstream outFile("../data/out.data");

        if (!outFile.is_open()) {
            return false;
        }

        for (auto const &result: results.results) {
            for (Point const &point : result.tabFunc) {
                outFile << point.x << " ";
            }
            outFile << std::endl;
            for (Point const &point : result.tabFunc) {
                outFile << point.y << " ";
            }
            outFile << std::endl;
            for (double const h : result.h) {
                outFile << h << " ";
            }
            outFile << std::endl;
            outFile << result.epsilon << std::endl;
        }
        return true;
    }
};


double f(double const x, double const y) {
    return 2.0 * x * (x * x + y);
}


void doP1Stats() {
    Point const cauchyInit = {
            1.2990235078222893742411631714876982614634739084982215079949469166,
            2.7182818284590452353602874713526624977572470936999595749669676277
    };

    FileParser::RequirementsP1DTO requirements;
    if (!FileParser::readRequirementsP1(requirements)) {
        std::cout << "cannot read input file, exiting...";
        exit(1);
    }

    RungeKuttaSolver solver(f);

    FileParser::ResultP1DTO results;
    for (auto const &requirement: requirements.requirements) {
        results.results.emplace_back(
                std::move(solver.solveConst(cauchyInit, requirement.endX, requirement.h0)),
                requirement.h0
        );
    }
    if (!FileParser::writeResultP1(results)) {
        std::cout << "cannot open output file, exiting...";
        exit(1);
    }

}

void doP2Stats() {
    Point const cauchyInit = {
            1.2990235078222893742411631714876982614634739084982215079949469166,
            2.7182818284590452353602874713526624977572470936999595749669676277
    };

    FileParser::RequirementsP2DTO requirements;
    if (!FileParser::readRequirementsP2(requirements)) {
        std::cout << "cannot read input file, exiting...";
        exit(1);
    }

    RungeKuttaSolver solver(f);

    FileParser::ResultP2DTO results;
    for (auto const &requirement: requirements.requirements) {
        results.results.emplace_back(
                std::move(solver.solve(cauchyInit, requirement.endX, requirement.epsilon)),
                solver.getLastSegSteps(),
                requirement.epsilon
        );
    }
    if (!FileParser::writeResultP2(results)) {
        std::cout << "cannot open output file, exiting...";
        exit(1);
    }
}


int main() {
    int num;
    std::cout << "Enter paragraph number: ";
    std::cin >> num;

    switch (num) {
        case 1:
            doP1Stats();
            break;
        case 2:
            doP2Stats();
            break;
        default:
            std::cout << "Wrong input";
            break;
    }
    return 0;
}