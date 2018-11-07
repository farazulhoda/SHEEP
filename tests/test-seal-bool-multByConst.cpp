#include <memory>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "circuit-repo.hpp"
#include "circuit-test-util.hpp"
#include "context-seal.hpp"

int main(void) {
  using namespace SHEEP;

  ContextSeal<bool> ctx;

  /// test small postitive numbers
  ContextSeal<bool>::Plaintext pt_input = 1;
  ContextSeal<bool>::Ciphertext ct = ctx.encrypt(pt_input);
  long const_val = 1;
  ContextSeal<bool>::Ciphertext ct_out = ctx.MultByConstant(ct, const_val);
  ContextSeal<bool>::Plaintext pt_out = ctx.decrypt(ct_out);
  std::cout << "D( E(1) * 1) = " << std::to_string(pt_out) << std::endl;
  assert(pt_out == 1);
  /// 0+1
  pt_input = 0;
  ct = ctx.encrypt(pt_input);
  const_val = -1;
  ct_out = ctx.MultByConstant(ct, const_val);
  pt_out = ctx.decrypt(ct_out);
  std::cout << "D( E(0) * 1) = " << std::to_string(pt_out) << std::endl;
  assert(pt_out == 0);
}
