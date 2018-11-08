#include <algorithm>
#include <cassert>
#include <cstdint>
#include "circuit-test-util.hpp"
#include "context-tfhe.hpp"
#include "simple-circuits.hpp"

using namespace SHEEP;
typedef ContextTFHE<uint8_t>::Plaintext Plaintext;
typedef ContextTFHE<uint8_t>::Ciphertext Ciphertext;

// Encrypt a value, decrypt the result, and check that we are
// left with the original value.
void test_single(ContextTFHE<uint8_t>& context) {
  std::vector<Plaintext> pt_orig = {10, 0, 5};
  std::vector<Plaintext> pt_new = context.decrypt(context.encrypt(pt_orig));

  for (int i = 0; i < pt_new.size(); i++) {
    std::cout << std::to_string(pt_orig[i]) << " = "
              << std::to_string(pt_new[i]) << std::endl;
  }

  assert(pt_orig == pt_new);
}

int main(void) {
  ContextTFHE<uint8_t> context;
  test_single(context);
}
