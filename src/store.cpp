#include <fstream>
#include <stdexcept>

#include "store.h"

using namespace libs;

void FileManager::saveData(const std::string &data) {
  std::string encryptedData = encrypt(data);
  std::ofstream file(filename_);
  if (!file) {
    throw std::runtime_error("Unable to open file for writing");
  }
  file << encryptedData;
}

std::string FileManager::loadData() {
  std::ifstream file(filename_);
  if (!file) {
    throw std::runtime_error("Unable to open file for reading");
  }

  std::string encryptedData((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
  std::string decryptedData = decrypt(encryptedData);

  return decryptedData;
}

std::string FileManager::encrypt(const std::string &data) {
  // 简单的异或加密，使用固定的密钥
  const char key = 0x42;
  std::string result = data;
  for (char &c : result) {
    c ^= key;
  }
  return result;
}

std::string FileManager::decrypt(const std::string &data) {
  // 解密过程与加密相同（异或运算的特性）
  return encrypt(data);
}
