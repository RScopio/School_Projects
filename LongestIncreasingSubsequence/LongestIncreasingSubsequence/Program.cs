using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LongestIncreasingSubsequence
{
    class Program
    {
        static int[] LISS(int[] X, int N)
        {
            int[] P = new int[N];
            int[] M = new int[N + 1];

            int L = 0;
            for (int i = 0; i <= N - 1; i++)
            {
                int lo = 1;
                int hi = L;
                while (lo <= hi)
                {
                    int mid = (int)Math.Ceiling((double)((lo + hi) / 2));
                    if (X[M[mid]] < X[i])
                    {
                        lo = mid + 1;
                    }
                    else
                    {
                        hi = mid - 1;
                    }
                }

                int newL = lo;
                P[i] = M[newL - 1];
                M[newL] = i;

                if (newL > L)
                {
                    L = newL;
                }
            }

            int[] S = new int[L];
            int k = M[L];
            for (int i = L - 1; i >= 0; i--)
            {
                S[i] = X[k];
                k = P[k];
            }

            return S;
        }


        static void Main(string[] args)
        {
            int[] X = { 4, -2, 5, 2, 2, 2, -6, 6, 3, 3, -1, 5, 6, -7, 8, -9, 10 };
            int N = X.Length;

            Console.Write("Original: ");
            foreach (int x in X)
            {
                Console.Write($"{x} ");
            }


            int[] liss = LISS(X, N);
            Console.Write("\nLISS: ");
            foreach (int i in liss)
            {
                Console.Write($"{i} ");
            }
            Console.WriteLine("\n");
            Console.ReadKey();
        }
    }
}
