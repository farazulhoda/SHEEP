#include <cstdint>
#include <cassert>
#include <algorithm>
#include "context-tfhe.hpp"
#include "simple-circuits.hpp"
#include "circuit-test-util.hpp"

using namespace SHEEP;
typedef ContextTFHE<int8_t>::Plaintext Plaintext;
typedef ContextTFHE<int8_t>::Ciphertext Ciphertext;

// Encrypt a value, decrypt the result, and check that we are
// left with the original value.
void test_single(ContextTFHE<int8_t>& context) {
	
  std::vector<Plaintext> pt_orig = {10, 0, -5};
  std::vector<Plaintext> pt_new = context.decrypt(context.encrypt(pt_orig));

  for (int i = 0; i < pt_new.size(); i++) {
    std::cout << std::to_string(pt_orig[i]) << " = " << std::to_string(pt_new[i]) << std::endl;
  }

  assert(pt_orig == pt_new);
}

int main(void) {
	ContextTFHE<int8_t> context;
	test_single(context);
}
