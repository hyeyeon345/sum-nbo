#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <stdlib.h>
#include <netinet/in.h> // for htons, htonl

uint32_t readFile(char *file, uint8_t *nb) {
    FILE *fp = fopen(file, "rb"); //바이너리 파일 읽기
    size_t read = fread(nb, sizeof(uint8_t), 4, fp); //파일 내용 저장

    fseek(fp, 0, SEEK_END); //파일 내 포인트 위치 변경
    int size = ftell(fp); //파일의 현재 위치 찾기
    if (size < 4) { //파일의 크기가 4바이트보다 작은 경우
        printf("File '%s' : Size error", file);
        fclose(fp);
        exit(EXIT_FAILURE);

    }
    if (fp == NULL) { //파일이 제대로 열리지 않는 경우
        printf("File '%s' : Empty", file);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fclose(fp); //fopen 함수로 열려진 파일 닫기

    uint32_t* p = reinterpret_cast<uint32_t*>(nb);
    uint32_t n = ntohl(*p); //network to host

    return n;
}

int main(int argc, char *argv[]) {
    //입력 확인
    if (argc!=3) {
        fprintf(stderr, "Usage: %s <inputfile1> <inputfile2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file1 = argv[1], *file2 = argv[2];
    uint8_t nb1[4] = {}, nb2[4] = {};
    uint32_t n1 = readFile(file1, nb1);
    uint32_t n2 = readFile(file2, nb2);
    //결과 출력
    printf("%d(0x%08x) + %d(0x%08x) = %d(0x%08x)", n1, n1, n2, n2, n1 + n2, n1 + n2);
}
