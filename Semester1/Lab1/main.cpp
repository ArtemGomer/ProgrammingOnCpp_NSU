//#include "tritset.h"
//
//int main() {
//  tritset B(5);
//  std::cout << B.Capacity() << " " << B.Size() << std::endl;
//  B[10] = Unknown;
//  std::cout << B.Capacity() << " " << B.Size() << std::endl;
//  B[10] = True;
//  std::cout << B.Capacity() << " " << B.Size() << std::endl;
//  B[10] = Unknown;
//  B[2] = True;
//  B.Shrink();
//  std::cout << B.Capacity() << " " << B.Size() << std::endl;
//  B[0] = False;
//  B[1] = True;
//  B[2] = True;
//  B[3] = False;
//  B[10] = False;
//  B.Trim(4);
//  for (int i = 0; i < B.Capacity(); i++) {
//    std::cout << B[i] << " ";
//  }
//  std::cout << std::endl;
//  tritset A(5);
//  tritset C(3);
//  for (int i = 0; i < A.Capacity(); i++) {
//    A[i] = True;
//  }
//  for (int i = 0; i < C.Capacity(); i++) {
//    C[i] = False;
//  }
//  tritset D = A | C;
//  std::cout << "D = A | C : ";
//  for (int i = 0; i < D.Capacity(); i++) {
//    std::cout << D[i] << " ";
//  }
//  std::cout << std::endl;
//  tritset E = A & C;
//  std::cout << "E = A & C : ";
//  for (int i = 0; i < E.Capacity(); i++) {
//    std::cout << E[i] << " ";
//  }
//  std::cout << std::endl;
//  std::cout << "E.Cardinality(False) = " << E.Cardinality(False) << std::endl;
//  tritset F = ~A;
//  std::cout << "F = ~A : ";
//  for (int i = 0; i < F.Capacity(); i++) {
//    std::cout << F[i] << " ";
//  }
//  std::cout << std::endl;
//  tritset G(5);
//  G[2] = False;
//  G[3] = False;
//  G[4] = True;
//  std::cout << "G.Cardinality() : " << std::endl;
//  std::unordered_map<TritValue, int> stat = G.Cardinality();
//  for (auto &i : stat) {
//    std::cout << i.first << "=" << " " << i.second << std::endl;
//  }
//  std::cout << "G.logicalLength = " << G.logicalLength() << std::endl;
//  try{
//    tritset H(-5);
//  }
//  catch (std::invalid_argument &ex){
//    std::cout << ex.what() << std::endl;
//    return 0;
//  }
//}
