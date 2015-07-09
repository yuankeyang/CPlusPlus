/**********************
 *程序描述：DFA化简
**********************/

#include <iostream>
#include <algorithm>
#include<stdlib.h>

/* Refinable partition */
int *M, *W, w = 0;  // temporary worksets

struct partition{
  int z, *E, *L, *S, *F, *P;

  void init( int n ){
    z = bool( n );  E = new int[n];
    L = new int[n]; S = new int[n];
    F = new int[n]; P = new int[n];
    for( int i = 0; i < n; ++i ){
      E[i] = L[i] = i; S[i] = 0; }
    if( z ){ F[0] = 0; P[0] = n; }
  }

  void mark( int e ){
    int s = S[e], i = L[e], j = F[s]+M[s];
    E[i] = E[j]; L[E[i]] = i;
    E[j] = e; L[e] = j;
    if( !M[s]++ ){ W[w++] = s; }
  }

  void split(){
    while( w ){
      int s = W[--w], j = F[s]+M[s];
      if( j == P[s] ){M[s] = 0; continue;}
      if( M[s] <= P[s]-j ){
        F[z] = F[s]; P[z] = F[s] = j; }
      else{
        P[z] = P[s]; F[z] = P[s] = j; }
      for( int i = F[z]; i < P[z]; ++i ){
        S[E[i]] = z; }
      M[s] = M[z++] = 0;
    }
  }

};

partition
  B,     // blocks (consist of states)
  C;     // cords (consist of transitions)

int
  nn,    // 状态数
  mm,    // 转移数
  ff,    // 接收态数
  q0,    // 初始状态
  *T,    // 转移
  *L,    // labels of transitions
  *H;    // heads of transitions

bool cmp( int i, int j ){
  return L[i] < L[j]; }

/* Adjacent transitions */
int *A, *F;
void make_adjacent( int K[] ){
  int q, t;
  for( q = 0; q <= nn; ++q ){ F[q] = 0; }
  for( t = 0; t < mm; ++t ){ ++F[K[t]]; }
  for( q = 0; q < nn; ++q )F[q+1] += F[q];
  for( t = mm; t--; ){ A[--F[K[t]]] = t; }
}

/* Removal of irrelevant parts */
int rr = 0;   // number of reached states

inline void reach( int q ){
  int i = B.L[q];
  if( i >= rr ){
    B.E[i] = B.E[rr]; B.L[B.E[i]] = i;
    B.E[rr] = q; B.L[q] = rr++; }
}

void rem_unreachable( int T[], int H[] ){
  make_adjacent( T ); int i, j;
  for( i = 0; i < rr; ++i ){
    for( j = F[B.E[i]];
         j < F[B.E[i] + 1]; ++j ){
      reach( H[A[j]] ); } }
  j = 0;
  for( int t = 0; t < mm; ++t ){
    if( B.L[T[t]] < rr ){
      H[j] = H[t]; L[j] = L[t];
      T[j] = T[t]; ++j; } }
  mm = j; B.P[0] = rr; rr = 0;
}

/* 主函数*/
int main(){

  /* 输入状态数、转移数、初始状态、接收状态数*/
  std::cin >> nn >> mm >> q0 >> ff;
  T = new int[ mm ]; L = new int[ mm ];
  H = new int[ mm ]; B.init( nn );
  A = new int[ mm ]; F = new int[ nn+1 ];

  /* 读取转移表 */
  for( int t = 0; t < mm; ++t ){
    std::cin >> T[t] >> L[t] >> H[t]; }

  /* Remove states that cannot be reached
    from the initial state, and from which
    final states cannot be reached */
  reach( q0 ); rem_unreachable( T, H );
  for( int i = 0; i < ff; ++i ){
    int q; std::cin >> q;
    if( B.L[q] < B.P[0] ){ reach( q ); } }
  ff = rr; rem_unreachable( H, T );

  /* Make initial partition */
  W = new int[ mm+1 ]; M = new int[ mm+1];
  M[0] = ff;
  if( ff ){ W[w++] = 0; B.split(); }

  /* Make transition partition */
  C.init( mm );
  if( mm ){
    std::sort( C.E, C.E+mm, cmp );
    C.z = M[0] = 0; int a = L[C.E[0]];
    for( int i = 0; i < mm; ++i ){
      int t = C.E[i];
      if( L[t] != a ){
        a = L[t]; C.P[C.z++] = i;
        C.F[C.z] = i; M[C.z] = 0; }
      C.S[t] = C.z; C.L[t] = i; }
    C.P[C.z++] = mm;
  }

  make_adjacent( H );
  int b = 1, c = 0, i, j;
  while( c < C.z ){
    for( i = C.F[c]; i < C.P[c]; ++i ){
      B.mark( T[C.E[i]] ); }
    B.split(); ++c;
    while( b < B.z ){
      for( i = B.F[b]; i < B.P[b]; ++i ){
        for(
          j = F[B.E[i]];
          j < F[B.E[i]+1]; ++j
        ){
          C.mark( A[j] ); } }
      C.split(); ++b; }
  }

  /* 计算转换数和接收态个数*/
  int mo = 0, fo = 0;
  for( int t = 0; t < mm; ++t ){
    if( B.L[T[t]] == B.F[B.S[T[t]]] ){
      ++mo; } }
  for( int b = 0; b < B.z; ++b ){
    if( B.F[b] < ff ){ ++fo; } }

  /*输出简化的DFA */
  std::cout<<"/*******简化后的DFA*******/\n";
  std::cout << B.z <<' '<< mo
    <<' '<< B.S[q0] <<' '<< fo <<'\n';
  for( int t = 0; t < mm; ++t ){
    if( B.L[T[t]] == B.F[B.S[T[t]]] ){
      std::cout << B.S[T[t]] <<' '<< L[t]
        <<' '<< B.S[H[t]] <<'\n'; } }
  for( int b = 0; b < B.z; ++b ){
    if( B.F[b] < ff ){
      std::cout << b <<'\n'; } }
  system("pause");

}
