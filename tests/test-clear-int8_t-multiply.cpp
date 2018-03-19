#include <memory>

#include "context-clear.hpp"

#include "circuit-repo.hpp"

using namespace Sheep::Clear;

int main(void) {

  
    //// instantiate the Circuit Repository
  CircuitRepo cr;

  //// build a circuit with a specified depth of a specified gate
  
  Circuit C = cr.create_circuit(Gate::Multiply, 3);
  std::cout << C;
  
  
  ContextClear<int8_t> ctx;
  
  ContextClear<int8_t>::CircuitEvaluator run_circuit;
  run_circuit = ctx.compile(C);
	
  std::list<ContextClear<int8_t>::Plaintext> plaintext_inputs = {4, 5, 6, 7};
  std::list<ContextClear<int8_t>::Ciphertext> ciphertext_inputs;

  uint8_t product = 1;

  
  for (ContextClear<int8_t>::Plaintext pt: plaintext_inputs) {
    ciphertext_inputs.push_back(ctx.encrypt(pt));
    product = (product * pt) % 256;
  }
  std::list<ContextClear<int8_t>::Ciphertext> ciphertext_outputs;
  using microsecond = std::chrono::duration<double, std::micro>;
  microsecond time = run_circuit(ciphertext_inputs, ciphertext_outputs);
  
  std::list<ContextClear<int8_t>::Plaintext> plaintext_outputs;
  for (ContextClear<int8_t>::Ciphertext ct: ciphertext_outputs) {
    ContextClear<int8_t>::Plaintext pt = ctx.decrypt(ct);
    plaintext_outputs.push_back(pt);
    std::cout << "output: "<<std::to_string(pt) << std::endl;
  }
  std::cout << "time was " << time.count() << " microseconds\n";

  if ( plaintext_outputs.front() == product) return 0;
  return -1;
  
}