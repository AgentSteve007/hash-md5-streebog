#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <openssl/md5.h> // ��� ������ � MD5
#include <vector>
#include <sstream>

// ��������� ���������� ����������� ������� ����� ��������� ����������
// ��� ����� ������� ������������, ��� � ��� ���� ���������� ��� �������
// ����� ������������, ��������, ���������� "streebog" ��� �����������

// ������� ��� ���������� MD5
std::string computeMD5(const std::string& data) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext;
    MD5_Init(&mdContext);
    MD5_Update(&mdContext, data.c_str(), data.length());
    MD5_Final(digest, &mdContext);

    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        ss << std::setfill('0') << std::setw(2) << std::hex << (int)digest[i];
    }
    return ss.str();
}

// ������� ��� ���������� ������� (����������������, ���������� ����)
std::string computeStreebog(const std::string& data) {
    // ���������� ������� (����� ���� ������������ ��������� ����������)
    // ��������� ��������, �������� �� �������� ���������� �������
    return "stub_streebog_hash_for_example";
}

int main9() {
    // ������ ������ �� �����
    std::ifstream file("large.txt", std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // ������ ����� ����������� ����� � ������
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string fileContent = ss.str();

    // ��������� ������� ��� MD5
    auto start = std::chrono::high_resolution_clock::now();
    std::string md5Hash = computeMD5(fileContent);
    auto end = std::chrono::high_resolution_clock::now();
    auto md5Duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // ��������� ������� ��� �������
    start = std::chrono::high_resolution_clock::now();
    std::string streebogHash = computeStreebog(fileContent);
    end = std::chrono::high_resolution_clock::now();
    auto streebogDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // ����� �����������
    std::cout << "MD5 hash: " << md5Hash << std::endl;
    std::cout << "MD5 time: " << md5Duration << " ms" << std::endl;
    std::cout << "Streebog hash: " << streebogHash << std::endl;
    std::cout << "Streebog time: " << streebogDuration << " ms" << std::endl;

    return 0;
}
