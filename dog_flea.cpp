#include <iostream>
#include "eigen-3.3.7/Eigen/Dense"

int main() {
    int N, absorbed, start, lambda;
    std::cin >> N >> absorbed >> start >> lambda;
    Eigen::MatrixXd Q = Eigen::MatrixXd::Constant(N + 1, N + 1, 0.0), 
                    V = Eigen::MatrixXd::Constant(N, N, 0.0), F;
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < N + 1; j++) {
            if (j == i + 1) {
                Q(i, j) = lambda * (N - i);
            } else if (j == i - 1) {
                Q(i, j) = lambda * i;
            } else if (j == i) {
                Q(i, j) = -lambda * N;
            }
        }
    }
    std::cout << ">>> Q" << std::endl;
    std::cout << Q << std::endl;
    V.block(0, 0, absorbed, absorbed) = Q.block(0, 0, absorbed, absorbed);
    V.block(0, absorbed, absorbed, N - absorbed) = Q.block(0, absorbed + 1, absorbed, N - absorbed);
    V.block(absorbed, 0, N - absorbed, absorbed) = Q.block(absorbed + 1, 0, N - absorbed, absorbed);
    V.block(absorbed, absorbed, N - absorbed, N - absorbed) = Q.block(absorbed + 1, absorbed + 1, N - absorbed, N - absorbed);
    std::cout << ">>> V" << std::endl;
    std::cout << V << std::endl;
    F = -(V.inverse());
    std::cout << ">>> F = -(V ^ -1)" << std::endl;
    std::cout << F << std::endl;
    std::cout << F.row((start > absorbed) ? (start - 1) : start).sum() << std::endl;
    return 0;
}
