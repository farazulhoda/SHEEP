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
  for (Plaintext pt_orig = 0; pt_orig < UINT8_MAX; pt_orig++) {
    Plaintext pt_new = context.decrypt(context.encrypt(pt_orig));
    // std::cout << std::to_string(pt_orig) << " -> " << std::to_string(pt_new)
    // << "\n";
    assert(pt_orig == pt_new);
  }
}

int main(void) {
  ContextTFHE<uint8_t> context;
  test_single(context);
}
