#include <stdio.h>
#include <math.h>

#define PI 3.14159265

// Fungsi untuk mengonversi derajat ke radian
double to_radian(double degree) {
    return degree * PI / 180.0;
}

// Fungsi untuk membuat matriks transformasi berdasarkan parameter DH
void compute_dh_transform(double a, double alpha, double d, double theta, double T[4][4]) {
    alpha = to_radian(alpha);
    theta = to_radian(theta);

    T[0][0] = cos(theta);
    T[0][1] = -sin(theta) * cos(alpha);
    T[0][2] = sin(theta) * sin(alpha);
    T[0][3] = a * cos(theta);

    T[1][0] = sin(theta);
    T[1][1] = cos(theta) * cos(alpha);
    T[1][2] = -cos(theta) * sin(alpha);
    T[1][3] = a * sin(theta);

    T[2][0] = 0;
    T[2][1] = sin(alpha);
    T[2][2] = cos(alpha);
    T[2][3] = d;

    T[3][0] = 0;
    T[3][1] = 0;
    T[3][2] = 0;
    T[3][3] = 1;
}

// Fungsi untuk mengalikan dua matriks 4x4
void multiply_matrix(double A[4][4], double B[4][4], double result[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Fungsi untuk menghitung posisi akhir end-effector berdasarkan parameter DH
void compute_end_effector_position(double dh_params[][4], int num_joints) {
    double T[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    double temp[4][4], result[4][4];

    for (int i = 0; i < num_joints; i++) {
        double a = dh_params[i][0];
        double alpha = dh_params[i][1];
        double d = dh_params[i][2];
        double theta = dh_params[i][3];

        compute_dh_transform(a, alpha, d, theta, temp);
        multiply_matrix(T, temp, result);

        // Salin hasil ke T untuk langkah selanjutnya
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                T[r][c] = result[r][c];
            }
        }
    }

    // Posisi akhir end-effector
    printf("%.2f\n%.2f\n%.2f\n", T[0][3], T[1][3], T[2][3]);
}

int main() {
    char robot;
    double theta1, theta2, theta3;

    // Input robot (L atau D) dan tiga nilai sudut
    scanf(" %c", &robot);
    scanf("%lf %lf %lf", &theta1, &theta2, &theta3);

    double dh_params[3][4];

    if (robot == 'L') {
        // Parameter DH untuk Lildan
        dh_params[0][0] = 0;      dh_params[0][1] = 90; dh_params[0][2] = 5;      dh_params[0][3] = theta1;
        dh_params[1][0] = 3;      dh_params[1][1] = 0;  dh_params[1][2] = 0;      dh_params[1][3] = theta2;
        dh_params[2][0] = 2;      dh_params[2][1] = 0;  dh_params[2][2] = 0;      dh_params[2][3] = theta3;
    } else if (robot == 'D') {
        // Parameter DH untuk Dharmi
        dh_params[0][0] = 0;      dh_params[0][1] = 90; dh_params[0][2] = 6;      dh_params[0][3] = theta1;
        dh_params[1][0] = 3;      dh_params[1][1] = 0;  dh_params[1][2] = 0;      dh_params[1][3] = theta2;
        dh_params[2][0] = 2;      dh_params[2][1] = 0;  dh_params[2][2] = 0;      dh_params[2][3] = theta3;
    } else {
        printf("Robot tidak dikenal!\n");
        return 1;
    }

    // Hitung dan tampilkan posisi akhir end-effector
    compute_end_effector_position(dh_params, 3);

    return 0;
}
