#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265
#define MAX_INPUT 3

double to_radian(double degree) {
    return degree * PI / 180.0;
}

void kinematika_omni_wheel(char *robot, double kecepatan[][3], int jumlah_input) {
    double diameter_roda, jari_jari_roda;
    double jarak_roda = 0.15;
    double kinematika_matrix[3][3];
    double kecepatan_roda[3];
    char arah;

    if (strcmp(robot, "LILDAN") == 0) {
        diameter_roda = 0.127;
        jari_jari_roda = diameter_roda / 2.0;
        arah = '▼';

        kinematika_matrix[0][0] = (-sin(to_radian(135)) / jari_jari_roda);
        kinematika_matrix[0][1] = (-cos(to_radian(135)) / jari_jari_roda);
        kinematika_matrix[0][2] = (jarak_roda / jari_jari_roda);

        kinematika_matrix[1][0] = (sin(to_radian(0)) / jari_jari_roda);
        kinematika_matrix[1][1] = (-cos(to_radian(0)) / jari_jari_roda);
        kinematika_matrix[1][2] = (jarak_roda / jari_jari_roda);

        kinematika_matrix[2][0] = (sin(to_radian(45)) / jari_jari_roda);
        kinematika_matrix[2][1] = (cos(to_radian(45)) / jari_jari_roda);
        kinematika_matrix[2][2] = (jarak_roda / jari_jari_roda);

    } else if (strcmp(robot, "DHARMI") == 0) {
        diameter_roda = 0.048;
        jari_jari_roda = diameter_roda / 2.0;
        arah = '∆';

        kinematika_matrix[0][0] = (sin(to_radian(240)) / jari_jari_roda);
        kinematika_matrix[0][1] = (cos(to_radian(120)) / jari_jari_roda);
        kinematika_matrix[0][2] = (jarak_roda / jari_jari_roda);

        kinematika_matrix[1][0] = (sin(to_radian(120)) / jari_jari_roda);
        kinematika_matrix[1][1] = (cos(to_radian(240)) / jari_jari_roda);
        kinematika_matrix[1][2] = (jarak_roda / jari_jari_roda);

        kinematika_matrix[2][0] = (sin(to_radian(360)) / jari_jari_roda);
        kinematika_matrix[2][1] = (cos(to_radian(360)) / jari_jari_roda);
        kinematika_matrix[2][2] = (jarak_roda / jari_jari_roda);

    } else {
        printf("Robot tidak dikenal!\n");
        return;
    }

    printf("%c\n", arah);

    for (int k = 0; k < jumlah_input; k++) {
        for (int i = 0; i < 3; i++) {
            kecepatan_roda[i] = 0;
            for (int j = 0; j < 3; j++) {
                kecepatan_roda[i] += (kinematika_matrix[i][j] * kecepatan[k][j]);
            }
        }

        if (kecepatan_roda[0] != 0 || kecepatan_roda[1] != 0 || kecepatan_roda[2] != 0) {
            printf("%.2f\n", kecepatan_roda[0]);
            printf("%.2f\n", kecepatan_roda[1]);
            printf("%.2f\n", kecepatan_roda[2]);
        }
    }
}

int main() {
    char robot[10];
    double kecepatan[MAX_INPUT][3];
    int jumlah_input = 0;
    char input[50];

    printf("Masukkan nama robot (LILDAN atau DHARMI): ");
    scanf("%s", robot);
    getchar();

    if (strcmp(robot, "LILDAN") == 0) {
        jumlah_input = MAX_INPUT;
    } else if (strcmp(robot, "DHARMI") == 0) {
        jumlah_input = MAX_INPUT;
    } else {
        printf("Robot tidak dikenal!\n");
        return 1;
    }

    for (int i = 0; i < MAX_INPUT; i++) {
        printf("Masukkan Vx, Vy, w (masukkan 'GAS' untuk berhenti): ");
        fgets(input, sizeof(input), stdin);

        if (strncmp(input, "GAS", 3) == 0) {
            break; // Berhenti jika input 'GAS'
        }

        if (sscanf(input, "%lf %lf %lf", &kecepatan[i][0], &kecepatan[i][1], &kecepatan[i][2]) != 3) {
            printf("Input tidak valid, gunakan format 'Vx Vy w'.\n");
            continue;
        }
    }

    // Hitung dan jalankan perhitungan kinematika hanya setelah 'GAS'
    printf("Hasil perhitungan:\n");
    kinematika_omni_wheel(robot, kecepatan, MAX_INPUT);

    return 0;
}
